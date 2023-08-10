objects := $(patsubst %.c,%.o,$(wildcard *.c))

all: $(objects)
	gcc -o mfetch $(objects)

