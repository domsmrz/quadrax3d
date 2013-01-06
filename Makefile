


quadrax3d: game.o init.o draw.o
	gcc -o quadrax3d game.o init.o draw.o `sdl-config --libs --cflags` -lGL -lGLU

game.o: game.c init.h draw.h main_sdl.h macros.h
	gcc -W -Wall -std=gnu99 -c game.c `sdl-config --libs --cflags` -lGL -lGLU

init.o: init.c main_sdl.h
	gcc -W -Wall -std=gnu99 -c init.c `sdl-config --libs --cflags` -lGL -lGLU

draw.o: draw.c main_sdl.h macros.h
	gcc -W -Wall -std=gnu99 -c draw.c `sdl-config --libs --cflags` -lGL -lGLU
