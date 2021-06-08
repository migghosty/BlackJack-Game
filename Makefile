CC = g++
CXXFLAGS = -g -Wall

OBJ = main.o Player.o Game.o
target = run

$(target): $(OBJ)
	$(CC) -o $@ $(OBJ)

main.o: Game.hpp
Player.o: Card.hpp
Game.o: Game.hpp Player.hpp Card.hpp


.PHONY: clean
clean:
	del $(target).exe $(OBJ)