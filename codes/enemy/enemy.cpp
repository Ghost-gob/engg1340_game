#include <iostream>
#include <cstdlib>
#include "enemy.h"
using namespace std;


// Initialize all invaders with their default values.
//
// Parameters:
// (int) n_rows - The number of rows of invaders in the current stage.
// (int) n_types - The number of types of invaders available in the current stage.
//
// Return:
// (void)
void Enemy::load_enemy(int n_rows, int n_types)
{
    offset_x_limit = 5;
    n_fire = 0;
    n_fire_limit = 5;
    offset_x = 0;
    n_frames_required_to_move_vert = 50;
    n_frames_required_to_move_hor = 10;
    n_frames_required_to_fire = 10;
    n_frames_elasped_before_moving_vert = 0;
    n_frames_elasped_before_moving_hor = 0;
    n_frames_elasped_before_firing = 0;
    is_right = 1;
    n_invaders_per_row = 9;
    n_row_of_invaders = n_rows;

    // Dynamically allocating array to store all available invaders.
    available_invaders = new Invader * [n_rows];
    for (int i = 0; i < n_rows; i++)
    {
        available_invaders[i] = new Invader [n_invaders_per_row];
        for (int j = 0; j < n_invaders_per_row; j++)
        {
            int random_type = rand() % n_types;
            available_invaders[i][j].load_invader(random_type, i, j * 5);
        }
    }
}


// Set fire limit of all invaders.
//
// Parameters:
// (int) n - New fire limit.
//
// Return:
// (void)
void Enemy::set_n_fire_limit(int n)
{
    n_fire_limit = n;
}


// Set number of frames that is required to be elasped before firing.
//
// Parameters:
// (int) n - Number of frames that is required to be elasped before firing.
//
// Return:
// (void)
void Enemy::set_n_frames_required_to_fire(int n)
{
    n_frames_required_to_fire = n;
}


// Set number of frames that is required to be elasped before moving horizontally.
//
// Parameters:
// (int) n - Number of frames that is required to be elasped before before moving
//           horizontally
//
// Return:
// (void)
void Enemy::set_n_frames_required_to_move_hor(int n)
{
    n_frames_required_to_move_hor = n;
}


// Set number of frames that is required to be elasped before moving vertically.
//
// Parameters:
// (int) n - Number of frames that is required to be elasped before before moving
//           vertically.
//
// Return:
// (void)
void Enemy::set_n_frames_required_to_move_vert(int n)
{
    n_frames_required_to_move_vert = n;
}


// Set HP of a type of invader manually.
//
// Parameters:
// (int) type - Invader type.
// (int) n - New HP.
//
// Return:
// (void)
void Enemy::set_n_hits(int inv_type, int n)
{
    for (int i = 0; i < n_row_of_invaders; i++)
    {
        for (int j = 0; j < n_invaders_per_row; j++)
        {
            if (available_invaders[i][j].type == inv_type)
            {
                available_invaders[i][j].n_hits = n;
            }
        }
    }
}


// Set reload time of a type of invader manually.
//
// Parameters:
// (int) type - Invader type.
// (int) time - New reload time.
//
// Return:
// (void)
void Enemy::set_reload_time(int inv_type, int time)
{
    for (int i = 0; i < n_row_of_invaders; i++)
    {
        for (int j = 0; j < n_invaders_per_row; j++)
        {
            if (available_invaders[i][j].type == inv_type)
            {
                available_invaders[i][j].reload_time = time;
            }
        }
    }
}


// Move the all the invaders. This function is called for every frame elasped.
//
// Parameters:
// (void)
//
// Return:
// (void)
void Enemy::move()
{
    n_frames_elasped_before_moving_vert++;
    n_frames_elasped_before_moving_hor++;
    n_frames_elasped_before_firing++;

    if (n_frames_elasped_before_moving_hor == n_frames_required_to_move_hor)
    {
        // Move invader ship sideways once after n frames is displayed.
        if (is_right == 1)
        {
            // Move to the right.
            offset_x++;
            if (offset_x == offset_x_limit)
            {
                // Switch direction to the left once 5 steps is taken to the right,
                is_right = 0;
            }
        }
        else
        {
            // Move to the left.
            offset_x--;
            if (offset_x == 1)
            {
                // Switch direction to the right once 5 steps is taken to the left,
                is_right = 1;
            }
        }

        // Update coordinates of all invaders.
        for (int i = 0; i < n_row_of_invaders; i++)
        {
            for (int j = 0; j < n_invaders_per_row; j++)
            {

                if (is_right == 1)
                {
                    available_invaders[i][j].x_coor++;
                }
                else
                {
                    available_invaders[i][j].x_coor--;
                }
            }
        }

        // Reset number of frames that elasped.
        n_frames_elasped_before_moving_hor = 0;
    }

    if (n_frames_elasped_before_moving_vert == n_frames_required_to_move_vert)
    {
        // Move invader ship down once after n frames is displayed.
        for (int i = 0; i < n_row_of_invaders; i++)
        {
            for (int j = 0; j < n_invaders_per_row; j++)
            {
                available_invaders[i][j].y_coor++;
            }
        }

        // Reset number of frames that elasped.
        n_frames_elasped_before_moving_vert = 0;
    }

    // Increment reload time for all invaders.
    for (int i = 0; i < n_row_of_invaders; i++)
    {
        for (int j = 0; j < n_invaders_per_row; j++)
        {
            available_invaders[i][j].increment_time();
        }
    }
}


