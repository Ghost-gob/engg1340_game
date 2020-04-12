#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../gun/gun.h"

class Spaceship
{
public:
    void load_spaceship(int);
    void move(char, char ***, int);
    void fill_frame(char ***, int);
    void new_gun();
    void switch_gun();

private:
    int x_coor;
    int ship_width = 5;
    int n_guns;
    int current_gun;
    Gun available_guns[3];
};

#endif
