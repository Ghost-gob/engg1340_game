#include <iostream>
#include "gun.h"
using namespace std;


void Gun::load_gun(int type)
{
    if (type == 0)
    {
        shape[0] = '/';
        shape[1] = '|';
        shape[2] = '\\';
        head = nullptr;
        time_charge = 3;
        time_between_fire = -1;
        bullet_width = 1;
        icon = '|';
        delay = 0;
    }
    else if (type == 1)
    {
        shape[0] = '/';
        shape[1] = 'v';
        shape[2] = '\\';
        head = nullptr;
        time_charge = 16;
        time_between_fire = -1;
        bullet_width = 1;
        icon = '|';
        delay = 4;
    }
}


void Gun::fire(int x_coor)
{

    if (time_between_fire == time_charge || time_between_fire == -1)
    {
        // Reset time elasped between each fire.
        time_between_fire = 0;

        // Fire gun.
        if (head == nullptr)
        {
            head = new Bullet;
            head -> next = nullptr;
            head -> X = x_coor + 2 - bullet_width / 2;
            head -> Y = 0;
        }
        else
        {
            Bullet *currentPtr = head;

            while (currentPtr -> next != nullptr)
            {
                currentPtr = currentPtr -> next;
            }

            currentPtr -> next = new Bullet;
            currentPtr = currentPtr -> next;
            currentPtr -> X = x_coor + 2 - bullet_width / 2;
            currentPtr -> Y = 0;
            currentPtr -> next = nullptr;
        }
    }
}


void Gun::move_bullet(char ***frame, int frame_height)
{
    if (time_between_fire != time_charge)
    {
        // Increment time between each fire.
        time_between_fire++;
    }

    if (head != nullptr)
    {
        (head -> Y)++;

        if ((head -> Y) > 32)
        {
            pop_bullet();
        }

        Bullet *currentPtr = head;
        while (currentPtr != nullptr)
        {
            (currentPtr -> Y)++;

            // If the bullet reach the edge of the display, delete bullet.
            currentPtr = currentPtr -> next;
        }
    }
}


void Gun::display_bullets(char ***frame, int frame_height)
{
    // Fill display frame with  the bullet fired.
    if (head != nullptr)
    {
        Bullet *currentPtr = head;

        while (currentPtr != nullptr)
        {
            int current_pos = frame_height - 2 - (currentPtr -> Y);
            for (int i = 0; i < bullet_width; i++)
            {
                bullet_hit(frame, (currentPtr -> X) + i, current_pos);
            }
            currentPtr = currentPtr -> next;

        }
    }
}


void Gun::display_laser(char ***frame, int frame_height)
{
    static int delay_time = 0;

    if (time_between_fire != time_charge)
    {
        // Increment time between each fire.
        time_between_fire++;
    }

    if (head != nullptr)
    {
        for (int i = 0; i < frame_height - 2; i++)
        {
            laser_hit(frame, head -> X, i);
        }

        if (++delay_time == delay)
        {
            pop_bullet();
            delay_time = 0;
        }
    }
}


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


void Gun::laser_hit(char ***frame, int x, int y)
{
    if ((*frame)[y][x] != ' ')
    {
        (*frame)[y][x] = '*';
        return;
    }
    (*frame)[y][x] = icon;
}


void Gun::bullet_hit(char ***frame, int x, int y)
{
    if ((*frame)[y][x] != ' ')
    {
        (*frame)[y][x] = '*';
        pop_bullet();
        return;
    }

    (*frame)[y][x] = icon;
}
