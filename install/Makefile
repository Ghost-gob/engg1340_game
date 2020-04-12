FLAGS = -pedantic-errors -lpthread -pthread -std=c++11
ENEMY = ../codes/enemy/*
SPACESHIP = ../codes/spaceship/*
FUNCTIONS = ../codes/functions/*
GUN = ../codes/gun/*

functions.o: $(FUNCTIONS)
	g++ $(FLAGS) -c ../codes/functions/functions.cpp

gun.o: $(GUN)
	g++ $(FLAGS) -c ../codes/gun/gun.cpp

spaceship.o: $(SPACESHIP)
	g++ $(FLAGS) -c ../codes/spaceship/spaceship.cpp

enemy.o: $(ENEMY)
	g++ $(FLAGS) -c ../codes/enemy/enemy.cpp

main.o: ../codes/main.cpp ../codes/player.h $(FUNCTIONS) $(ENEMY) $(FUNCTIONS) $(GUN)
	g++ $(FLAGS) -c $<

si_2: main.o functions.o spaceship.o enemy.o gun.o
	g++ $(FLAGS) $^ -o $@
