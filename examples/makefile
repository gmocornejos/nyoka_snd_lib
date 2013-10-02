VORBIS = ../build/ogg_vorbis.o `pkg-config --libs vorbis vorbisfile vorbisenc`
FFTWEST = ../build/fftwest.o `pkg-config --libs fftw3`

all: decoder fftwest ifftwest cosft clean

decoder:
	g++ -c -I../include decoder.cpp
	g++ -o decoder.exe decoder.o ../build/plot.o $(VORBIS)

fftwest:
	g++ -c -I../include fftwest.cpp
	g++ -o fftwest.exe fftwest.o ../build/plot.o $(VORBIS) $(FFTWEST)	

ifftwest:
	g++ -c -I../include ifftwest.cpp
	g++ -o ifftwest.exe ifftwest.o ../build/plot.o $(VORBIS) $(FFTWEST) 

cosft:
	g++ -c -I../include cosine_transform.cpp
	g++ -o cosine_transform.exe cosine_transform.o ../build/plot.o $(VORBIS) ../build/cosft.o
	
sinft:
	g++ -c -I../include sine_transform.cpp
	g++ -o sine_transform.exe sine_transform.o ../build/plot.o $(VORBIS) ../build/sinft.o   

whitenoise:
	g++ -c -I../include whitenoise.cpp
	g++ -o whitenoise.exe whitenoise.o ../build/noise.o ../build/plot.o $(VORBIS)

clean:
	rm *.o

exerm:
	rm *.exe
	rm outputdata.txt
	rm *.ogg
