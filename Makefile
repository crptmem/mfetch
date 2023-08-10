objects := $(patsubst %.c,%.o,$(wildcard src/*.c))

all: $(objects)
	gcc -o bin/mfetch $(objects)

