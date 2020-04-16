#include <iostream>
#include "stage.h"
using namespace std;


// Initialize stage.
//
// Parameters:
// (int) n_guns - Number of weapon types available for current stage.
// (int) n_enemy - Number of invader types available for current stage.
//
// Return:
// (void)
void Stage::load_stage(int n_guns, int n_enemy, int n_rows)
{
    n_gun_type = n_guns;
    n_enemy_type = n_enemy;
    n_row_of_invaders = n_rows;

    spaceship.load_spaceship(n_guns);
    enemy.load_enemy(n_rows, n_enemy);

    // TEST...
    spaceship.set_key_binds(2, 'l');
    spaceship.set_n_hits(30);
    spaceship.set_reload_time(1, 1);
}


// Set number of weapon types available for current stage manually.
//
// Parameters:
// (int) n - The number of weapon types available for current stage.
//
// Return:
// (void)
void Stage::set_n_gun_type(int n)
{
    n_gun_type = n;
}


// Set number of invader types available for current stage manually.
//
// Parameters:
// (int) n - The number of invader types available for current stage.
//
// Return:
// (void)
void Stage::set_n_enemy_type(int n)
{
    n_enemy_type = n;
}


// Set number of rows of invaders available for current stage manually.
//
// Parameters:
// (int) n - The number of rows of invaders available for current stage.
//
// Return:
// (void)
void Stage::set_n_row_of_invaders(int n)
{
    n_row_of_invaders = n;
}


// Empty the display frame.
//
// Parameters:
// (char ***) frame - The address of the display frame.
// (int) frame_width - The width of the display frame.
// (int) frame_height - The height of the display frame.
//
// Return:
// (void)
void Stage::clear_display_frame(char ***frame, int frame_width, int frame_height)
{
    for (int i = 0; i < frame_height; i++)
    {
        for (int j = 0; j < frame_width; j++)
        {
            (*frame)[i][j] = ' ';
        }
    }
}


// Free all dynamic memory allocated for the spaceship and enemies.
//
// Parameters:
// (void)
//
// Return:
// (void)
void Stage::clear_stage()
{
    spaceship.clear_spaceship();
    enemy.clear_enemy();
}


// Loads objects in the display frame.
//
// Parameters:
// (char ***) frame - The address of the display frame.
// (int) frame_width - The width of the display frame.
// (int) frame_height - The height of the display frame.
//
// Return:
// (int) 0 - Indicates continue game.
// (int) 1 - Indicates player has lost.
// (int) -1 - Indicates player has won.
int Stage::reload(char input, char ***frame, int frame_width, int frame_height)
{
    // State of the game.
    int game_state = 0;
    spaceship.move(input, frame_width);
    enemy.move();
    enemy.fire();

    game_state = enemy.update_position(frame, frame_height);
    if (game_state == 1)
    {
        // Invaders have reached the spaceship.
        return 1;
    }
    spaceship.update_position(frame, frame_height);

    enemy.update_bullet_position(frame, frame_height);
    spaceship.update_bullet_position(frame, frame_height);

    // Check for projectile impacts
    game_state = detect_bullet_collision(*frame, frame_width, frame_height);

    return game_state;
}


// Checks for projectile(bullet) collisions.
//
// Parameters:
// (char ***) frame - The address of the display frame.
// (int) frame_width - The width of the display frame.
// (int) frame_height - The height of the display frame.
//
// Return:
// (int) 0 - Indicates continue game.
// (int) 1 - Indicates player has lost.
// (int) -1 - Indicates player has won.
int Stage::detect_bullet_collision(char **frame, int frame_width, int frame_height)
{
    int start = enemy.get_y_coor_of_first_row();
    int n_row_of_invaders = enemy.get_n_row_of_invaders();
    int x = spaceship.get_x_coor();
    int game_state = 0;

    // Begin checking at the first row of invaders.
    for (int i = start; i < frame_height - 2; i++)
    {
        if (i == start + n_row_of_invaders)
        {
            // Break loop when all rows of invaders have been checked.
            break;
        }

        for (int j = 0; j < frame_width; j++)
        {
            // '*' indicates projectile impact.
            if (frame[i][j] == '*')
            {
                enemy.enemy_hit(j, i);
            }
        }
    }

    // Check if all invaders have been destroyed.
    if (enemy.all_invaders_destroyed() == 1)
    {
        return -1;
    }

    // Check if spaceship has been hit along its width.
    for (int i = 0; i < frame_width; i++)
    {
        if (frame[33][i] == '*' || frame[34][i] == '*')
        {
            game_state = spaceship.spaceship_hit(i);
        }
    }

    return game_state;
}
