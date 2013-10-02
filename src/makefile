all: plot ogg_vorbis fftwest noise sinft lib

plot:
	g++ -c plot.cpp

ogg_vorbis:
	g++ -c `pkg-config --cflags vorbis` ogg_vorbis.cpp

fftwest:
	g++ -c `pkg-config --cflags fftw3` fftwest.cpp

noise:
	g++ -c noise.cpp	

cosft:
	g++ -c cosft.cpp

sinft:
	g++ -c sinft.cpp

lib:
	mv *.o ../build/
