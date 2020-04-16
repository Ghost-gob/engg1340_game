#include <iostream>
#include "gun.h"
using namespace std;


// Initialize guns with their default values.
//
// Parameters:
// (int) type - Gun type (0 to 3).
// (int) y - The y-coordinate of gun in the display frame.
//
// Return:
// (void)
void Gun::load_gun(int type, int y)
{
    // bullet_direction is -1 to indicate movement of bullets upwards.
    bullet_direction = -1;
    current_reload_duration = -1;
    icon = '|';
    y_coor = y;
    head = nullptr;

    if (type == 0)
    {
        // Type 0 is the basic gattling gun.
        shape[0] = '/';
        shape[1] = '|';
        shape[2] = '\\';
        reload_time = 5;
        bullet_width = 1;
        frame_elasped_limit = 0;
    }
    else if (type == 1)
    {
        // Type 1 is the shot gun.
        shape[0] = '^';
        shape[1] = '^';
        shape[2] = '^';
        bullet_width = 3;
        frame_elasped_limit = 0;
        reload_time = 15;
    }
    else if(type == 2)
    {
        // Type 2 is the laser.
        shape[0] = '/';
        shape[1] = 'v';
        shape[2] = '\\';
        reload_time = 30;
        bullet_width = 1;
        frame_elasped_limit = 5;
    }
    else if(type == 3)
    {
        // Type 3 is the shield.
        shape[0] = 'w';
        shape[1] = '-';
        shape[2] = 'w';
        bullet_width = 5;
        frame_elasped_limit = 12;
        reload_time = 30;
    }
}


// Set reload time of the gun manually.
//
// Parameters:
// (int) type - New reload time.
//
// Return:
// (void)
void Gun::set_reload_time(int time)
{
    reload_time = time;
}


// Set number of frames the laser/shield of the gun will last.
//
// Parameters:
// (int) type - New number of frames the laser/shield of the gun will last.
//
// Return:
// (void)
void Gun::set_frame_elasped_limit(int n_frames)
{
    frame_elasped_limit = n_frames;
}


// Increments the current reload duration.
//
// Parameters:
// (void)
//
// Return:
// (void)
void Gun::increment_time()
{
    if (current_reload_duration != -1)
    {
        if (current_reload_duration == reload_time)
        {
            // Reset current reload duration once reload time is reached.
            current_reload_duration = -1;
        }
        else
        {
            // Increment current reload duration.
            current_reload_duration++;
        }
    }
}


// Move every bullet fired by 1 step in their specified direction.
//
// Parameters:
// (int) frame_height - The height of the display frame.
//
// Return:
// (void)
void Gun::move_bullet(int frame_height)
{
    if (head != nullptr)
    {
        Bullet *currentPtr;
        (head -> Y) += bullet_direction;

        if ((head -> Y) >= frame_height || (head -> Y) < 0)
        {
            // Delete bullet since it reached the edge of the display frame..
            pop_bullet();
            currentPtr = head;
        }
        else
        {
            currentPtr = head -> next;
        }

        while (currentPtr != nullptr)
        {
            (currentPtr -> Y) += bullet_direction;
            currentPtr = currentPtr -> next;
        }
    }
}


// Update position of the shield so it matches the body of the spaceship.
//
// Parameters:
// (int) x - The x-coordinate of the spaceship in the display frame.
//
// Return:
// (void)
void Gun::move_shield(int x)
{
    if (head != nullptr)
    {
        head -> X = x;
    }
}


// Load every bullet fired into the display frame.
//
// Parameters:
// (char ***) frame - The address of the display frame.
// (int) frame_height - The height of the display frame.
//
// Return:
// (void)
void Gun::display_bullets(char ***frame, int frame_height)
{
    // Indicates if the bullet has hit a target.
    int is_hit = 0;

    if (head != nullptr)
    {
        Bullet *currentPtr = head;

        while (currentPtr != nullptr)
        {
            // Indicates if the bullet has hit at least an target along its width.
            int hit;

            for (int i = 0; i < bullet_width; i++)
            {
                // To check if the bullet has hit any target along its width.
                hit = bullet_hit(frame, (currentPtr -> X) + i, (currentPtr -> Y));
                if (hit == 1)
                {
                    is_hit = 1;
                }
            }
            currentPtr = currentPtr -> next;

            if (is_hit == 1)
            {
                // Reset is_hit indicator.
                is_hit = 0;
                // Delete bullet since it has hit a target.
                pop_bullet();
            }
        }
    }
}


