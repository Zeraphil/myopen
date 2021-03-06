#ifndef __MEMORY_H__
#define __MEMORY_H__

//memory.h -- how the memory is laid out in the blackfin.
/* BF-532 has two memory banks -
0xff904000 (B) and 0xff804000 (A)
rules for memory conflicts:  (from Analog EE-197, look it up!)
A one cycle stall is incurred during a collision of simultaneous
accesses only if the accesses are to
* the same 32-bit word polarity (address bits 2 match),
* the same 4 KB sub-bank (address bits 13 and 12 match),
	4kb = 0x1000, e.g. one bank = 0xff904000 - 0xff904fff.
* the same 16 KB half-bank (address bits 16 match),
* the same bank (address bits 21 and 20 match).
"
hence, the weights and taps should, at least, be on different sub-banks.
we put them on separate banks completely. */
/* Bank B */
/*
memory map:
	Filter coeficients A1:
	0xFF90 4000	-- read with i0. (and write, in the case of LMS).
	0	toggle step  | toggle reset (on the correct channel)
		{
	1		48		b0 b1 b2 a1 a2		bandpass biquad. may include gain up to 8.
	6		9		AGC targets, sqrt.
	7		70		AGC enable (mu).
	8		53		LMS 0					m0 increments 2 channels (below)
	9		4		LMS 1					m1 jump back to update weight,
	10		5		LMS 2						2 to 16 32b words.
	1		6		LMS 3					m2 jump forward to update channel,
	2		7		LMS 4						multiple of m0.
	3		8		LMS 5					i3 indexes a table which loads m1, m2.
	4		9		LMS 6
	5		60		LMS 7
	6		1		LMS 8
	7		2		LMS 9
	8		3		LMS 10
	9		4		LMS 11
	20		5		LMS 12
	1		6		LMS 13
	2		7		LMS 14
	3		8		LMS weight decay (16384 = none, allows you to individually disable LMS.).
	4		1		b00 b01 b02 a00 a01	-- unit 1.
	9		6		b10 b11 b12 a10 a12
	34		81		threshold unit 1
	5		2		b00 b01 b02 a00 a01	-- unit 2.
	40		7		b10 b11 b12 a10 a12
	5		92		threshold unit 2
	6		3		loadmask unit 1  (0x00100001, 0x00200002, 0x00400004, ...)
	7		4		loadmask unit 2
		} X2 (47 altogether, = A1_STRIDE)
	95	channel, 0-31

		Total (both sports): 94 + 2 = 96
		96 * 32 * 4 = 12288, 0x3000.
		end at 0xFF90 7000


	Taps/delays/data:
			read with i1, write with i2.
	0xFF80 4000
			0		x0 n-1
			1		x0 n-2
			2		y0 n-2	(note!! backwards)
			3		y0 n-1	(prefilter output -- this so we can read chan+2 easily)
			4		gain
			5 		gained sample
			6		saturated sample
			7		LMS prediction 	(write only)
			8		x1 n-1 	(unit 1)
			9		x1 n-2
		1	0		y1 n-1	x2 n-1
			1		y1 n-2	x2 n-2
			2		y2 n-1
			3		y2 n-2
			4		x1 n-1 	(unit 2)
			5		x1 n-2
			6		y1 n-1	x2 n-1
			7		y1 n-2	x2 n-2
			8		y2 n-1
			9		y2 n-2
			-- and repeat for SPORT1.
	Total: 20 * 2 * 32 ch * 32-bit words. 
	total length: 5120, 0x1400
	0xFF80 5400	end of delay buffer.

	T1: stores state, indexed by i3.
	0	m1[0]		16*4
	1	m2[0]		m0*1
	2	qs[0]		0
	3	m1[1]		15*4
	4	m2[1]		m0*2
	5	qs[1]		1
	6	m1[2]		14*4
	7	m2[2]		m0*3
	8	qs[2]		2
	9	m1[3]		13*4
	10	m2[3]		m0*4
	11	qs[3]		3
	12	m1[4]		12*4
	13	m2[4]		m0*5
	14	qs[4]		4
	15	m1[5]		11*4
	16	m2[5]		m0*6
	17	qs[5]		5

	18	sf[0]		0x0000 0000 --state flag. bits 31, 23, 15, 7 (mask 0x80808080)
	19 mp[0]		(MATCH + 32 + 0*8) --32 for 7b region, 8 for # match bytes/pkt.

	20	m1[0]		10*4
	21	m2[0]		m0*7
	22	qs[0]		0
	23	m1[1]		9*4
	24	m2[1]		m0*8
	25	qs[1]		1
	26	m1[2]		8*4
	27	m2[2]		m0*9
	28	qs[2]		2
	29	m1[3]		7*4
	30	m2[3]		m0*10
	31	qs[3]		3
	32	m1[4]		6*4
	33	m2[4]		m0*11
	34	qs[4]		4
	35	m1[5]		5*4
	36	m2[5]		m0*12
	37	qs[5]		5

	38	sf[1]		0x0000 0080 --state flag. bits 31, 23, 15, 7 (mask 0x80808080)
	39 mp[1]		(MATCH + 32 + 1*8) -- '1' this varies from 0-3.

	Total length of this buffer is determined by the three cycles it supports: 15, 6, and 16
	(15 for LMS, 6 for packet samples, 16 for state flag (and 4 for match write.)
	-- LCM: 5*3*2^4 = 240.
	This is too big; we have 0x1000 memory available.
	Each packet consumes 20 words (above), or 80 bytes, so we have space for 51 packets.
	Packets must come in multiple of 16 -- unlike LMS which can be skipped -- so
	we have space for 48 packets (3 frames), 0xf00 bytes.
	This will go through 19.2 LMS updates -- most LMS weights will be updated 19 times,
	and 1/5 will be updated 20 times.  biased, but probably ok!
*/
/** BANK B **/ //i0 accesses -- coefficients.
#define A1 				0xFF904000
// -- sizes --
#define A1_STEP		1			//should *not* change this from the client. unless I make a mistake.
#define A1_PREF		5			//units: 32bit words.
#define A1_LMS			16			//15 taps + weight decay.
#define A1_AGC			2			//4 coefs per 4 biquads.
#define A1_IIR			10			//two biquads, 5 coefs each.
// -- offsets (within stride)
#define A1_AGCS		(A1_PREF) //5
#define A1_LMSA		(A1_AGCS + A1_AGC) //7
#define A1_IIRA		(A1_LMSA + A1_LMS) //23
#define A1_UNITA		(A1_IIRA + A1_IIR) //33
#define A1_IIRB		(A1_UNITA + 1) //34
#define A1_UNITB		(A1_IIRB + A1_IIR) //44
#define A1_STRIDE 	(A1_UNITB + 3) //total: 47
#define A1_PITCH		(A1_STRIDE*2 + 2) //step and channel afterward; 96 total.

