#
# Simple development makefile
#

#
# add more flags here,
# but don't remove the "+="
#
CC = arm-cortexm3-uclinuxeabi-gcc
CFLAGS += -O2 -g -Wall #-Wsign-compare -Wfloat-equal -Wformat-security #-Werror
CPPFLAGS +=
LDFLAGS += -lm

all: game
	
game: ${OBJ}
	${CC} ${CFLAGS} game.c graphic.c graphic.h ${OBJ} -o game ${LDFLAGS}

clean:
	-rm -f game *.o

install:


.PHONY: all install clean

# end of development makefile
