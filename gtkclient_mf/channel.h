#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_sort.h>
#include <sqlite3.h>
#include "gettime.h"
#include "sql.h"
#include "matchSpike.h"

void gsl_matrix_to_mat(gsl_matrix *x, const char* fname);
void glPrint(char *text);

//need some way of encapsulating per-channel information.
class Channel {
private:
	float	m_aperture[2];
	float m_threshold;
	float	m_centering; //left/right centering. used to look for threshold crossing.
public:
	Vbo*	m_wfVbo; //range 1 mean 0
	Vbo*	m_usVbo;
	VboPca*	m_pcaVbo; //2D points, with color.
	float	m_pca[2][32]; //range 1 mean 0
	float m_pcaScl[2]; //sqrt of the eigenvalues.
	matchSpike	m_mspk[2]; //IIR matched filter class -- also stores filter coef.
	float	m_mf[2][10]; // same as matlab -- mply by 16384 for bfin. 2x 5 coef biquads.
	float m_template[2][16]; //range 1 mean 0.
	float	m_loc[4];
	int	m_ch; //channel number, obvi.
	float m_gain;
	float m_agc;
	int	m_lmsEn; // is LMS enabled for this channel?
	int	m_agcEn; // is AGC enabled for this channel?
	i64	m_isi[2][100]; //counts of the isi, in units of 4 packets -- 768us/packet.
	int	m_lastSpike[2]; //zero when a spike occurs.

