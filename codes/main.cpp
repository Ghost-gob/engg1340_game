#include <iostream>
#include <unistd.h>
#include <future>
#include <fstream>
#include <ctime>
#include <string>
#include "functions/functions.h"
#include "spaceship/spaceship.h"
#include "enemy/enemy.h"
#include "player.h"
#include "gun/gun.h"
#include "invader/invader.h"
#include "stage/stage.h"
using namespace std;

// Define a structure that stores the details of the players.
struct Player_details
{
    string player_name;
    int storymode_level;
    int storymode_timespent;
    bool bonusmode_status;
    bool story_mode_status;
};

int main()
{
    // A variable for pausing the asynchronous function.
    int key_in = 0;
    // To get the current calendar time.
    // Reference: https://www.geeksforgeeks.org/c-program-print-current-day-date-time/
    time_t timevariable;
    struct tm * current_time;
    time (&timevariable);
    current_time = localtime(&timevariable);

    // Open new terminal window with specified dimensions.
    system("resize -s 39 52");
    system("stty rows 39");
    system("stty columns 52");
    // Supress echo for terminal.
    system("stty -echo");

    // Use RAW mode for terminal.
    system("stty cbreak");

    // Initialize stage.
    Stage stage;
    // Initialize a variable to indicate current game state.
    int game_state;
    //Initialize a variable to track the number of frames taken by players to finish 10 story mode levels.
    int number_of_frames_record;
    // Initialize a variable to indicate the current level.
    int stage_count_story_mode = 1;
    int stage_count_bonus_mode = 1;
    // Initialize a variable to check if game should proceeds to next level.
    bool next_level = false;
    // Variable to check if the "Story Mode" has been finished.
    bool Story_mode_finished;
    // Variable to check if the "Bonus Mode" has been unlocked.
    bool Bonus_mode_unlocked = false;

    char input = '0';
    int position = 0;
    const int width = 50;
    const int height = 35;
    // Set maximum number of Players that the game can save to 30.
    const int max_players = 30;

    // Allocate memory to the display frame (2D Array).
    char **frame = new char *[height];
    for (int i = 0; i < height; i++)
    {
        frame[i] = new char [width];
    }

    // READ SAVED FILE (BEGIN)
    // Insert the details of players to an array of structures and insert their names to a 2d array for printing.
    int number_of_saved_players = 0;
    string line_input;
    // Initiate a dynamic array of structures to store the details of players.
    Player_details * players_gamestatus_array = new Player_details[max_players];
    char savefile_file[] = "../saves/savefile.txt";
    char savefile[height][width];
    ifstream fin;
    fin.open(savefile_file);
    if(fin.fail())
    {
        cout << "Unable to open file." << endl;
        // Reset terminal settings
        system("stty echo");
        system("stty -cbreak");
        exit(1);
    }
    else
    {
        int blankspace = 0;
        string name;
        // Load the savefile.txt into the 2D array "savefile" for printing.
        while(fin >> players_gamestatus_array[number_of_saved_players].player_name)
        {
            name = players_gamestatus_array[number_of_saved_players].player_name;
            blankspace = width - name.length();
            for(int i = 0; i < blankspace; ++i)
                name = name + ' ';
            for(int j = 0; j < width; ++j)
            {
                savefile[number_of_saved_players][j] = (name.c_str())[j];
            }
            fin >> players_gamestatus_array[number_of_saved_players].storymode_level >>  players_gamestatus_array[number_of_saved_players].storymode_timespent >> players_gamestatus_array[number_of_saved_players].bonusmode_status >> players_gamestatus_array[number_of_saved_players].story_mode_status;
            number_of_saved_players++;
        }
    }

    for(int i = number_of_saved_players; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            savefile[i][j] = ' ';
        }
    }
    fin.close();
    string bottomline_1 = "Please insert your name and press enter.          ";
    string bottomline_2 = "If name unavailable, type any key and press enter.";
    string bottomline_3 = "to return to main menu.                           ";
    // Insert bottomline_1
    for(int i = 0; i < 50; ++i)
    {
        savefile[32][i] = (bottomline_1.c_str())[i];
        savefile[33][i] = (bottomline_2.c_str())[i];
        savefile[34][i] = (bottomline_3.c_str())[i];
    }
    // READ SAVED FILE (END)

    // Sorting the players_gamestatus_array based on the number_of_frames_record (ascending order).
    for(int i = 0; i < number_of_saved_players - 1; i++)
    {
        for(int j = 0; j < number_of_saved_players - i - 1; j++)
        {
            if(players_gamestatus_array[j].storymode_timespent > players_gamestatus_array[j+1].storymode_timespent)
            {
                swap(players_gamestatus_array[j].storymode_timespent, players_gamestatus_array[j+1].storymode_timespent);
                swap(players_gamestatus_array[j].player_name, players_gamestatus_array[j+1].player_name);
                swap(players_gamestatus_array[j].storymode_level, players_gamestatus_array[j+1].storymode_level);
                swap(players_gamestatus_array[j].bonusmode_status, players_gamestatus_array[j+1].bonusmode_status);
                swap(players_gamestatus_array[j].story_mode_status, players_gamestatus_array[j+1].story_mode_status);
            }
        }
    }

    // Creating Leaderboard array for printing
    char leaderboard[height][width];
    char word[] = "LeaderBoard";
    //Initiate an array with blank spaces.
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            leaderboard[i][j] = ' ';
    // Inserting the word "LeaderBoard"
    for(int i = 0; i < 11; i++)
        leaderboard[10][18+i] = word[i];
    //Inserting top 5 players' name and time spent for completing story mode.
    int j = 0;
    int number_of_players_printed = 0;
    while(number_of_players_printed < 5 && j < number_of_saved_players)
    {
        // Only consider players that finished 10 levels in bonus mode.
        if(players_gamestatus_array[j].story_mode_status == 1)
        {
            //Print top scorer's Name and Time Spent.
            int starting_index = 0;
            leaderboard[11][18] = '1', leaderboard[12][18] = '2', leaderboard[13][18] = '3', leaderboard[14][18] = '4', leaderboard[15][18] = '5';
            leaderboard[11][19] = ')', leaderboard[12][19] = ')', leaderboard[13][19] = ')', leaderboard[14][19] = ')', leaderboard[15][19] = ')';
            while(players_gamestatus_array[j].player_name[starting_index] != '\0')
            {
                leaderboard[11+number_of_players_printed][20+starting_index] = players_gamestatus_array[j].player_name[starting_index];
                starting_index++;
            }
            starting_index++;
            int temp = 0;
            while((to_string(players_gamestatus_array[j].storymode_timespent/12))[temp] != '\0')
            {
                leaderboard[11+number_of_players_printed][20+starting_index] = (to_string(players_gamestatus_array[j].storymode_timespent/12))[temp];
                starting_index++;
                temp++;
            }
            number_of_players_printed++;
        }
        j++;
    }

    // LOAD ILLUSTRATION FILES (BEGIN)
    // Initiate array for Main Menu illustration.
    char main_menu_locked[height][width];
    char main_menu_unlocked[height][width];
    // Initiate array for Instruction page.
    char instructions[height][width];
    // Initiate array for all the information pages.
    char stage_1[height][width];
    char stage_2[height][width];
    char stage_3[height][width];
    char stage_4[height][width];
    char stage_5[height][width];
    char stage_6[height][width];
    char stage_7[height][width];
    char stage_8[height][width];
    char stage_9[height][width];
    char stage_10[height][width];
    char stage_bonus[height][width];
    char stage_completed[height][width];
    char game_over_1[height][width];
    char game_over_2[height][width];
    char story_mode_completed[height][width];

    // Store file name that store the illustrations into arrays (For Mainpages)
    char homepage_locked[] = "../In-game_illustrations/homepage(locked).txt";
    char homepage_unlocked[] = "../In-game_illustrations/homepage(unlocked).txt";
    char instruction_page[] = "../In-game_illustrations/instructions.txt";
    // Store file name that store the illustrations as c-string (For pages relating to stages information)
    char stage_1_file[] = "../In-game_illustrations/Stage_1.txt";
    char stage_2_file[] = "../In-game_illustrations/Stage_2.txt";
    char stage_3_file[] = "../In-game_illustrations/Stage_3.txt";
    char stage_4_file[] = "../In-game_illustrations/Stage_4.txt";
    char stage_5_file[] = "../In-game_illustrations/Stage_5.txt";
    char stage_6_file[] = "../In-game_illustrations/Stage_6.txt";
    char stage_7_file[] = "../In-game_illustrations/Stage_7.txt";
    char stage_8_file[] = "../In-game_illustrations/Stage_8.txt";
    char stage_9_file[] = "../In-game_illustrations/Stage_9.txt";
    char stage_10_file[] = "../In-game_illustrations/Stage_10.txt";
    char stage_bonus_file[] = "../In-game_illustrations/Stage_Bonus.txt";
    char stage_completed_file[] = "../In-game_illustrations/Stage_completed.txt";
    char game_over_1_file[] = "../In-game_illustrations/Game_over_1.txt";
    char game_over_2_file[] = "../In-game_illustrations/Game_over_2.txt";
    char story_mode_completed_file[] = "../In-game_illustrations/Story_mode_completed.txt";

    //Copy text in text files to array for Mainpages.
    open_file(homepage_locked, main_menu_locked, height, width);
    open_file(homepage_unlocked, main_menu_unlocked, height, width);
    open_file(instruction_page, instructions, height, width);

    //Copy text in text files to array for Stage Informations.
    open_file(stage_1_file, stage_1, height, width);
    open_file(stage_2_file, stage_2, height, width);
    open_file(stage_3_file, stage_3, height, width);
    open_file(stage_4_file, stage_4, height, width);
    open_file(stage_5_file, stage_5, height, width);
    open_file(stage_6_file, stage_6, height, width);
    open_file(stage_7_file, stage_7, height, width);
    open_file(stage_8_file, stage_8, height, width);
    open_file(stage_9_file, stage_9, height, width);
    open_file(stage_10_file, stage_10, height, width);
    open_file(stage_bonus_file, stage_bonus, height, width);
    open_file(stage_completed_file, stage_completed, height, width);
    open_file(game_over_1_file, game_over_1, height, width);
    open_file(game_over_2_file, game_over_2, height, width);
    open_file(story_mode_completed_file, story_mode_completed, height, width);
    // LOAD ILLUSTRATION FILES (END)

    auto control = async(get_player_input, &input, &key_in);
    cin.clear();

    //This is where the whole program starts.
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
            // Bonus Mode is not unlocked yet.
            if(Bonus_mode_unlocked == false)
            {
                pages_fill_frame(&frame, main_menu_locked, height, width);
                display(frame, height, width);
                cout << "      Game launched: " << asctime(current_time);
            }
            else
            {
                pages_fill_frame(&frame, main_menu_unlocked, height, width);
                display(frame, height, width);
                cout << "      Game launched: " << asctime(current_time);
            }
        }
        // There is a game in progress.
        else
        {
            next_level = false;
            input = '1';
        }
        //Selection on Main Menu
        //Selection 1 (New Game / Continue Game)
        if(input == '1')
        {
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
            if(stage_count_story_mode == 1)
            {
                    number_of_frames_record = 0;
                    Story_mode_finished = false;
                    // Settings for Stage 1
                    //
                    // One basic gattling gun, 1 type of enemy, 2 rows of enemy
                    stage.load_stage(1, 1, 2);
                    // Set spaceship HP to 10.
                    stage.spaceship.set_n_hits(10);
                    // Set spaceship reload time for gattling gun to 5.
                    stage.spaceship.set_reload_time(0, 5);
                    // Set the reload time for Craft X to 2.
                    stage.enemy.set_reload_time(0, 2);
                    // Set the hp of Craft X to 5.
                    stage.enemy.set_n_hits(0, 5);
                    // Set horizontal speed of enemy.
                    stage.enemy.set_n_frames_required_to_move_hor(20);
                    //Set vertical speed of enemy.
                    stage.enemy.set_n_frames_required_to_move_vert(150);
                    // Set enemy fire limit to 3
                    stage.enemy.set_n_fire_limit(3);
                    // Set enemy fire speed.
                    stage.enemy.set_n_frames_required_to_fire(30);

                    //Display Stage 1 information.
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
            else if(stage_count_story_mode == 2)
            {
                //One basic gattling gun, 1 type of enemy, 4 rows of enemy
                stage.load_stage(1, 1, 4);
                // Set spaceship HP to 10.
                stage.spaceship.set_n_hits(10);
                // Set spaceship reload time for gattling gun to 3.
                stage.spaceship.set_reload_time(0, 3);
                // Set the reload time for Craft X to 2.
                stage.enemy.set_reload_time(0, 2);
                // Set the hp of Craft X to 5.
                stage.enemy.set_n_hits(0, 5);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(10);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(150);
                // Set enemy fire limit to 4
                stage.enemy.set_n_fire_limit(4);
                // Set enemy fire speed at increased rate.
                stage.enemy.set_n_frames_required_to_fire(25);

                //Display Stage 2 Informations
                while(input != 'c')
                {
                    pages_fill_frame(&frame, stage_2, height, width);
                    display(frame, height, width);
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }
            }
            // Stage 3
            else if(stage_count_story_mode == 3)
            {
                //Gattling gun & Shot gun. 2 types of enemy, 2 rows of enemy
                stage.load_stage(2, 2, 2);
                // Set spaceship HP to 15.
                stage.spaceship.set_n_hits(15);
                // Set spaceship reload time for gattling gun to 3.
                stage.spaceship.set_reload_time(0, 3);
                // Set spaceship reload time for shot gun to 15.
                stage.spaceship.set_reload_time(1, 15);
                // Set the hp of Craft X to 5.
                stage.enemy.set_n_hits(0, 5);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(5);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(150);
                // Set enemy fire limit to 4.
                stage.enemy.set_n_fire_limit(4);
                // Set enemy fire speed.
                stage.enemy.set_n_frames_required_to_fire(25);

                //Display Stage 3 Informations.
                while(input != 'c')
                {
                    pages_fill_frame(&frame, stage_3, height, width);
                    display(frame, height, width);
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }
            }
            // Stage 4
            else if(stage_count_story_mode == 4)
            {
                //Gattling gun & Shot gun. 2 types of enemy, 4 rows of enemy
                stage.load_stage(2, 2, 4);
                // Set spaceship HP to 15.
                stage.spaceship.set_n_hits(15);
                // Set spaceship reload time for gattling gun to 2.
                stage.spaceship.set_reload_time(0, 2);
                // Set spaceship reload time for shot gun to 10.
                stage.spaceship.set_reload_time(1, 10);
                // Set the hp of Craft X to 5.
                stage.enemy.set_n_hits(0, 5);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(5);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(150);
                // Set enemy fire limit to 5.
                stage.enemy.set_n_fire_limit(5);
                // Set enemy fire speed.
                stage.enemy.set_n_frames_required_to_fire(25);

                //Display Stage 4 Informations.
                while(input != 'c')
                {
                    pages_fill_frame(&frame, stage_4, height, width);
                    display(frame, height, width);
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }
            }
            // Stage 5
            else if(stage_count_story_mode == 5)
            {
                //Gattling gun, Shot gun and laser. 3 types of enemy, 5 rows of enemy
                stage.load_stage(3, 3, 5);
                // Set spaceship HP to 20.
                stage.spaceship.set_n_hits(20);
                // Set spaceship reload time for gattling gun to 2.
                stage.spaceship.set_reload_time(0, 2);
                // Set spaceship reload time for shot gun to 10.
                stage.spaceship.set_reload_time(1, 10);
                // Set the hp of Craft X to 10.
                stage.enemy.set_n_hits(0, 10);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(5);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(150);
                // Set enemy fire limit to 5.
                stage.enemy.set_n_fire_limit(5);
                // Set enemy fire speed.
                stage.enemy.set_n_frames_required_to_fire(25);

                //Display Stage 5 Informations.
                while(input != 'c')
                {
                    pages_fill_frame(&frame, stage_5, height, width);
                    display(frame, height, width);
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }
            }
            // Stage 6
            else if(stage_count_story_mode == 6)
            {
                //Gattling gun, Shot gun and laser. 3 types of enemy, 7 rows of enemy
                stage.load_stage(3, 3, 7);
                // Set spaceship HP to 20.
                stage.spaceship.set_n_hits(20);
                // Set spaceship reload time for gattling gun to 1.
                stage.spaceship.set_reload_time(0, 1);
                // Set spaceship reload time for shot gun to 8.
                stage.spaceship.set_reload_time(1, 8);
                // Set spaceship reload time for laser to 25.
                stage.spaceship.set_reload_time(2,25);
                // Set the hp of Craft X to 10.
                stage.enemy.set_n_hits(0, 10);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(5);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(125);
                // Set enemy fire limit to 5.
                stage.enemy.set_n_fire_limit(5);
                // Set enemy fire speed.
                stage.enemy.set_n_frames_required_to_fire(25);

                //Display Stage 6 Informations.
                while(input != 'c')
                {
                    pages_fill_frame(&frame, stage_6, height, width);
                    display(frame, height, width);
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }
            }
            // Stage 7        cout << "HI" << endl;
            else if(stage_count_story_mode == 7)
            {
                // Gattling gun, Shot gun and laser. 3 types of enemy, 7 rows of enemy. Shield is available.
                stage.load_stage(4, 3, 7);
                // Set spaceship HP to 20.
                stage.spaceship.set_n_hits(20);
                // Set spaceship reload time for gattling gun to 1.
                stage.spaceship.set_reload_time(0, 1);
                // Set spaceship reload time for shot gun to 5.
                stage.spaceship.set_reload_time(1, 5);
                // Set the duration of laser
                stage.spaceship.set_frame_elasped_limit(2, 7);
                // Set the hp of Craft X to 10.
                stage.enemy.set_n_hits(0, 10);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(3);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(125);
                // Set enemy fire limit to 7.
                stage.enemy.set_n_fire_limit(7);
                // Set enemy fire speed.
                stage.enemy.set_n_frames_required_to_fire(20);

                //Display Stage 7 Informations.
                while(input != 'c')
                {
                    pages_fill_frame(&frame, stage_7, height, width);
                    display(frame, height, width);
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }
            }
            // Stage 8
            else if(stage_count_story_mode == 8)
            {
                // Gattling gun, Shot gun and laser. 3 types of enemy, 9 rows of enemy. Shield is available.
                stage.load_stage(4, 3, 9);
                // Set spaceship HP to 25.
                stage.spaceship.set_n_hits(25);
                // Set spaceship reload time for gattling gun to 1.
                stage.spaceship.set_reload_time(0, 1);
                // Set spaceship reload time for shot gun to 5.
                stage.spaceship.set_reload_time(1, 5);
                // Set the duration of laser
                stage.spaceship.set_frame_elasped_limit(2, 7);
                // Set the hp of Craft X to 10.
                stage.enemy.set_n_hits(0, 10);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(3);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(125);
                // Set enemy fire limit to 7.
                stage.enemy.set_n_fire_limit(7);
                // Set enemy fire speed.
                stage.enemy.set_n_frames_required_to_fire(20);

                //Display Stage 8 Informations.
                while(input != 'c')
                {
                    pages_fill_frame(&frame, stage_8, height, width);
                    display(frame, height, width);
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }
            }
            // Stage 9
            else if(stage_count_story_mode == 9)
            {
                // Gattling gun, Shot gun and laser. 3 types of enemy, 9 rows of enemy. Shield is available.
                stage.load_stage(4, 3, 9);
                // Set spaceship HP to 25.
                stage.spaceship.set_n_hits(25);
                // Set spaceship reload time for gattling gun to 1.
                stage.spaceship.set_reload_time(0, 1);
                // Set spaceship reload time for shot gun to 3.
                stage.spaceship.set_reload_time(1, 3);
                // Increase the duration of laser
                stage.spaceship.set_frame_elasped_limit(2, 7);
                // Increase the duration of shield.
                stage.spaceship.set_frame_elasped_limit(3,20);
                // Set the hp of Craft X to 10.
                stage.enemy.set_n_hits(0, 10);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(3);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(125);
                // Set enemy fire limit to 9.
                stage.enemy.set_n_fire_limit(9);
                // Set enemy fire speed.
                stage.enemy.set_n_frames_required_to_fire(18);

                //Display Stage 9 Informations.
                while(input != 'c')
                {
                    pages_fill_frame(&frame, stage_9, height, width);
                    display(frame, height, width);
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }
            }
            // Stage 10
            else if(stage_count_story_mode == 10)
            {
                // Gattling gun, Shot gun and laser. 3 types of enemy, 9 rows of enemy. Shield is available.
                stage.load_stage(4, 3, 9);
                // Set spaceship HP to 25.
                stage.spaceship.set_n_hits(25);
                // Set spaceship reload time for gattling gun to 1.
                stage.spaceship.set_reload_time(0, 1);
                // Set spaceship reload time for shot gun to 3.
                stage.spaceship.set_reload_time(1, 3);
                // Increase the duration of laser
                stage.spaceship.set_frame_elasped_limit(2, 10);
                // Increase the duration of shield
                stage.spaceship.set_frame_elasped_limit(3,25);
                // Set the hp of Craft X to 10.
                stage.enemy.set_n_hits(0, 10);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(1);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(100);
                // Set enemy fire limit to 10.
                stage.enemy.set_n_fire_limit(10);
                // Set enemy fire speed.
                stage.enemy.set_n_frames_required_to_fire(15);

                //Display Stage 10 Informations.
                while(input != 'c')
                {
                    pages_fill_frame(&frame, stage_10, height, width);
                    display(frame, height, width);
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }
            }

            // Execution of the each stage.
            while (input != 'm')
            {
                stage.clear_display_frame(&frame, width, height);
                game_state = stage.reload(input, &frame, width, height);
                number_of_frames_record++;

                display(frame, height, width);
                if (game_state == 1)
                {
                    // LOSE
                    stage.clear_stage();
                    // Variable used to switch between images.
                    bool image_switch = true;
                    //Show Game over Pages
                    while(input != 'c')
                    {
                        if(image_switch == true)
                        {
                            pages_fill_frame(&frame, game_over_1, height, width);
                            image_switch = false;
                        }
                        else
                        {
                            pages_fill_frame(&frame, game_over_2, height, width);
                            image_switch = true;
                        }
                        display(frame, height, width);
                        cin.clear();
                        input = '\0';
                        usleep(300000);
                    }
                    // Level status is refreshed to level 1. Time Spent refreshed to 0.
                    stage_count_story_mode = 1;
                    number_of_frames_record = 0;
                    break;
                }
                else if(game_state == -1)//
                {
                    // WIN
                    stage.clear_stage();
                    while(input != 'c')
                    {
                        pages_fill_frame(&frame, stage_completed, height, width);
                        display(frame, height, width);
                        cin.clear();
                        input = '\0';
                        usleep(75000);
                    }
                    // Proceed to the next level.
                    stage_count_story_mode = stage_count_story_mode + 1;
                    // To ensure that level 10 is the last level in story mode.
                    if(stage_count_story_mode <= 10)
                        next_level = true;
                    // Story Mode finished, stage count refreshed to 1.
                    if(stage_count_story_mode == 11)
                    {
                        stage_count_story_mode = 1;
                        Bonus_mode_unlocked = true;
                        Story_mode_finished = true;
                        while(input != 'm')
                        {
                            pages_fill_frame(&frame, story_mode_completed, height, width);
                            display(frame, height, width);
                            cin.clear();
                            input = '\0';
                            usleep(75000);
                        }
                    }
                    break;
                }
                cout << "| Life Points: " << stage.spaceship.spaceship_lifepoint() << "| Current Level: " << stage_count_story_mode << "|Time Spent: " << number_of_frames_record/12 << "|" << endl;
                cin.clear();
                input = '\0';
                usleep(75000);
            }
        }
        //Selection 2 ( Bonus Stages - Unlimited Waves)
        else if(input == '2')
        {
            if(Bonus_mode_unlocked == true)
            {
                // Bonus level
                int row_of_enemies = 2;
                int spaceship_hp = 30;
                int gattling_gun_reload_time = 5;
                int shot_gun_reload_time = 15;
                int duration_of_laser = 5;
                int duration_of_shield = 12;
                int enemy_horizontal_speed = 10;
                int enemy_vertical_speed = 100;
                int enemy_fire_limit = 2;
                int enemy_fire_speed = 10;
                // Start game.
                game_state = 0;
                // Set new keybind. 'l' to fire.
                stage.spaceship.set_key_binds(2, 'l');
                // Set new keybind. 'k' to switch weapon.
                stage.spaceship.set_key_binds(3, 'k');
                // Set new keybind. ';' to activate shield.
                stage.spaceship.set_key_binds(4, ';');
                //Display Bonus Stage Informations.
                while(input != 'c')
                {
                    pages_fill_frame(&frame, stage_bonus, height, width);
                    display(frame, height, width);
                    cin.clear();
                    input = '\0';
                    usleep(75000);
                }

                while(input != 'm' && game_state != 1)
                {
                    stage.load_stage(4, 3, row_of_enemies);
                    // Set spaceship HP.
                    stage.spaceship.set_n_hits(spaceship_hp);
                    // Set spaceship reload time for gattling gun.
                    stage.spaceship.set_reload_time(0, gattling_gun_reload_time);
                    // Set spaceship reload time for shot gun.
                    stage.spaceship.set_reload_time(1, shot_gun_reload_time);
                    // Set the duration of laser.
                    stage.spaceship.set_frame_elasped_limit(2, duration_of_laser);
                    // Set the duration of shield.
                    stage.spaceship.set_frame_elasped_limit(3,duration_of_shield);
                    // Set horizontal speed of enemy.
                    stage.enemy.set_n_frames_required_to_move_hor(enemy_horizontal_speed);
                    //Set vertical speed of enemy.
                    stage.enemy.set_n_frames_required_to_move_vert(enemy_vertical_speed);
                    // Set enemy fire limit.
                    stage.enemy.set_n_fire_limit(enemy_fire_limit);
                    // Set enemy fire speed.
                    stage.enemy.set_n_frames_required_to_fire(enemy_fire_speed);

                    //Execution of each stage
                    while(input != 'm')
                    {
                        stage.clear_display_frame(&frame, width, height);
                        game_state = stage.reload(input, &frame, width, height);

                        if (game_state == 1)
                        {
                            // LOSE
                            stage.clear_stage();
                            // Variable used to switch between images.
                            bool image_switch = true;
                            //Show Game over Pages
                            while(input != 'c')
                            {
                                if(image_switch == true)
                                {
                                    pages_fill_frame(&frame, game_over_1, height, width);
                                    image_switch = false;
                                }
                                else
                                {
                                    pages_fill_frame(&frame, game_over_2, height, width);
                                    image_switch = true;
                                }
                                display(frame, height, width);
                                cin.clear();
                                input = '\0';
                                usleep(300000);
                            }
                            // Level status is refreshed to level 1.
                            stage_count_bonus_mode = 1;
                            break;
                        }
                        else if(game_state == -1)
                        {
                            // WIN
                            stage.clear_stage();
                            while(input != 'c')
                            {
                                pages_fill_frame(&frame, stage_completed, height, width);
                                display(frame, height, width);
                                cin.clear();
                                input = '\0';
                                usleep(75000);
                            }
                            // Proceed to the next level.
                            stage_count_bonus_mode = stage_count_bonus_mode + 1;
                            row_of_enemies++;
                            spaceship_hp = stage.spaceship.spaceship_lifepoint();
                            if(gattling_gun_reload_time > 1)
                                gattling_gun_reload_time--;
                            if(shot_gun_reload_time > 1)
                                shot_gun_reload_time--;
                            duration_of_laser++;
                            duration_of_shield++;
                            if(enemy_horizontal_speed > 1)
                                enemy_horizontal_speed--;
                            if(enemy_vertical_speed > 1)
                                enemy_vertical_speed--;
                            enemy_fire_limit++;
                            enemy_fire_speed++;
                            break;
                        }
                        display(frame, height, width);
                        cout << "||   Life Points: " << stage.spaceship.spaceship_lifepoint() << "    ||    Current Wave: " << stage_count_bonus_mode << "    ||" << endl;
                        cin.clear();
                        input = '\0';
                        usleep(75000);
                    }
                }
                // If quitted to Main Menu, must replay from wave 1.
                if(game_state == 0)
                    stage_count_bonus_mode = 1;
            }
        }
        //Selection 3 (Load Saved Game)
        else if(input == '3')
        {
            key_in = 1;
            system("stty echo");
            system("stty -cbreak");
            string name;
            // Prompts User to type his name.
            pages_fill_frame(&frame, savefile, height, width);
            display(frame, height, width);
            getline(cin, name);
            name = input + name;

            //Check the players_gamestatus_array for the name of player entered.
            for(int i = 0; i < number_of_saved_players; i++)
            {
                if(players_gamestatus_array[i].player_name == name)
                {
                    string proceed;
                    stage_count_story_mode = players_gamestatus_array[i].storymode_level;
                    Bonus_mode_unlocked = players_gamestatus_array[i].bonusmode_status;
                    number_of_frames_record = players_gamestatus_array[i].storymode_timespent;
                    Story_mode_finished = players_gamestatus_array[i].story_mode_status;
                    cout << endl << "Username found. Press ENTER to return to main menu." << endl;
                    getline(cin, proceed);
                }
            }
            key_in = 0;
            // Supress echo for terminal.
            system("stty -echo");
            // Use RAW mode for terminal.
            system("stty cbreak");
        }
        //Selection 4 (Show Instructions)
        else if(input == '4')
        {
            pages_fill_frame(&frame, instructions, height, width);
            display(frame, height, width);
            while(input != 'm')
            {

            }
            cin.clear();
            input = '\0';
        }
        //Selection 5 (Show Leaderboard)
        else if(input == '5')
        {
            pages_fill_frame(&frame, leaderboard, height, width);
            display(frame, height, width);
            cout << "Press 'm' to return to Main Menu" << endl;
            while(input != 'm')
            {

            }
        }
        cin.clear();
        input = '\0';
        usleep(75000);
    }
    // GAME exited.
    cin.clear();
    // Save Game Progress of Player.
    ofstream fout;
    fout.open(savefile_file);
    if(fout.fail())
    {
        cout << "Error in file opening." << endl;
        // Reset terminal settings
        system("stty echo");
        system("stty -cbreak");
        exit(1);
    }
    // Reset terminal settings
    system("stty echo");
    system("stty -cbreak");
    string user_name;
    // Variable to store number of players to save to savefile.txt;
    int number_of_players_to_save = 0;
    // Prompts User to type his name.
    cout << "Please type your name and press enter!" << endl;
    cin >> user_name;
    // Check if the current player has saved any game status beforehand.
    // Check if the current player has saved any game status beforehand.
    if(number_of_saved_players == 0)
    {
        players_gamestatus_array[number_of_saved_players].player_name = user_name;
        players_gamestatus_array[number_of_saved_players].storymode_level = stage_count_story_mode;
        players_gamestatus_array[number_of_saved_players].storymode_timespent = number_of_frames_record;
        players_gamestatus_array[number_of_saved_players].bonusmode_status = Bonus_mode_unlocked;
        players_gamestatus_array[number_of_saved_players].story_mode_status = Story_mode_finished;
        number_of_players_to_save = number_of_saved_players + 1;
    }
    else
    {
        for(int i = 0; i < number_of_saved_players; i++)
        {
            // Overwrite Current Game Data.
            if(players_gamestatus_array[i].player_name == user_name)
            {
                players_gamestatus_array[i].storymode_level = stage_count_story_mode;
                players_gamestatus_array[i].storymode_timespent = number_of_frames_record;
                players_gamestatus_array[i].bonusmode_status = Bonus_mode_unlocked;
                players_gamestatus_array[i].story_mode_status = Story_mode_finished;
                number_of_players_to_save = number_of_saved_players;
                break;
            }
            // Add a new player to the players_gamestatus_array
            else
            {
                players_gamestatus_array[number_of_saved_players].player_name = user_name;
                players_gamestatus_array[number_of_saved_players].storymode_level = stage_count_story_mode;
                players_gamestatus_array[number_of_saved_players].storymode_timespent = number_of_frames_record;
                players_gamestatus_array[number_of_saved_players].bonusmode_status = Bonus_mode_unlocked;
                players_gamestatus_array[number_of_saved_players].story_mode_status = Story_mode_finished;
                number_of_players_to_save = number_of_saved_players + 1;
            }
        }
    }


    for(int j = 0; j < number_of_players_to_save; ++j)
    {
        fout << players_gamestatus_array[j].player_name << " " << players_gamestatus_array[j].storymode_level << " " << players_gamestatus_array[j].storymode_timespent << " " << players_gamestatus_array[j].bonusmode_status << " " << players_gamestatus_array[j].story_mode_status << endl;
    }
    fout.close();

    //Indicating game has quitted.
    cout << "Game Saved. You successfully exit from the game. Hope you had fun!" << endl;
    // Free memory allocated to the array.
    for (int i = 0; i < height; i++)
    {
    delete[] frame[i];
    }
    delete[] frame;
    delete[] players_gamestatus_array;

    return 0;
}
