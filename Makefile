CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99
LIBS := -lSDL2 -lSDL2_image -lSDL2_ttf
OUTPUT := run.out
INPUT := $(wildcard src/*.c)

default: $(INPUT)
	$(CC) $(CFLAGS) $(INPUT) -o $(OUTPUT)  $(LIBS)

clean:
	rm -f *.out
