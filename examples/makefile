VORBIS = ../build/ogg_vorbis.o `pkg-config --libs vorbis vorbisfile vorbisenc`
FFTWEST = ../build/fftwest.o `pkg-config --libs fftw3`

all: decoder fftwest ifftwest pitch_filter clean

decoder:
	g++ -c -I../include decoder.cpp
	g++ -o decoder.exe decoder.o ../build/plot.o $(VORBIS)

fftwest:
	g++ -c -I../include fftwest.cpp
	g++ -o fftwest.exe fftwest.o ../build/plot.o $(VORBIS) $(FFTWEST)	

ifftwest:
	g++ -c -I../include ifftwest.cpp
	g++ -o ifftwest.exe ifftwest.o ../build/plot.o $(VORBIS) $(FFTWEST) 

whitenoise:
	g++ -c -I../include whitenoise.cpp
	g++ -o whitenoise.exe whitenoise.o ../build/noise.o ../build/plot.o $(VORBIS)

pitch_filter:
	g++ -c -I../include pitch_filter.cpp
	g++ -o pitch_filter.exe pitch_filter.o ../build/plot.o $(VORBIS) ../build/pitch_filter.o

clean:
	rm *.o

exerm:
	rm *.exe
	rm outputdata.txt
	rm *.ogg
