default:
	g++ -lSDL2 -lSDL2_image -lSDL2_mixer -fpermissive -Wall src/main.cpp -I./include -o game-00

debug:
	g++ -D DEBUG -lSDL2 -lSDL2_image -lSDL2_mixer -fpermissive -Wall src/main.cpp -I./include -o game-00
