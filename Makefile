all: Src/main.cpp
	g++ -Werror Src/main.cpp Src/Game.cpp -o snake -lSDL2 -lSDL2_image -lm


.phony: clean
clean:
	rm -f snake
