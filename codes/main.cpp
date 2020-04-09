#include <iostream>
#include <unistd.h>
#include <future>
#include "functions/functions.h"
#include "spaceship/spaceship.h"
#include "enemy/enemy.h"
#include "player.h"
using namespace std;


int main()
{
    // Supress echo for terminal.
    system("stty -echo");

    // Use RAW mode for terminal.
    system("stty cbreak");

    char input = '0';
    int position = 0;
    int updated_map = 0;
    const int width = 50;
    const int height = 35;

    // Initialize spaceship.
    Spaceship user_ship;
    user_ship.load_spaceship();

    // Allocate memory to the display frame (2D Array).
    char **frame = new char *[height];
    for (int i = 0; i < height; i++)
    {
    frame[i] = new char [width];
    }
    cout << endl;

    auto control = async(get_player_input, &input, &updated_map);

    cin.clear();
    while (input != 'q')
    {
        // Create empty display frame.
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                frame[i][j] = ' ';
            }
        }

        user_ship.move(input, &frame, width);
        user_ship.fill_frame(&frame, height);

        updated_map = 1;
        display(frame, height, width);
        cin.clear();
        input = '\0';
        usleep(75000);
    }

    // Free memory allocated to the array.
    for (int i = 0; i < height; i++)
    {
    delete[] frame[i];
    }
    delete[] frame;

    // Reset terminal settings
    system("stty echo");
    system("stty -cbreak");

    return 0;
}
