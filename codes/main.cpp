#include <iostream>
#include <unistd.h>
#include <future>
#include <fstream>
#include "functions/functions.h"
#include "spaceship/spaceship.h"
#include "enemy/enemy.h"
#include "player.h"
#include "gun/gun.h"
#include "invader/invader.h"
#include "stage/stage.h"
using namespace std;


int main()
{
    // Supress echo for terminal.
    system("stty -echo");

    // Use RAW mode for terminal.
    system("stty cbreak");

    // Initialize stage.
    Stage stage;
    // Initialize a variable to indicate current game state.
    int game_state;

    char input = '0';
    int position = 0;
    const int width = 50;
    const int height = 35;

    // Initiate array for Main Menu illustration.
    char main_menu[height][width], instructions[height][width];

    // Copy text from text files to arrays.
    char homepage[] = "homepage.txt", instruction_page[] = "instructions.txt", leaderBoard[] = "leaderboard.txt";
    open_file(homepage, main_menu, height, width);
    open_file(instruction_page, instructions, height, width);

    // Allocate memory to the display frame (2D Array).
    char **frame = new char *[height];
    for (int i = 0; i < height; i++)
    {
    frame[i] = new char [width];
    }
    cout << endl;

    auto control = async(get_player_input, &input);
    cin.clear();

    //This is where the main game starts
    while(input != '6')
    {
        // Create empty display frame.
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                frame[i][j] = ' ';
            }
        }
        pages_fill_frame(&frame, main_menu, height, width);
        display(frame, height, width);
        switch(input)
        {
            case '1':
                // Start game.
                game_state = 0;
                stage.load_stage(4, 3, 2);

                // Set new keybind. 'l' to fire.
                stage.spaceship.set_key_binds(2, 'l');
                // Set spaceship HP to 30.
                stage.spaceship.set_n_hits(30);
                // Set spaceship reload time for shot gun to 1.
                stage.spaceship.set_reload_time(1, 1);

                // Set enemy fire limit to 3
                stage.enemy.set_n_fire_limit(3);
                // Set type 0 invader hp to 10
                stage.enemy.set_n_hits(0, 10);

                while (input != 'm')
                {
                    stage.clear_display_frame(&frame, width, height);
                    game_state = stage.reload(input, &frame, width, height);

                    if (game_state == 1)
                    {
                        // LOSE
                        stage.clear_stage();
                        break;
                    }
                    else if(game_state == -1)
                    {
                        // WIN
                        stage.clear_stage();
                        break;
                    }

                    display(frame, height, width);
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }
                break;
            case '2':
                //load_saved_game();
                break;
            case '3':
                pages_fill_frame(&frame, instructions, height, width);
                display(frame, height, width);
                while(input != 'm')
                {

                }
                break;
            case '4':
                //show_leaderboard();
                break;
            case '5':
                //show_credits();
                break;
        }
        cin.clear();
        input = '\0';
        usleep(75000);
    }

    //indicating game has quitted.
    cout << "You successfully exit from the game. Hope you had fun!" << endl;
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
