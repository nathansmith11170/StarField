OBJS = StarField.c

#DEPS = MatrixGraph.h prototypes.h LTexture.h

CC = gcc

COMPILER_FLAGS = -w -g -pedantic -std=c99 $(shell sdl2-config --cflags)

LINKER_FLAGS = $(shell sdl2-config --libs) -lSDL2_gfx

OBJ_NAME = starfield

starfield: $(OBJS) $(DEPS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME) $(LINKER_FLAGS)

randomPrototype:
	$(CC) $(COMPILER_FLAGS) -o randomPrototype randomPrototype.c

clean:
	rm -f $(OBJ_NAME) randomPrototype *.o