# not a very smart makefile -- no deps -- but works.
# depends on google protocol buffers -- not too hard to install, in debian.
# you'll need to install libatlas-base-dev for linear algebra.

DBG = false
JACK = true

CC  = gcc
CPP = g++

ifeq ($(strip $(DBG)),true)
	CFLAGS  += -g -rdynamic -DDEBUG
	LDFLAGS += -rdynamic
else
	CFLAGS += -O3
endif

ifeq ($(strip $(JACK)),true)
	CFLAGS += -DJACK
	LDFLAGS += -ljack
	GOBJS += jacksnd.o
endif

CFLAGS=-I/usr/local/include -I../common_host
CFLAGS+=  -O6
CFLAGS+= -Wall -Wcast-align -Wpointer-arith -Wshadow -Wsign-compare -Wformat=2 \
-Wno-format-y2k -Wmissing-braces -Wparentheses -Wtrigraphs \
-Wextra -pedantic -Wno-int-to-pointer-cast -std=c++11
LDFLAGS = -lGL -lGLU -lpthread -lCg -lCgGL -lgsl -lcblas -latlas -lm -lsqlite3
# if
GLIBS = gtk+-2.0 gtkglext-1.0 gtkglext-x11-1.0 protobuf
GTKFLAGS = `pkg-config --cflags $(GLIBS) `
GTKLD = `pkg-config --libs $(GLIBS) `

OBJS = main.o sock.o

GOBJS = spikes.pb.o parameters.pb.o gtkclient.o decodePacket.o headstage.o\
	gettime.o sock.o sql.o tcpsegmenter.o glInfo.o matStor.o

COBJS = convert.o decodePacket.o
COM_HDR = channel.h ../common_host/vbo.h ../common_host/cgVertexShader.h ../common_host/firingrate.h

all: gtkclient
convert: convert

%.o: %.cpp $(COM_HDR)
	g++ -c -o $@ $(CFLAGS) $(GTKFLAGS) $<

%.o: ../common_host/%.cpp $(COM_HDR)
	g++ -c -o $@ $(CFLAGS) $(GTKFLAGS) $<

spikes.pb.cc : spikes.proto
	protoc $< --cpp_out=.
	protoc $< --python_out=.

parameters.pb.cc : parameters.proto
	protoc $< --cpp_out=.
	protoc $< --python_out=.

gtkclient: $(GOBJS)
	g++ -o $@ $(GTKLD) $(LDFLAGS) -lmatio -lhdf5 $(GOBJS)

convert: $(COBJS)
	g++ -o $@ -g -Wall -lmatio -lz $(COBJS)

clean:
	rm -rf gtkclient convert *.o spikes.pb.* parameters.pb.*

wf_plot: wf_plot.c
	gcc -g -lSDL -lGL -lGLU -lglut -lpthread -lmatio -lpng -o $@ wf_plot.c

deps:
	sudo apt-get install libprotobuf-dev protobuf-compiler libgtk2.0-dev libgtkgl2.0-dev \
	libgtkglext1-dev freeglut3-dev nvidia-cg-toolkit libgsl0-dev \
	libatlas-base-dev libjack-jackd2-dev python-matplotlib python-jsonpickle python-opengl libhdf5-dev \
	libboost1.49-all-dev
	echo "make sure /usr/lib64 is in /etc/ld.so.conf.d/libc.conf"
	echo "otherwise Cg may not be found. "
