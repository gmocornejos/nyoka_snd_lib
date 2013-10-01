all: decoder clean

decoder:
	g++ -c -I../include decoder.cpp
	g++ -o decoder.exe decoder.o ../build/plot.o ../build/ogg_vorbis.o `pkg-config --libs vorbis vorbisfile vorbisenc`

clean:
	rm *.o
