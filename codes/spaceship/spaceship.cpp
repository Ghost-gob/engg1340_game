#include <iostream>
#include "spaceship.h"
using namespace std;


// Initialize spaceship with its default values.
//
// Parameters:
// (int) n - The number of gun types available to the user at the current stage.
//
// Return:
// (void)
void Spaceship::load_spaceship(int n)
{
    // Default ship width is 5.
    ship_width = 5;
    current_gun = 0;
    x_coor = 0;
    y_coor = 33;
    n_hits = 3;
    firing_disabled = 0;
    n_guns = n;

    // Load guns into the spaceship;
    for (int i = 0; i < n_guns; i++)
    {
        available_guns[i].load_gun(i, y_coor);
    }
}


// Set key bind to control the movement of the spaceship.
//
// Parameters:
// (int) action - The key bind of the corresponding action to be changed. 0 to
//                strafe left, 1 to strafe right, 2 to fire, 3 to switch weapons.
//                4 to enable shield.
// (char) input - New character to be used as key bind
//
// Return:
// (void)
void Spaceship::set_key_binds(int action, char input)
{
    key_binds[action] = input;
}


// Set HP of spaceship.
//
// Parameters:
// (int) n - The new HP value.
//
// Return:
// (void)
void Spaceship::set_n_hits(int n)
{
    n_hits = n;
}


// Set reload time for a specified gun.
//
// Parameters:
// (int) type - The type of gun.
// (int) time - The new reload time.
//
// Return:
// (void)
void Spaceship::set_reload_time(int type, int time)
{
    available_guns[type].set_reload_time(time);
}


// Set number of frames the projectile will last for a specified gun.
//
// Parameters:
// (int) type - The type of gun.
// (int) frames - The number of frames the projectile will last.
//
// Return:
// (void)
void Spaceship::set_frame_elasped_limit(int type, int frames)
{
    available_guns[type].set_frame_elasped_limit(frames);
}


// Control the spacehip depending on user input This function is called for
// every frame elasped.
//
// Parameters:
// (int) input - The input from the user.
// (int) frame_width - The width of the display frame.
//
// Return:
// (void)
void Spaceship::move(char input, int frame_width)
{
    if (input == key_binds[0] && (x_coor - ship_width) > -1)
    {
        // Move spaceship to the left if the edge of the display frame is not reached.
        x_coor -= ship_width;
    }
    else if (input == key_binds[1] && (x_coor + ship_width) < (frame_width - 1))
    {
        // Move spaceship to the right if the edge of the display frame is not reached.
        x_coor += ship_width;
    }
    else if (input == key_binds[2])
    {
        int x = x_coor;
        int bullet_width = available_guns[current_gun].bullet_width;

        // Check if shield is up. If yes, do nothing. Else, proceed to fire.
        if (firing_disabled == 0)
        {
            // Adjust x-coordinate of the bullet fired depending on its width.
            if (bullet_width == 3)
            {
                x += 1;
            }
            else if(bullet_width == 1)
            {
                x += 2;
            }
            available_guns[current_gun].fire(x);
        }
    }
    else if (input == key_binds[3])
    {
        // Switch weapon.
        switch_gun();
    }
    else if (input == key_binds[4])
    {
        // Only switch to shield if available.
        if (n_guns == 4 && firing_disabled == 0)
        {
            int temp_gun = current_gun;
            current_gun = 3;
            available_guns[current_gun].fire(x_coor);
            // Switch back to original weapon.
            current_gun = temp_gun;
        }
    }

    // Increment reload time for all available_guns on the spaceship.
    for (int i = 0; i < n_guns; i++)
    {
        available_guns[i].increment_time();
    }
}


// Loads the new position of the spacehip in the display frame.
//
// Parameters:
// (char ***) frame - The address of the display frame.
// (int) frame_height - The height of the display frame.
//
// Return:
// (void)
void Spaceship::update_position(char ***frame, int frame_height)
{
    // Fill display frame with body of spaceship.
    (*frame)[frame_height - 1][x_coor] = '[';
    (*frame)[frame_height - 1][x_coor + ship_width - 1] = ']';

    // Fill display frame with body of its guns.
    for (int i = 0; i < 3; i++)
    {
        (*frame)[frame_height - 2][x_coor + i + 1] = available_guns[current_gun].shape[i];
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
void Spaceship::update_bullet_position(char ***frame, int frame_height)
{
    for (int i = 0; i < n_guns; i++)
    {
        if (i == 0 || i == 1)
        {
            // Move and load bullets in the display frame for gun type 0 and 1.
            available_guns[i].move_bullet(frame_height);
            available_guns[i].display_bullets(frame, frame_height);
        }
        else if (i == 2)
        {
            // Move and load laser in the display frame for gun type 2.
            available_guns[i].display_laser(frame, frame_height);
        }
        else if (i == 3)
        {
            // Move the shield to match the position of the spacehip.
            available_guns[i].move_shield(x_coor);
            // If shield is enabled, disable all firing abilities.
            firing_disabled = available_guns[i].display_shield(frame);
        }
    }
}


// Switch the current equipped weapon (gun).
//
// Parameters:
// (void)
//
// Return:
// (void)
void Spaceship::switch_gun()
{
    current_gun++;
    current_gun %= n_guns;
    if (current_gun == 3)
    {
        // Reset current weapon to 1 if the current weapon is a shield.
        current_gun = 0;
    }
}


// Delete all bullet fired by the spaceship. This function is called when the
// current stage ends.
//
// Parameters:
// (void)
//
// Return:
// (void)
void Spaceship::clear_spaceship()
{
    for (int i = 0; i < n_guns; i++)
    {
        available_guns[i].clear_bullets();
    }
}


// Get x-coordinate of spaceship in the display frame..
//
// Parameters:
// (void)
//
// Return:
// (int) The x-coordinate of the spaceship in the display frame.
int Spaceship::get_x_coor()
{
    return x_coor;
}


// Decrement HP of spaceship when it is hit.
//
// Parameters:
// (int) x - The x-coordinate of the collision in the display frame.
//
// Return:
// (int) 0 - Spaceship HP still above 0, continue game.
// (int) 1 - Spaceship HP reaches 0, lose game.
int Spaceship::spaceship_hit(int x)
{
    // Check shield is up. If yes, do nothing.
    if (firing_disabled == 0)
    {
        if ((x - x_coor) < 5 && (x - x_coor) > -1)
        {
            n_hits--;
        }
    }

    // When n_hits reaches 0, return 1 to end the game
    if (n_hits < 1)
    {
        return 1;
    }
    return 0;
}

// To return the value of the current lifepoint of space ship.
//
// Return:
// (int) number of n_hits.
int Spaceship::spaceship_lifepoint()
{
    return n_hits;
}
