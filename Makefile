objects := $(patsubst %.c,%.o,$(wildcard src/*.c))

all: $(objects)
	rm -rf bin && mkdir bin
	gcc -o bin/mfetch $(objects)

install:
	cp bin/mfetch /usr/bin
	chmod +x /usr/bin/mfetch
