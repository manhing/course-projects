PROGS := game

all: $(PROGS)


game: Feature.o Animation.o Player.o Item.o Room.o Game.o 
	g++ -g Feature.o Player.o Item.o Room.o Animation.o Game.o -o game -lcurses

Feature.o: Feature.cpp Feature.hpp
	g++ -c Feature.cpp

Animation.o: Animation.cpp Animation.hpp
	g++ -c Animation.cpp

Player.o: Player.cpp Player.hpp
	g++ -c Player.cpp

Item.o: Item.cpp Item.hpp
	g++ -c Item.cpp

Room.o: Room.cpp Room.hpp
	g++ -c Room.cpp

Game.o: Game.cpp
	g++ -c Game.cpp


clean:
	rm -f $(PROGS) *.o *~
