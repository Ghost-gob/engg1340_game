#include <iostream>
#include "invader.h"
using namespace std;


// Initialize invaders with their default values.
//
// Parameters:
// (int) inv_type - Invader type (0 to 2).
// (int) y - The y-coordinate of the invader in the display frame.
//
// Return:
// (void)
void Invader::load_invader(int inv_type, int y, int x)
{
    // Default width is 5
    x_coor = x;
    y_coor = y;
    width = 5;
    bullet_direction = 1;
    current_reload_duration = -1;
    head = nullptr;

    if (inv_type == 0)
    {
        // "X-Craft" invader (high firing rate, low HP).
        shape[0] = '[';
        shape[1] = 'X';
        shape[2] = 'X';
        shape[3] = 'X';
        shape[4] = ']';
        n_hits = 5;
        reload_time = 2;
        bullet_width = 1;
        frame_elasped_limit = 0;
        type = inv_type;
        icon = 'o';
    }
    else if (inv_type == 1)
    {
        // "The Wall" invader (low firing rate, high HP).
        shape[0] = '[';
        shape[1] = '-';
        shape[2] = '-';
        shape[3] = '-';
        shape[4] = ']';
        n_hits = 25;
        reload_time = 10;
        bullet_width = 1;
        frame_elasped_limit = 0;
        type = inv_type;
        icon = 'o';
    }
    else if (inv_type == 2)
    {
        // "Mirage" invader (Drops a mirror which blocks lasers).
        shape[0] = '[';
        shape[1] = 'T';
        shape[2] = 'T';
        shape[3] = 'T';
        shape[4] = ']';
        n_hits = 10;
        reload_time = 15;
        bullet_width = 5;
        frame_elasped_limit = 0;
        type = inv_type;
        icon = '_';
    }
}


// Decrement HP of the invader.
//
// Parameters:
// (char **) - The display frame.
//
// Return:
// (void)
void Invader::hit(char **frame)
{
    // Check for bullet/laser collisions along the width of the invader.
    for (int i = 0; i < width; i++)
    {
        // Whenever a '*' is found, it means that a bullet/laser collision has occured.
        if (frame[y_coor][x_coor + i] == '*')
        {
            n_hits--;
        }
    }
}
