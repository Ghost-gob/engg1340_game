#include <iostream>
#include <fstream>
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

    // PRINT HERE
}


void get_player_input(char *input, int *updated_map)
{
    while(cin >> *input)
    {
        if (*input == '6')
        {
            break;
        }
    }
}

//To update the frame with text files
void pages_fill_frame(char ***frame, char text_file[][50], int height, int width)
{
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            (*frame)[i][j] = text_file[i][j];
        }
    }
}

void open_file(char filename[], char array[][50], int height, int width)
{
    ifstream object_name;
    string line_to_print;
    //Copy home pages information from text file into an array.
    object_name.open(filename);
    if(object_name.fail())
    {
        cout << "Unable to open file" << endl;
        exit(1);
    }
    else
    {
        getline(object_name, line_to_print);
        for(int i = 0; i < height; ++i)
        {
            for(int j = 0; j < width; ++j)
            {
                array[i][j] = (line_to_print.c_str())[j];
            }
            getline(object_name, line_to_print);
        }
    }
    object_name.close();
}
