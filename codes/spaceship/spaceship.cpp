#include <iostream>
#include "spaceship.h"
using namespace std;


void Spaceship::load_spaceship(int n)
{
    current_gun = 0;
    n_guns = n;
    x_coor = 0;

    // Load guns into the spaceship;
    for (int i = 0; i < n_guns; i++)
    {
        available_guns[i].load_gun(i);
    }
}


void Spaceship::new_gun()
{
    available_guns[n_guns].load_gun(n_guns);
    n_guns++;
}


void Spaceship::move(char input, char ***frame, int frame_width)
{
    if (input == 'a'&& (x_coor - ship_width) > -1)
    {
        x_coor -= ship_width;
    }
    else if (input == 'd' && (x_coor + ship_width) < (frame_width - 1))
    {
        x_coor += ship_width;
    }
    else if (input == 'e')
    {
        available_guns[current_gun].fire(x_coor);
    }
    else if (input == 'c')
    {
        switch_gun();
    }
}


void Spaceship::fill_frame(char ***frame, int frame_height)
{

    // Fill display frame with body of spaceship.
    (*frame)[frame_height - 1][x_coor] = '[';
    (*frame)[frame_height - 1][x_coor + ship_width - 1] = ']';

    // Fill display frame with body of gun.
    for (int i = 0; i < 3; i++)
    {
        (*frame)[frame_height - 2][x_coor + i + 1] = available_guns[current_gun].shape[i];
    }

    // Move bullet for every turn;
    for (int i = 0; i < n_guns; i++)
    {
        if (i == 0)
        {
            // If current gun type is 0, move bullet.
            available_guns[i].move_bullet(frame, frame_height);
            available_guns[i].display_bullets(frame, frame_height);
        }
        else if (i == 1)
        {
            available_guns[i].display_laser(frame, frame_height);
        }
    }
}


void Spaceship::switch_gun()
{
    current_gun++;
    current_gun %= n_guns;
}
