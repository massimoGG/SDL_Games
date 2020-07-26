main: main.c
	gcc -o main main.c gfx.c net.c -lSDL2 -lm

clean:
	rm main
