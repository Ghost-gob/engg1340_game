FLAGS = -pedantic-errors -lpthread -pthread -std=c++11
ENEMY = ../codes/enemy/*
SPACESHIP = ../codes/spaceship/*
FUNCTIONS = ../codes/functions/*

functions.o: $(FUNCTIONS)
	g++ $(FLAGS) -c ../codes/functions/functions.cpp

spaceship.o: $(SPACESHIP)
	g++ $(FLAGS) -c ../codes/spaceship/spaceship.cpp

enemy.o: $(ENEMY)
	g++ $(FLAGS) -c ../codes/enemy/enemy.cpp

main.o: ../codes/main.cpp ../codes/player.h $(FUNCTIONS) $(ENEMY) $(FUNCTIONS)
	g++ $(FLAGS) -c $<

si_2: main.o functions.o spaceship.o enemy.o
	g++ $(FLAGS) $^ -o $@
