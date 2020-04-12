#include <iostream>
#include <cstdlib>
#include "enemy.h"
using namespace std;


void Enemy::load_enemy()
{
    enemies = new char *[max_height];
    for (int i = 0; i < max_height; i++)
    {
        enemies[i] = new char [max_width];
    }

    for (int i = 0; i < max_height; i++)
    {
        for (int j = 0; j < max_width; j += 5)
        {
            int type = rand() % n_invaders;
            // enemies[i][j] = load_invader(type);
        }
    }
}


void Invader::load_invader(int type)
{

}
