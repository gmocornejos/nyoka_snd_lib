VORBIS = ../build/ogg_vorbis.o `pkg-config --libs vorbis vorbisfile vorbisenc`
FFTWEST = ../build/fftwest.o `pkg-config --libs fftw3`

all: decoder fftwest ifftwest pitch_filter cosft sinft bandpass clean 

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
	g++ -o cosine_transform.exe cosine_transform.o ../build/plot.o $(VORBIS) $(FFTWEST) ../build/cosft.o
	
sinft:
	g++ -c -I../include sine_transform.cpp
	g++ -o sine_transform.exe sine_transform.o ../build/plot.o $(VORBIS) $(FFTWEST) ../build/sinft.o   

whitenoise:
	g++ -c -I../include whitenoise.cpp
	g++ -o whitenoise.exe whitenoise.o ../build/noise.o ../build/plot.o $(VORBIS)

pitch_filter:
	g++ -c -I../include pitch_filter.cpp
	g++ -o pitch_filter.exe pitch_filter.o ../build/plot.o $(VORBIS) ../build/pitch_filter.o

bandpass:
	g++ -c -I../include bandpass.cpp
	g++ -o bandpass.exe bandpass.o ../build/plot.o $(VORBIS) ../build/freqfilters.o $(FFTWEST)

clean:
	rm *.o

exterm:
	rm *.exe
	rm outputdata.txt
	rm *.ogg
