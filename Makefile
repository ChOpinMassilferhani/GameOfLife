CC ?= gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra  -std=c99 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lSDL -lm

OBJS = GameOfLife.o ./Tools/image.o ./Tools/pixel_operations.o


all:  GameOfLife

GameOfLife: ${OBJS}
	${CC} ${OBJS} ${LDLIBS} ${CPPFLAGS} ${CFLAGS}  -o $@

clean:
	${RM} *.o
	${RM} Tools/*.o
	${RM} Tools/*.d
	${RM} *.d
	${RM} GameOfLife

# END
