#ifndef STAGE_H
#define STAGE_H

#include "../spaceship/spaceship.h"
#include "../enemy/enemy.h"


class Stage
{
public:

    Spaceship spaceship;
    Enemy enemy;

    // Member functions:
    void load_stage(int, int, int);
    void set_n_gun_type(int);
    void set_n_enemy_type(int);
    void set_n_row_of_invaders(int);
    void clear_display_frame(char ***, int, int);
    void clear_stage();
    int reload(char, char ***, int, int);
    int detect_bullet_collision(char **, int, int);


private:
    // Number of weapon types available for current stage.
    int n_gun_type;
    // Number of invader types available for current stage.
    int n_enemy_type;
    // Number of rows of invaders for current stage.
    int n_row_of_invaders;
};

#endif
