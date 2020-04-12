#ifndef ENEMY_H
#define ENEMY_H

#include "../gun/gun.h"


class Invader : public Gun
{
public:
    char shape[5];
    void load_invader(int);


private:
    char n_hits;
};

class Enemy
{
public:
    void load_enemy();
    char ** enemies;

private:
    int max_height = 2;
    int max_width = 35;
    int n_invaders;
};

#endif
