#include <iostream>
#include <unistd.h>
#include <curses.h>
#include <future>
#include <termios.h>
#include "functions/functions.h"
#include "spaceship/spaceship.h"
#include "enemy/enemy.h"
#include "player.h"
using namespace std;


int main()
{
    char input = '0';
    const int width = 50;
    const int height = 35;

    // Allocate memory to the display frame (2D Array).
    char **frame = new char *[height];
    for (int i = 0; i < height; i++)
    {
    frame[i] = new char [width];
    }
    cout << endl;

    auto control = async(get_player_input, &input);

    while (input != 'q')
    {
        display(frame, height, width);
        sleep(1);
    }

    // Free memory allocated to the array.
    for (int i = 0; i < height; i++)
    {
    delete[] frame[i];
    }
    delete[] frame;

    return 0;
}
