all: plot ogg_vorbis fftwest noise pitch_filter lib

plot:
	g++ -c plot.cpp

ogg_vorbis:
	g++ -c `pkg-config --cflags vorbis` ogg_vorbis.cpp

fftwest:
	g++ -c `pkg-config --cflags fftw3` fftwest.cpp

noise:
	g++ -c noise.cpp	

pitch_filter:
	g++ -c pitch_filter.cpp

cosft:
	g++ -c cosft.cpp

sinft:
	g++ -c sinft.cpp

lib:
	mv *.o ../build/
