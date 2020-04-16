#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../gun/gun.h"


class Spaceship
{
public:
    // Member functions:
    void load_spaceship(int);
    void set_key_binds(int, char);
    void set_n_hits(int);
    void set_reload_time(int, int);
    void set_frame_elasped_limit(int, int);
    void move(char, int);
    void update_position(char ***, int);
    void update_bullet_position(char ***, int);
    void switch_gun();
    void clear_spaceship();
    int get_x_coor();
    int spaceship_hit(int);

private:
    // x and y coordinates of the spaceship
    int x_coor, y_coor;
    // Number of hits the spaceship can take before losing.
    int n_hits;
    // Width of the ship. Default value is 5.
    int ship_width;
    // Number of gun types available.
    int n_guns;
    // The current gun.
    int current_gun;
    // The the shield is activated, firing will be disabled.
    int firing_disabled;
    // Gun array to store all available guns.
    Gun available_guns[4];

    // Key binds. Default:
    // a - Strafe left
    // d - Strafe right
    // e - Fire
    // c - Switch weapons(guns)
    // p - Enable shield
    char key_binds[5] = {'a', 'd', 'e', 'c', 'p'};
};

#endif
