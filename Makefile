build:
	mkdir -p out
	arch -x86_64 gcc -Wall -std=c99 ./*.c -o out/game `sdl2-config --cflags --libs`
	./out/game