// Load laser fired into the display frame.
//
// Parameters:
// (char ***) frame - The address of the display frame.
// (int) frame_height - The height of the display frame.
//
// Return:
// (void)
void Gun::display_laser(char ***frame, int frame_height)
{
    // Static counter to prevent reinitialization for multiple function calls.
    // This counter indicates the number of frames the laser has lasted for.
    static int n_frames_elasped = 0;
    // Indicates if the laser has hit a target.
    int is_hit = 0;

    if (head != nullptr)
    {
        // Load laser into an entire column.
        for (int i = frame_height - 3; i >= 0; i--)
        {
            is_hit = laser_hit(frame, head -> X, i);
            if(is_hit == 1)
            {
                // Break laser since it has encountered a mirror.
                break;
            }
        }

        // Increment n_frames_elasped counter everytime the function is called.
        if (++n_frames_elasped == frame_elasped_limit)
        {
            // Reset n_frames_elasped counter since it has reached the limit.
            n_frames_elasped = 0;
            // Delete the laser.
            pop_bullet();
        }
    }
}


// Delete a bullet.
//
// Parameters:
// (void)
//
// Return:
// (void)
void Gun::pop_bullet()
{
    Bullet *tempPtr = head;

    if (head -> next != nullptr)
    {
        head = head -> next;
    }
    else
    {
        head = nullptr;
    }

    delete tempPtr;
}


// Delete all bullets. This function is called when the current stage ends.
//
// Parameters:
// (void)
//
// Return:
// (void)
void Gun::clear_bullets()
{
    if (head != nullptr)
    {
        while(head -> next != nullptr)
        {
            Bullet *tempPtr = head;
            head = head -> next;
            delete tempPtr;
        }
        delete head;
    }
}


// Fire the gun.
//
// Parameters:
// (int) x_coor - The x-coordinate of the gun in the display frame.
//
// Return:
// (int) 0 - Gun is not fired.
// (int) 1 - Gun is fired.
int Gun::fire(int x_coor)
{
    // Only fire the gun if the current reload duration is -1.
    if (current_reload_duration == -1)
    {
        // Increment current reload duration.
        current_reload_duration++;

        if (head == nullptr)
        {
            head = new Bullet;
            head -> next = nullptr;
            head -> X = x_coor;
            head -> Y = y_coor;
        }
        else
        {
            Bullet *currentPtr = head;

            // Using while loop to 'walk' to the last bullet.
            while (currentPtr -> next != nullptr)
            {
                currentPtr = currentPtr -> next;
            }

            // Initialize a new bullet at the end of the queue.
            currentPtr -> next = new Bullet;
            currentPtr = currentPtr -> next;
            currentPtr -> X = x_coor;
            currentPtr -> Y = y_coor;
            currentPtr -> next = nullptr;
        }
        return 1;
    }
    return 0;
}


// Check if the bullet has hit a target.
//
// Parameters:
// (char ***) frame - The address of the display frame.
// (int) x - The x-coordinate of the laser in the display frame.
// (int) y - The y-coordinate of the laser in the display frame.
//
// Return:
// (int) 0 - Bullet did not hit a target.
// (int) 1 - Bullet has hit a target.
int Gun::bullet_hit(char ***frame, int x, int y)
{
    // Get current character in the display frame from the coordinate specified.
    char symbol = (*frame)[y][x];

    if (symbol == '_' || symbol == 'o' || symbol == ' ')
    {
        // Current cell is empty or contains an enemy bullet.
        (*frame)[y][x] = icon;
        return 0;
    }
    else
    {
        // Current cell is a target.
        (*frame)[y][x] = '*';
        return 1;
    }
}


// Check if the laser has hit a mirror. Hitting a mirror breaks the laser.
//
// Parameters:
// (char ***) frame - The address of the display frame.
// (int) x - The x-coordinate of the laser in the display frame.
// (int) y - The y-coordinate of the laser in the display frame.
//
// Return:
// (int) 0 - Laser did not hit a mirror.
// (int) 1 - Laser has hit a mirror.
int Gun::laser_hit(char ***frame, int x, int y)
{
    // Get current character in the display frame from the coordinate specified.
    char symbol = (*frame)[y][x];

    if (symbol == '_')
    {
        // Current cell is a mirror, which breaks the laser.
        (*frame)[y][x] = '_';
        return 1;
    }
    else if(symbol == ' ' || symbol == 'o')
    {
        // Current cell is empty or contains an enemy bullet.
        (*frame)[y][x] = icon;
    }
    else
    {
        // Current cell is a target.
        (*frame)[y][x] = '*';
    }
    return 0;
}


// Load shield into the display frame.
//
// Parameters:
// (char ***) frame - The address of the display frame.
//
// Return:
// (int) 0 - The shield is not enabled.
// (int) 1 - The shield is enabled.
int Gun::display_shield(char ***frame)
{
    // Static counter to prevent reinitialization for multiple function calls.
    // This counter indicates the number of frames the shield has lasted for.
    static int n_frames_elasped = 0;

    if (head != nullptr)
    {
        for (int i = 0; i < bullet_width; i++)
        {
            (*frame)[y_coor - 1][(head -> X) + i] = '_';
        }

        // Increment n_frames_elasped counter everytime the function is called.
        if (++n_frames_elasped == frame_elasped_limit)
        {
            // Reset n_frames_elasped counter since it has reached the limit.
            n_frames_elasped = 0;
            // Delete the laser.since it expired.
            pop_bullet();
            return 0;
        }
        return 1;
    }
    return 0;
}
