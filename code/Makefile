all: maths_prog.c libmaths.so
	gcc -Wall -Wextra -pedantic -std=c11 -o maths_prog maths_prog.c -lmaths -L.
libmaths.so: add.c add.h subtract.c subtract.h
	gcc -Wall -Wextra -pedantic -std=c11 -shared -o libmaths.so -fPIC add.c subtract.c
clean:
	rm -rf maths_prog libmaths.so