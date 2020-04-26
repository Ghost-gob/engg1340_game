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
#include <ctime>
using namespace std;


int main()
{
    //declare argument for time()
    time_t tt;
    struct tm * current_time;
    time (&tt);
    current_time = localtime(&tt);

    // Supress echo for terminal.
    system("stty -echo");

    // Use RAW mode for terminal.
    system("stty cbreak");

    // Initialize stage.
    Stage stage;
    // Initialize a variable to indicate current game state.
    int game_state;
    // Initialize a variable to indicate the current level.
    int stage_count = 1;
    // Initialize a variable to check if game should proceeds to next level.
    bool next_level = false;

    char input = '0';
    int position = 0;
    const int width = 50;
    const int height = 35;

    // Initiate array for Main Menu illustration.
    char main_menu[height][width];

    // Initiate array for Instruction page.
    char instructions[height][width];
    //Initiate array for Stage_1 information page.
    char stage_1[height][width];
    char stage_2[height][width];
    // Copy text from text files to arrays. (For Mainpages)
    char homepage[] = "homepage.txt", instruction_page[] = "instructions.txt", leaderBoard[] = "leaderboard.txt";
    //Copy text from text files to arrays. (For pages relating to stages information)
    char stage_1_file[] = "../In-game illustrations/Stage_1.txt";
    char stage_2_file[] = "../In-game illustrations/Stage_2.txt";
    open_file(homepage, main_menu, height, width);
    open_file(instruction_page, instructions, height, width);
    open_file(stage_1_file, stage_1, height, width);
    open_file(stage_2_file, stage_2, height, width);

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
        //No game is in progress, so print main menu
        if(next_level == false)
        {
            pages_fill_frame(&frame, main_menu, height, width);
            display(frame, height, width);
            cout << "      Game launched: " << asctime(current_time);
        }
        else
        {
            next_level = false;
            input = '1';
        }
        switch(input)
        {
            case '1':
                // Start game.
                game_state = 0;
                //
                // Keyboard input settings
                // Set new keybind. 'l' to fire.
                stage.spaceship.set_key_binds(2, 'l');
                // Set new keybind. 'k' to switch weapon.
                stage.spaceship.set_key_binds(3, 'k');
                // Set new keybind. ';' to activate shield.
                stage.spaceship.set_key_binds(4, ';');
                //
                // Setting the game attributes (difficulty) based on the current level.
                // Stage 1
                if(stage_count == 1)
                {
                    case 1:
                        // Settings for Stage 1
                        //
                        // One basic gattling gun, 1 type of enemy, 2 rows of enemy
                        stage.load_stage(1, 1, 2);
                        // Set spaceship HP to 10.
                        stage.spaceship.set_n_hits(10);
                        // Set spaceship reload time for shot gun to 5.
                        stage.spaceship.set_reload_time(0, 5);
                        // Set the reload time for enemy to 2.
                        stage.enemy.set_reload_time(0, 2);
                        // Set the hp of enemy to 5.
                        stage.enemy.set_n_hits(0, 1);
                        // Set horizontal speed of enemy.
                        stage.enemy.set_n_frames_required_to_move_hor(10);
                        //Set vertical speed of enemy.
                        stage.enemy.set_n_frames_required_to_move_vert(100);
                        // Set enemy fire limit to 3
                        stage.enemy.set_n_fire_limit(3);
                        // Set enemy fire speed.
                        stage.enemy.set_n_frames_required_to_fire(15);

                        //Display Stage 1 informations.
                        while(input != 'c')
                        {
                            stage.clear_display_frame(&frame, width, height);
                            pages_fill_frame(&frame, stage_1, height, width);
                            display(frame, height, width);
                            cin.clear();
                            input = '\0';
                            usleep(75000);
                        }
                }
                // Stage 2
                else if(stage_count == 2)
                {
                    //One basic gattling gun, 1 type of enemy, 4 rows of enemy
                    stage.load_stage(1, 1, 2);
                    // Set spaceship HP to 10.
                    stage.spaceship.set_n_hits(15);
                    // Set spaceship reload time for shot gun to 1.
                    stage.spaceship.set_reload_time(0, 2);
                    // Set the reload time for enemy
                    stage.enemy.set_reload_time(0, 2);
                    // Set the hp of enemy.
                    stage.enemy.set_n_hits(0, 10);
                    // Set horizontal speed of enemy.
                    stage.enemy.set_n_frames_required_to_move_hor(5);
                    //Set vertical speed of enemy.
                    stage.enemy.set_n_frames_required_to_move_vert(100);
                    // Set enemy fire limit to 3
                    stage.enemy.set_n_fire_limit(3);
                    // Set enemy fire speed.
                    stage.enemy.set_n_frames_required_to_fire(15);
                    while(input != 'c')
                    {
                        pages_fill_frame(&frame, stage_2, height, width);
                        display(frame, height, width);
                        cin.clear();
                        input = '\0';
                        usleep(75000);
                    }
                }
                while (input != 'm')
                {
                    stage.clear_display_frame(&frame, width, height);
                    game_state = stage.reload(input, &frame, width, height);

                    if (game_state == 1)
                    {
                        // LOSE
                        stage.clear_stage();
                        // Level status is refreshed to level 1.
                        stage_count = 1;
                        break;
                    }
                    else if(game_state == -1)
                    {
                        // WIN
                        stage.clear_stage();
                        // Proceed to the next level.
                        stage_count = stage_count + 1;
                        next_level = true;
                        break;
                    }
                    display(frame, height, width);
                    cout << "||   Life Points: " << stage.spaceship.spaceship_lifepoint() << "    ||    Current Level: " << stage_count << "    ||" << endl;
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }
                if(game_state == 0)
                    stage_count = 1;
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
