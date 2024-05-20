build:
	g++ -Wall src/*.cpp -lSDL2 -o game
run:
	./game
clean:
	rm game
