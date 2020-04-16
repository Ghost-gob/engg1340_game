FLAGS = -pedantic-errors -lpthread -pthread -std=c++11
ENEMY = ../codes/enemy/*
SPACESHIP = ../codes/spaceship/*
FUNCTIONS = ../codes/functions/*
GUN = ../codes/gun/*
INVADER = ../codes/invader/*
STAGE = ../codes/stage/*


gun.o: $(GUN)
	g++ $(FLAGS) -c ../codes/gun/gun.cpp

invader.o: $(INVADER) $(GUN)
	g++ $(FLAGS) -c ../codes/invader/invader.cpp

spaceship.o: $(SPACESHIP) $(GUN)
	g++ $(FLAGS) -c ../codes/spaceship/spaceship.cpp

enemy.o: $(ENEMY) $(INVADER)
	g++ $(FLAGS) -c ../codes/enemy/enemy.cpp

stage.o: $(STAGE) $(ENEMY) $(SPACESHIP)
	g++ $(FLAGS) -c ../codes/stage/stage.cpp

functions.o: $(FUNCTIONS)
	g++ $(FLAGS) -c ../codes/functions/functions.cpp

main.o: ../codes/main.cpp ../codes/player.h $(FUNCTIONS) $(ENEMY) $(FUNCTIONS) $(GUN) $(INVADER) $(STAGE)
	g++ $(FLAGS) -c $<

si_2: main.o functions.o spaceship.o enemy.o gun.o invader.o stage.o
	g++ $(FLAGS) $^ -o $@