	Channel(int ch){
		m_wfVbo = new Vbo(6, 512, 34); //sorted units, with color.
		m_usVbo = new Vbo(3, 256, 34); //unsorted units, all gray.
		m_pcaVbo = new VboPca(6, 1024*8, 1, ch);
		m_pcaVbo->m_fade = 0.f;
		m_ch = ch;
		m_lmsEn = 1; //should be read from the database. oops.
		m_agcEn = 1;
		//init PCA, template.
		for(int j=0; j<32; j++){
			m_pca[0][j] = 1.f/8.f;
			m_pca[1][j] = (j > 15 ? 1.f/8.f : -1.f/8.f);
			m_pcaScl[0] = m_pcaScl[1] = 1.f;
		}
		float mfA[10]={1.f,0.f,0.f,0.1f,0.f,1.f,0.f,0.f,0.1f,0.f};
		float mfB[10]={1.f,0.f,0.f,0.1f,0.f,1.f,0.f,0.f,0.1f,0.f};
		for(int j=0; j<10; j++){
			m_mf[0][j] = mfA[j];
			m_mf[1][j] = mfB[j];
		}
		for(int j=0; j<16; j++){
			m_mf[0][j] = 0.f;
			m_mf[1][j] = 0.f;
		}
		//read from sql if it's there..
		for(int j=0; j<2; j++){
			sqliteGetBlob(ch, j, "pca", &(m_pca[j][0]), 32);
			sqliteGetBlob(ch, j, "matchedfilter", &(m_mf[j][0]), 10);
			sqliteGetBlob(ch, j, "template", &(m_template[j][0]), 16);
			m_aperture[j] = sqliteGetValue2(ch, j, "aperture", 56.f);
			m_aperture[j] = 16000; // reset! FIXME
		}
		sqliteGetBlob(ch, 0, "pcaScl", m_pcaScl, 2);
		m_threshold = sqliteGetValue(ch, "threshold", 0.6f);
		m_centering = sqliteGetValue(ch, "centering", 25.f);
		m_gain = sqliteGetValue(ch, "gain", 1.f);
		m_agc = sqliteGetValue(ch, "agc", 6000.f);
		//init m_wfVbo.
		for(int i=0; i<512; i++){
			float* f = m_wfVbo->addRow();
			f[0] = 0.f;
			f[1] = 0.5f;
			f[2] = 0.f;
			f[3] = f[4] = f[5] = 0.f;
			for(int j=0; j<32; j++){
				f[(j+1)*6 + 0] = (float)j/31.f;
				f[(j+1)*6 + 1] = 0.5f;
				f[(j+1)*6 + 2] = 0.0f;
				for(int k=0; k<3; k++)
					f[(j+1)*6 + 3 + k] = 0.5f; //all init gray.
			}
			f[(33)*6 + 0] = 1.f;
			f[(33)*6 + 1] = 0.5f;
			f[(33)*6 + 2] = 0.0f;
			for(int k=0; k<3; k++)
				f[(33)*6 + 3 + k] = 0.5f; //all init gray.
		}
		//init unsorted Vbo,
		for(int i=0; i<256; i++){
			float* f = m_usVbo->addRow();
			f[0] = 0.f;
			f[1] = 0.5f;
			f[2] = 0.f;
			for(int j=0; j<32; j++){
				f[(j+1)*3 + 0] = (float)j/31.f;
				f[(j+1)*3 + 1] = (float)rand()/(float)RAND_MAX - 0.5f;
				f[(j+1)*3 + 2] = 0.0f;
			}
			f[(33)*3 + 0] = 1.f;
			f[(33)*3 + 1] = 0.5f;
			f[(33)*3 + 2] = 0.0f;
		}
		m_loc[0] = m_loc[1] = 0.f;
		m_loc[2] = m_loc[3] = 1.f;
		for(int u=0; u<2; u++){
			m_lastSpike[u] = 0;
			for(unsigned int i=0; i < sizeof(m_isi[0])/sizeof(m_isi[0][0]); i++){
				m_isi[u][i] = 0;
			}
		}
	}
	~Channel(){
		delete m_wfVbo; m_wfVbo = 0;
		delete m_usVbo; m_usVbo = 0;
		delete m_pcaVbo; m_pcaVbo = 0;
	}
	void save(){
		for(int j=0; j<2; j++){
			sqliteSetBlob(m_ch, j, "pca", &(m_pca[j][0]), 32);
			sqliteSetBlob(m_ch, j, "matchedfilter", &(m_mf[j][0]), 10);
			sqliteSetValue2(m_ch, j, "aperture", m_aperture[j]);
		}
		sqliteSetBlob(m_ch, 0, "pcaScl", m_pcaScl, 2);
		sqliteSetValue(m_ch, "threshold", m_threshold);
		sqliteSetValue(m_ch, "centering", m_centering);
		sqliteSetValue(m_ch, "agc", m_agc);
		sqliteSetValue(m_ch, "gain", m_gain);
		m_pcaVbo->save(m_ch);
	}
	int addWf(float* wf, int unit, float time, bool updatePCA){
		if(!m_wfVbo) return 0; //being called from another thread, likely.
		//wf assumed to be 32 points long.
		//wf should range 1 mean 0.
		float color[3] = {0.5, 0.5, 0.5}; //unsorted.
		//error type 1 moves toward green-yellow; error type 2 moves to purple.
		//see color wheel in gimp.
		if(unit == 1){ color[0] = 0.0f; color[1] = 1.0f; color[2] = 1.0f; } //cyan.
		if(unit == 3){ color[0] = 0.0f; color[1] = 1.0f; color[2] = 0.5f; } //cyan-green.
		if(unit == 5){ color[0] = 0.0f; color[1] = 0.5f; color[2] = 1.0f; } //blue-green

		if(unit == 2){ color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f; } //red
		if(unit == 4){ color[0] = 1.0f; color[1] = 0.5f; color[2] = 0.0f; } //orange
		if(unit == 6){ color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.5f; } //magenta.
			//copy to m_wfVbo first.
		if(unit > 0){
			float* f = m_wfVbo->addRow();
			for(int j=0; j<32; j++){
				f[(j+1)*6 + 1] = wf[j];
				f[(j+1)*6 + 2] = time;
				for(int k=0; k<3; k++)
					f[(j+1)*6 + 3 + k] = color[k];
			}
		}else{
			float* f = m_usVbo->addRow();
			for(int j=0; j<32; j++){
				f[(j+1)*3 + 1] = wf[j];
				f[(j+1)*3 + 2] = time;
			}
		}
		if(updatePCA){
			//add waveform to database.
			float* nw = m_pcaVbo->addWf();
			for(int j=0; j<32; j++){
				nw[j] = wf[j];
			}
			//compute PCA. just inner product.
			float* pca = m_pcaVbo->addRow();
			pca[0] = pca[1] = 0.f;
			for(int j=0; j<32; j++){
				for(int i=0; i<2; i++)
					pca[i] += m_pca[i][j] * wf[j];
			}
			pca[2] = time;
			for(int i=0; i<3; i++){
				pca[3+i] = color[i];
			}
		}
		return unit;
	}
	void copy(){
		m_wfVbo->copy();
		m_usVbo->copy();
		m_pcaVbo->copy(false,false);
	}
	void setVertexShader(cgVertexShader* vs){
		m_pcaVbo->setVertexShader(vs);
		m_wfVbo->setVertexShader(vs);
		m_usVbo->setVertexShader(vs);
	}
	void configure(cgVertexShader* vs){
		m_pcaVbo->configure();
		m_wfVbo->configure();
		m_usVbo->configure();
		setVertexShader(vs);
	}
	bool mouse(float* f){
		//possibly set the threshold and centering for this channel.
		//incoming location will be in global coordinates (+-1)
		float x = f[0]; float y = f[1];
		x -= m_loc[0]; y -= m_loc[1];
		x /= m_loc[2]; y /= m_loc[3];
		if(x >= 1/62.f && x <= 31/62.f && y >= 0.f && y <= 1.f){
			m_threshold = (y-0.5f)*2.f;
			x *= 62.f; x -= 0.5f; x = 31.f-x; //inverse centering transform.
			m_centering = x;
			resetPca();
			return true;
		} else return false;
	}
	void addPoly(float* f){ m_pcaVbo->addPoly(f); }
	void resetPoly(){ m_pcaVbo->m_polyW = 0; }
	unsigned int getAperture(int n) { return (unsigned int)(m_aperture[n]);}
	void setApertureLocal(unsigned int a, int n){
		if(n >= 0 && n <= 1) m_aperture[n] = a;
		float aperture = (float)a/255.f;
		float color[3] = {0.f, 1.f, 1.f};
		if(n == 1){color[0] = 1.f; color[1] = 0.f; color[2] = 0.f; }
		m_pcaVbo->updateAperture(m_template[n], aperture, color);
		//this really should be replaced with some sort of matched-filter sorting.
	}
	float getThreshold() { return m_threshold; }
	void setThreshold(float thresh){
		if(thresh != m_threshold)
			resetPca();
		m_threshold = thresh;
	}
	int getCentering() { return (int)m_centering; }
	void setCentering(float c){
		if(c != m_centering)
			resetPca();
		m_centering = c;
	}
	void setLoc(float x, float y, float w, float h){
		m_wfVbo->setLoc(x, y+h/2, w/2.f, h);
		m_usVbo->setLoc(x, y+h/2, w/2.f, h);
		m_pcaVbo->setLoc(x+w/2.f, y+h/4, w/2.f, h/2.f);
		m_loc[0] = x; m_loc[1] = y;
		m_loc[2] = w; m_loc[3] = h;
	}
	void draw(int drawmode, float time, float* cursPos,
				 bool showPca, bool closest, bool showSort){
		glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
		m_usVbo->draw(drawmode, time, true);
		m_pcaVbo->draw(GL_POINTS, time, true, cursPos, closest);
		m_wfVbo->draw(drawmode, time, true);
		if(closest)
			m_pcaVbo->drawClosestWf();

		float ox = m_loc[0]; float oy = m_loc[1];
		float ow = m_loc[2]/2; float oh = m_loc[3];
		//draw the templates.
		glLineWidth(3.f);
		glBegin(GL_LINE_STRIP);
		/*for(int k=0; k<2; k++){
			for(int j=0; j<16; j++){
				float ny = m_template[k][j] + 0.5f;
				float nx = (float)(j+8)/31.f;
				// cyan -> purple; red -> orange (color wheel)
				if(k == 0) glColor4f(0.6f, 0.f, 1.f, 0.65f);
				else glColor4f(1.f, 0.5f, 0.f, 0.65f);
				glVertex3f(nx*ow+ox, ny*oh+oy, 0.f);
			}
			glColor4f(0.f, 0.f, 0.f, 0.75f);
			glVertex3f(1.f*ow+ox, 0.5f*oh+oy, 1.f);
			glVertex3f(0.f*ow+ox, 0.5f*oh+oy, 1.f);
		}
		*/
		//and the PCA templates.
		if(showPca){
			glLineWidth(5.f);
			for(int k=0; k<2; k++){
				for(int j=0; j<32; j++){
					float ny = m_pca[k][j]*m_pcaScl[k]+0.5;
					float nx = (float)(j)/31.f;
					glColor4f(1.f-k, k, 0.f, 0.75f);
					glVertex3f(nx*ow+ox, ny*oh+oy, 0.f);
				}
				glColor4f(0.f, 0.f, 0.f, 0.75f);
				glVertex3f(1.f*ow+ox, 0.5f*oh+oy, 1.f);
				glVertex3f(0.f*ow+ox, 0.5f*oh+oy, 1.f);
			}
		}
		glEnd();
		//and if we are running the matched filter annealing.
		//can do approx 1e6 steps/second.
		//want the GUI to run at 30 fps min -- so can do around 20e3 iterations/frame.
		for(int u=0; u<2; u++){
			if(m_mspk[u].m_nn >= 0){
				m_mspk[u].fit(20000);
				//and plot the output.
				for(int k=0; k<NSOL; k++){
					float tmp[32];
					float q = m_mspk[u].getImpulse(k, tmp);
					glLineWidth(1.f);
					glColor4f(1.f, 0.f, 1.f, 0.5f-q*0.5);
					glBegin(GL_LINE_STRIP);
					for(int j=0; j<32; j++){
						float ny = tmp[j] + 0.5;
						float nx = (float)(j)/31.f;
						glVertex3f(nx*ow+ox, ny*oh+oy, 0.f);
					}
					glEnd();
				}
			}
			//also draw what we are fitting to
			glLineWidth(1.f);
			if(u == 0) glColor4f(0.6f, 0.f, 1.f, 0.95f);
			else glColor4f(1.f, 0.5f, 0.f, 0.95f);
			glBegin(GL_LINE_STRIP);
			for(int j=0; j<32; j++){
				float ny = m_mspk[u].m_ss[j]/32768.f + 0.5;
				float nx = (float)(j)/31.f;
				glVertex3f(nx*ow+ox, ny*oh+oy, 0.f);
			}
			glEnd();
			//and the current best.
			// cyan -> purple; red -> orange (color wheel)
			glLineWidth(3.f);
			if(u == 0) glColor4f(0.6f, 0.f, 1.f, 0.55f);
			else glColor4f(1.f, 0.5f, 0.f, 0.55f);
			glBegin(GL_LINE_STRIP);
			for(int j=0; j<32; j++){
				float ny = m_mspk[u].m_ssFit[j]/32768.f + 0.5;
				float nx = (float)(j)/31.f;
				glVertex3f(nx*ow+ox, ny*oh+oy, 0.f);
			}
			glEnd();
		}
		//if we are in sort mode:
		if(showSort){
			//draw a dark blue quad for the template ROI.
			glColor4f(0.2f,0.1f,1.f,0.15f);
			glBegin(GL_QUADS);
			glVertex2f(ow*8.0/31.f + ox, oh*0.02f + oy);
			glVertex2f(ow*8.0/31.f + ox, oh*0.98f + oy);
			glVertex2f(ow*23.0/31.f + ox,oh*0.98f + oy);
			glVertex2f(ow*23.0/31.f + ox,oh*0.02f + oy);
			glEnd();
			//draw the threshold & centering.
			//glDisableClientState(GL_VERTEX_ARRAY);
			glColor4f(1.f,1.f,1.f,0.4f);
			glLineWidth(1.f);
			glBegin(GL_LINE_STRIP);
			float t = m_threshold;
			t = oh*(t/2.f+0.5) + oy;
			glVertex2f(0.0f+ox, t);
			glVertex2f(0.5f+ox, t);
			glEnd();
			glColor4f(1.f,1.f,1.f,0.3f);
			glBegin(GL_LINE_STRIP);
			float c = (float)m_centering;
			c = 31.f-c; c += 0.5f; c /= (31.f*2.f); //centering transform.
			glVertex2f(c+ox, t-0.2*oh);
			glVertex2f(c+ox, t+0.2*oh);
			glEnd();
		}
		if(1){
			//draw shaded plots of the ISI.
			for(int u=0; u<2; u++){
				int nisi = sizeof(m_isi[0])/sizeof(m_isi[0][0]);
				i64 max = 1;
				for(int i=0; i < nisi; i++){
					max = m_isi[u][i] > max ? m_isi[u][i] : max;
				}
				float scl = (float)max;
				if(u == 0)
					glColor4f(0.0f,1.f,1.f,0.2f);
				else
					glColor4f(1.f,0.0f,0.f,0.25f);
				glBegin(GL_TRIANGLE_STRIP);
				for(int i=0; i < nisi; i++){
					float y1 = (float)m_isi[u][i]/scl;
					float x1 = (float)i/((float)(nisi-1));
					glVertex2f(x1*ow+ox+ow, y1*oh*0.5+oy);
					glVertex2f(x1*ow+ox+ow, oy);
				}
				glEnd();
			}
		}
		//finally, the channel. upper left hand corner.
		glColor4f(1.f, 1.f, 1.f, 0.5);
		glRasterPos2f(ox, oy + oh - 13.f*2.f/g_viewportSize[1]); //13 pixels vertical offset.
		//kearning is from the lower right hand corner.
		char buf[64];
		snprintf(buf, 64, "Ch %d", m_ch);
		glPrint(buf);
	}
	int updateTemplate(int unit){
		//called when the button is clicked.
		//must also fit the matched filter. (have a stop button here?)
		// also need to set the threshold aka aperture..  later!
		if(unit < 1 || unit > 2){
			printf("unit out of range in Channel::updateTemplate()\n");
			return false;
		}
		float aperture = 0;
		float color[3] = {0.f, 1.f, 1.f};
		if(unit == 2){color[0] = 1.f; color[1] = 0.f; color[2] = 0.f; }
		float temp[32];
		m_pcaVbo->getTemplate(temp, aperture, color);
		printf("template %d ", unit);
		for(int i=0; i<16; i++){
			m_template[unit-1][i] = temp[i+8];
			printf("%d ", (int)((temp[i+8]+0.5f) * 255));
		}
		printf("\n");
		m_mspk[unit-1].init(NULL, temp); //this will enable the annealing step.
		//old code below.
		//m_aperture[unit-1] = aperture * 255;
		//printf("m_aperture[%d][%d] = %d\n", m_ch, unit-1, (int)m_aperture[unit-1]);
		//update sorting based on new aperture.
		//m_pcaVbo->updateAperture(m_template[unit-1], aperture, color);
		//store the equivalent of the unsigned bytes actually used on the headstage.
		/*
		for(int i=0; i<16; i++){
			float r = round((m_template[unit-1][i] + 0.5f)*255.f);
			m_template[unit-1][i] = r/255.f - 0.5f;
		}
		*/
		//let's send the new data to the headstage.
		//setTemplate(m_ch, unit-1);
		setAperture(m_ch);
		return true;
	}
	void resetPca(){
		//should be called if threshold, gain
		//(or really anything else) is changed / invalidates current display.
		m_pcaVbo->reset();
		m_wfVbo->setFade(1.7);//clear it a bit quicker.
		m_usVbo->setFade(1.7);
		for(int u=0; u<2; u++){
			m_lastSpike[u] = 0;
			for(unsigned int i=0; i < sizeof(m_isi[0])/sizeof(m_isi[0][0]); i++){
				m_isi[u][i] = 0;
			}
		}
	}
	void computePca(){
		//whatever ... this can be blocking.
		double t;
		int nsamp = MIN(m_pcaVbo->m_w, m_pcaVbo->m_rows);
		if(nsamp < 32){
			printf("Channel::computePca %d (%x) samples, not enough\n", nsamp, m_pcaVbo->m_w);
			return;
		}else{
			printf("Channel::computePca  %d samples\n", nsamp);
		}
		float mean[32];
		for(int j=0; j<32; j++) mean[j] = 0.f;
		for(int i=0; i<nsamp; i++){
			for(int j=0; j<32; j++)
				mean[j] += m_pcaVbo->m_wf[i*32 + j];
		}
		for(int j=0; j<32; j++){
			mean[j] /= (float)nsamp;
		}
		//gsl is row major!
		gsl_matrix *m = gsl_matrix_alloc(nsamp, 32); //rows, columns (like matlab)
		for(int i=0; i<nsamp; i++){
			for(int j=0; j<32; j++){
				m->data[i*32 + j] = m_pcaVbo->m_wf[i*32 + j]; // - mean[j];
			}
		}
		//gsl_matrix_to_mat(m, "wavforms.mat");
		if(0){
			//method 1 - SVD.  slow.
			// I'm looking at matlab's princomp function.
			// they say S = X0' * X0 ./ (n-1), but computed using SVD.
			//columns of V seem to contain the principle components.
			gsl_matrix *x = gsl_matrix_alloc(32,32);
			gsl_matrix *v = gsl_matrix_alloc(32,32);
			gsl_vector *s = gsl_vector_alloc(32);
			gsl_vector *work = gsl_vector_alloc(32);

			gsl_linalg_SV_decomp_mod(m, x, v, s, work);

			//copy! v is untransposed and in row-major. s should be sorted descending.
			printf("pca coef!\n");
			int offset = 0;
			gsl_matrix_to_mat(v, "pca_coef.mat");
			while(s->data[offset] > 1000) offset++;
			for(int i=0; i<32; i++){
				m_pca[0][i] = v->data[i*32 + offset];
				m_pca[1][i] = v->data[i*32 + 1 + offset];
				printf("%f %f\n", m_pca[0][i],
								m_pca[1][i]);
			}
			gsl_matrix_free(m);
			gsl_matrix_free(x);
			gsl_matrix_free(v);
			gsl_vector_free(s);
			gsl_vector_free(work);
		}else{
			//method 2 - eigen decomposition.
			gsl_matrix *cov = gsl_matrix_alloc(32,32);
			t = gettime();
			gsl_blas_dgemm(CblasTrans,CblasNoTrans,1.0/nsamp,m,m,0.0,cov);
			printf("dgemm time %f siz %d\t", (double)(gettime()-t),nsamp);
			//regularize.
			for(int i=0; i<32;i++)
				cov->data[i*32+i] += 0.001;
			//gsl_matrix_to_mat(cov, "pca_cov.mat");
			//eigen decomp.
			t = gettime();
			gsl_eigen_symmv_workspace *ws = gsl_eigen_symmv_alloc(32);
			gsl_matrix *v = gsl_matrix_alloc(32,32);
			gsl_vector *d = gsl_vector_alloc(32);
			gsl_eigen_symmv(cov, d, v, ws);
			gsl_matrix_to_mat(v, "pca_v.mat");
			//the result will be unsorted. sort it, ascending.
			size_t p[2];
			gsl_sort_largest_index(p,2,d->data,1,32);
			for(int k=0; k<2; k++){
				for(int i=0; i<32; i++){
					m_pca[k][i] = v->data[p[k] + i*32] / sqrt(d->data[p[k]]);
					m_pcaScl[k] = sqrt(d->data[p[k]]);
				}
			}
			printf("eig decomp time %f\t", (double)(gettime()-t));
			gsl_matrix_free(v);
			gsl_vector_free(d);
			gsl_eigen_symmv_free(ws);
		}

		//recalculate the pca points for immediate display.
		//t = gettime();
		for(int i=0; i<nsamp; i++){
			float pca[2] = {0,0};
			for(int k=0; k<2; k++){
				for(int j=0; j<32; j++){
					pca[k] += m_pcaVbo->m_wf[i*32 + j] * m_pca[k][j];
				}
			}
			m_pcaVbo->m_f[i*6 + 0] = pca[0];
			m_pcaVbo->m_f[i*6 + 1] = pca[1];
			//m_pcaVbo->m_f[i*6 + 2] = 0.f;
			//leave whatever it used to be sorted as (color).
			//for(int k=0; k<3; k++)
			//	m_pcaVbo->m_f[i*6 + 3 + k] = 0.5f;
		}
		//printf("naive reproject %f\n", gettime()-t); //it's fast (enough).
		t = gettime();
		m_pcaVbo->m_r = 0;
		m_pcaVbo->m_w = nsamp; //force a copy-over of the whole thing.
		m_pcaVbo->copy(false,true);
		printf("copy %f\n", (double)(gettime()-t));
	}
	void spike(int unit){
		//this used for calculating ISI.
		if(unit >=0 && unit < 2){
			unsigned int b = m_lastSpike[unit]/4;
			if(b > 0 && b < sizeof(m_isi[0])/sizeof(m_isi[0][0]))
				m_isi[unit][b]++;
			m_lastSpike[unit] = 0;
		}
	}
	void isiIncr(){
		m_lastSpike[0]++;
		m_lastSpike[1]++;
	}
	int* getMF(int unit){
		return m_mspk[unit & 1].m_coefs;
	}
};

#endif