// Make all invaders fire at random once a certain number of frames have elasped.
//
// Parameters:
// (void)
//
// Return:
// (void)
void Enemy::fire()
{
    if (n_frames_elasped_before_firing == n_frames_required_to_fire)
    {
        // Reset number of frames that elasped.
        n_frames_elasped_before_firing = 0;

        // Navigate through each invader by column.
        for (int i = 0; i < n_invaders_per_row; i++)
        {
            // Start with the invader at the bottom of each column.
            for (int j = n_row_of_invaders - 1; j >= 0 ; j--)
            {
                // Check if invader is still alive.
                if (available_invaders[j][i].n_hits > 0)
                {
                    int type = available_invaders[j][i].type;

                    // Generate 1 or 0 on random to determine whether to fire or not.
                    int fire_now = rand() % 2;
                    if (fire_now == 1 && n_fire < n_fire_limit)
                    {
                        // Fire gun if indicator is 1 and fire limit is not reached.
                        n_fire++;
                        int x_coor = available_invaders[j][i].x_coor;
                        available_invaders[j][i].fire(x_coor + 2);
                    }
                    // Jump to next column.
                    break;
                }
            }
        }

        // Reset number of invaders fired.
        n_fire = 0;
    }
}


// Move and updates the position of every bullet fired in the display frame.
// This function will be called for every frame elasped.
//
// Parameters:
// (char ***) frame - The address of the display frame.
// (int) frame_height - The height of the display frame.
//
// Return:
// (void)
void Enemy::update_bullet_position(char ***frame, int frame_height)
{
    for (int i = 0; i < n_row_of_invaders; i++)
    {
        for (int j = 0; j < n_invaders_per_row; j++)
        {
            available_invaders[i][j].move_bullet(frame_height);
            available_invaders[i][j].display_bullets(frame, frame_height);
        }
    }
}


// Decrement HP of the invaders when they are hit.
//
// Parameters:
// (int) x - The x-coordinate of the collision in the display frame.
// (int) y - The y-coordinate of the collision in the display frame.
//
// Return:
// (void)
void Enemy::enemy_hit(int x, int y)
{
    for (int i = 0; i < n_row_of_invaders; i++)
    {
        for (int j = 0; j < n_invaders_per_row; j++)
        {
            int x_coor = available_invaders[i][j].x_coor;
            int y_coor = available_invaders[i][j].y_coor;

            if((x - x_coor) < 5 && (x - x_coor) > -1 && y == y_coor)
            {
                available_invaders[i][j].n_hits--;
            }
        }
    }
}


// Delete all bullet fired by all invaders and frees up memory allocated for all
// invaders. This function is called when the current stage ends.
//
// Parameters:
// (void)
//
// Return:
// (void)
void Enemy::clear_enemy()
{
    for (int i = 0; i < n_row_of_invaders; i++)
    {
        for (int j = 0; j < n_invaders_per_row; j++)
        {
            available_invaders[i][j].clear_bullets();
        }

        delete [] available_invaders[i];
    }

    delete [] available_invaders;
}


// Loads the new positions of all invaders in the display frame.
//
// Parameters:
// (char ***) frame - The address of the display frame.
// (int) frame_height - The height of the display frame.
//
// Return:
// (int) 0 - Invaders have not reached the spaceship.
// (int) 1 - Invaders have reached the spaceship.
int Enemy::update_position(char ***frame, int frame_height)
{
    int game_state = 0;

    for (int i = 0; i < n_row_of_invaders; i++)
    {
        for (int j = 0; j < n_invaders_per_row; j++)
        {
            // Check if invader is still alive.
            if (available_invaders[i][j].n_hits > 0)
            {
                int y_pos = available_invaders[i][j].y_coor;
                int x_pos = available_invaders[i][j].x_coor;

                if (y_pos == 33)
                {
                    return 1;
                }

                (*frame)[y_pos][x_pos] = available_invaders[i][j].shape[0];
                (*frame)[y_pos][x_pos + 1] = available_invaders[i][j].shape[1];
                (*frame)[y_pos][x_pos + 2] = available_invaders[i][j].shape[2];
                (*frame)[y_pos][x_pos + 3] = available_invaders[i][j].shape[3];
                (*frame)[y_pos][x_pos + 4] = available_invaders[i][j].shape[4];
            }
        }
    }
    return game_state;
}


// Checks if all invaders have been destroyed.
//
// Parameters:
// (void)
//
// Return:
// (int) 0 - All invaders have not been destroyed.
// (int) 1 - All invaders have been destroyed.
int Enemy::all_invaders_destroyed()
{
    for (int i = 0; i < n_row_of_invaders; i++)
    {
        for (int j = 0; j < n_invaders_per_row; j++)
        {
            if (available_invaders[i][j].n_hits > 0)
            {
                return 0;
            }
        }
    }
    return 1;
}


// Get the y-coordinate of the first row of invaders.
//
// Parameters:
// (void)
//
// Return:
// (int) The y-coordinate of the first row of invaders.
int Enemy::get_y_coor_of_first_row()
{
    return available_invaders[0][0].y_coor;
}


// Get the number of rows of invaders in the current stage.
//
// Parameters:
// (void)
//
// Return:
// (int) The the number of rows of invaders in the current stage.
int Enemy::get_n_row_of_invaders()
{
    return n_row_of_invaders;
}
