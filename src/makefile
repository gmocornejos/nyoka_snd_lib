<<<<<<< HEAD
all: plot ogg_vorbis fftwest noise pitch_filter lib
=======
<<<<<<< HEAD
all: plot ogg_vorbis fftwest noise cosft lib
=======
<<<<<<< HEAD
all: plot ogg_vorbis fftwest noise pitch_filter lib
=======
all: plot ogg_vorbis fftwest noise sinft lib
>>>>>>> 0abe564f899140c7b705fe67c12bdab4d24763e0
>>>>>>> 6ca43cfcec52ffa6976907b03247846ee21d2e3d
>>>>>>> 232ce660bdf865170df913a68dad0b5f2205308d

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
