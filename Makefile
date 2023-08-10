objects := $(patsubst %.c,%.o,$(wildcard src/*.c))

all: $(objects)
	gcc -o mfetch $(objects)

