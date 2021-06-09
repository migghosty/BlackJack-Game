CC = g++
CXXFLAGS = -g -Wall

OBJ = main.o Player.o Game.o
target = run

$(target): $(OBJ)
	$(CC) -o $@ $(OBJ)

main.o: Game.hpp
Player.o: Card.hpp
Game.o: Game.hpp Player.hpp Card.hpp


# if you are using windows, use the clean below
.PHONY: clean
#clean:
#	del $(target).exe $(OBJ)

# if you are using linux, use the clean below
clean:
	rm $(target) $(OBJ)
