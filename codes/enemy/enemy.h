#ifndef ENEMY_H
#define ENEMY_H

#include "../invader/invader.h"


class Enemy
{
public:

    Invader ** available_invaders;

    // Member functions:
    void load_enemy(int, int);
    void set_n_fire_limit(int);
    void set_n_frames_required_to_fire(int);
    void set_n_frames_required_to_move_vert(int);
    void set_n_frames_required_to_move_hor(int);
    void set_n_hits(int, int);
    void set_reload_time(int, int);
    void move();
    void fire();
    void update_bullet_position(char ***, int);
    void enemy_hit(int, int);
    void clear_enemy();
    int update_position(char ***, int);
    int all_invaders_destroyed();
    int get_y_coor_of_first_row();
    int get_n_row_of_invaders();


private:

    // Number of rows of invaders.
    int n_row_of_invaders;
    // Number of invaders per row. Default is 9.
    int n_invaders_per_row;
    // Number of invaders that fired.
    int n_fire;
    // Maximum number of invaders allowed to fire.
    int n_fire_limit;
    // Number of frames that elasped since the last fire.
    int n_frames_elasped_before_firing;
    // Number of frames that elapsed required to fire again.
    int n_frames_required_to_fire;
    // Number of frames that elasped since moving down.
    int n_frames_elasped_before_moving_vert;
    // Number of frames that elapsed required for the enemies to move down.
    int n_frames_required_to_move_vert;
    // Number of frames that elasped since the moving horizontally.
    int n_frames_elasped_before_moving_hor;
    // Number of frames that elapsed required for the enemies to move horizontally.
    int n_frames_required_to_move_hor;
    // The number of steps the enemies have taken to the right.
    int offset_x;
    // The maximum number of steps the enemies can take to the right. Default is 5.
    int offset_x_limit;
    // Which horizontal direction to move. 1 for moving right, 0 for moving left.
    int is_right = 1;
};

#endif
