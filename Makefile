

CFLAGS+=$(shell sdl-config --libs --cflags) -W -Wall -std=gnu99
LIBS+=$(shell sdl-config --libs --cflags) -lGL -lGLU


quadrax3d: game.o move.o init.o draw.o
	gcc -o quadrax3d game.o move.o init.o draw.o $(LIBS)

game.o: game.c move.h init.h draw.h main_sdl.h macros.h
	gcc -c game.c $(CFLAGS)

move.o: move.c macros.h
	gcc -c move.c $(CFLAGS)

init.o: init.c main_sdl.h
	gcc -c init.c $(CFLAGS)

draw.o: draw.c main_sdl.h macros.h
	gcc -c draw.c $(CFLAGS)

clean:
	rm -f quadrax3d *.o
