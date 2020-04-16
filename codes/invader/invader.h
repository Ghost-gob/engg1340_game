#ifndef INVADER_H
#define INVADER_H

#include "../gun/gun.h"


class Invader : public Gun
{
public:
    // Character array to store shape of invader.
    char shape[5];
    // Number of hits the invader can take before 'dying'.
    int n_hits;
    // The x-coordinate of the invader.
    int x_coor;
    // The width of the invader. Default value is 5.
    int width;
    // The type of invader.
    int type;

    // Member functions:
    void load_invader(int, int, int);
    void hit(char **);
};

#endif
