<<<<<<< HEAD
all: plot ogg_vorbis fftwest noise pitch_filter lib
=======
all: plot ogg_vorbis fftwest noise sinft lib
>>>>>>> 0abe564f899140c7b705fe67c12bdab4d24763e0

plot:
	g++ -c plot.cpp

ogg_vorbis:
	g++ -c `pkg-config --cflags vorbis` ogg_vorbis.cpp

fftwest:
	g++ -c `pkg-config --cflags fftw3` fftwest.cpp

noise:
	g++ -c noise.cpp	

<<<<<<< HEAD
pitch_filter:
	g++ -c pitch_filter.cpp
=======
cosft:
	g++ -c cosft.cpp

sinft:
	g++ -c sinft.cpp
>>>>>>> 0abe564f899140c7b705fe67c12bdab4d24763e0

lib:
	mv *.o ../build/
