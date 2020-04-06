#include <iostream>
#include <termios.h>
#include <curses.h>
#include "functions.h"
using namespace std;


void display(char **frame, int height, int width)
{
    // Print upper border.
    for (int i = 0; i < (width + 2); i++)
    {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        // Print side border for every line.
        cout << "|";
        // Print display frame
        for (int j = 0; j < width; j++)
        {
            cout << frame[i][j];
        }

        cout << "|" << endl;
    }

    // Print lower border.
    for (int i = 0; i < (width + 2); i++)
    {
        cout << "-";
    }
    cout << endl;
}


void get_player_input(char *input)
{
    while(getc(*input))
    {
        if (*input == 'q')
        {
            break;
        }
    }
}
