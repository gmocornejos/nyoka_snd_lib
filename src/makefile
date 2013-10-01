all: plot ogg_vorbis lib clean

plot:
	g++ -c plot.cpp

ogg_vorbis:
	g++ -c `pkg-config --cflags vorbis` ogg_vorbis.cpp
	
lib:
	ar rcs ../build/nyoka_snd_lib.a ogg_vorbis.o plot.o

clean:
	rm *.o
