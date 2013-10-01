all: plot ogg_vorbis lib

plot:
	g++ -c plot.cpp

ogg_vorbis:
	g++ -c `pkg-config --cflags vorbis` ogg_vorbis.cpp
	
lib:
	mv *.o ../build/