#define FP_BASE		0xFF907200 //length: 0x200, 512 bytes.
	// ** Frame pointer counts down! **
#define GCC_RESERVED 	0xFF907200 //above this GCC stomps around on.

#define W1 				0xFF804000  /** BANK A **/
#define W1_STRIDE	 	20 // see above.
						  //total length = W1_STRIDE * 2 * 32 * 4 = 5120 = 0x1400 bytes
#define T1				0xFF805400 //accessed by i3, read/write LMS & state.
#define T1_LENGTH		(48*20*4) //3840, 0xF00 -- 48 packets, each needs 20 words.


#define MATCH			0xFF806300 //256 bits, 128 channels * 2 templates.
#define MATCH_LENGTH	64    // 32 bytes, or 8 4-byte words, TWICE -
							//second half is 7-b encoded. (length: 0x40)

#define ENC_LUT		0xff806400 //256 bytes (0x100), map 8 bits -> 7 bits.
#define STATE_LUT		0xff806500 //16 32bit words, 64 bytes.

#define WFBUF			0xFF807000  //really the transmit buffer.
#define WFBUF_LEN		1024		// length 2 512 byte, 16-packet frames. (0x400)



//use the frame pointer to store local variables for fast access.
#define FP_QPACKETS		4
#define FP_ADDRESS		8  //for RX
#define FP_VALUE			12  //for RX
#define FP_TXCHAN3		16
#define FP_TXCHAN2		20
#define FP_TXCHAN1		24
#define FP_TXCHAN0		28
#define FP_TIMER			32
#define FP_MATCH			36
#define FP_SPORT0_RX		40
#define FP_SPI_TDBR		44
#define FP_FIO_FLAG_D	48
#define FP_MATCH_BASE	52 //= MATCH, defined above. write ptr= this + FP_CHAN
#define FP_MATCH_PTR7	56
#define FP_ENC_LUT_BASE	60
#define FP_STATE_LUT_BASE 64 //need this for echo flag.
#define FP_ECHO			68
#define FP_BLINK			72
#define FP_0FFF0FFF		76
#define FP_16384			80

#ifndef LO
#define LO(con32) ((con32) & 0xFFFF)
#endif
#ifndef HI
#define HI(con32) (((con32) >> 16) & 0xFFFF)
#endif

//pins.
#define STEP 			0x0100
#define MUXRESET 		0x0080  //active low; must keep it high.
#define LED_BLINK		0x0010  //blink LED.

#endif
