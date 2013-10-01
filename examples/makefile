all: decoder clean

decoder:
	g++ -c `pkg-config --cflags vorbis` -I../include decoder.cpp
	g++ -o decode.exe decoder.o ../build/nyoka_snd_lib.a `pkg-config --libs vorbis`

clean:
	rm *.o
