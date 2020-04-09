#include <iostream>
#include "spaceship.h"
using namespace std;


void Spaceship::load_spaceship()
{
    current_gun = 0;
    x_coor = 0;
    ship_width = 5;
    n_guns = 1;
    available_guns[0].load_gun(0);
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
        available_guns[i].move_bullet(frame, frame_height);
        available_guns[i].display_bullets(frame, frame_height);
    }
}


    void Spaceship::switch_gun()
    {

}


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
                destroy_target(frame, (currentPtr -> X) + i, current_pos, icon);
            }
            currentPtr = currentPtr -> next;

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


void Gun::destroy_target(char ***frame, int x, int y, char icon)
{
    if ((*frame)[y][x] != ' ')
    {
        (*frame)[y][x] = '*';
        pop_bullet();
        return;
    }

    (*frame)[y][x] = icon;
}
