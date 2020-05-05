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
    // Initialize a variable to check if game should proceeds to next level.
    bool next_level = false;
    // Variable to check if the "Regular Game mode" has been finished.
    bool Bonus_mode_unlocked = false;

    char input = '0';
    int position = 0;
    const int width = 50;
    const int height = 35;

    // Initiate array for Main Menu illustration.
    char main_menu_locked[height][width];
    char main_menu_unlocked[height][width];
    // Initiate array for Instruction page.
    char instructions[height][width];
    //Initiate array for Stage_1 information page.
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

    // Store file name that store the illustrations into arrays (For Mainpages)
    char homepage_locked[] = "../In-game illustrations/homepage(locked).txt", homepage_unlocked[] = "../In-game illustrations/homepage(unlocked).txt", instruction_page[] = "../In-game illustrations/instructions.txt", leaderBoard[] = "leaderboard.txt";
    //Store file name that store the illustrations into arrays (For pages relating to stages information)
    char stage_1_file[] = "../In-game illustrations/Stage_1.txt";
    char stage_2_file[] = "../In-game illustrations/Stage_2.txt";
    char stage_3_file[] = "../In-game illustrations/Stage_3.txt";
    char stage_4_file[] = "../In-game illustrations/Stage_4.txt";
    char stage_5_file[] = "../In-game illustrations/Stage_5.txt";
    char stage_6_file[] = "../In-game illustrations/Stage_6.txt";
    char stage_7_file[] = "../In-game illustrations/Stage_7.txt";
    char stage_8_file[] = "../In-game illustrations/Stage_8.txt";
    char stage_9_file[] = "../In-game illustrations/Stage_9.txt";
    char stage_10_file[] = "../In-game illustrations/Stage_10.txt";
    char stage_bonus_file[] = "../In-game illustrations/Stage_Bonus.txt";
    char stage_completed_file[] = "../In-game illustrations/Stage_completed.txt";
    char game_over_1_file[] = "../In-game illustrations/Game_over_1.txt";
    char game_over_2_file[] = "../In-game illustrations/Game_over_2.txt";

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
        else
        {
            next_level = false;
            input = '1';
        }
        //Selection on Main Menu
        //Selection 1
        if(input == '1')
        {
            // Start game.
            game_state = 0;
            // Initialize a variable to indicate the current level.
            int stage_count = 1;
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
            else if(stage_count == 3)
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
                stage.enemy.set_n_frames_required_to_move_vert(100);
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
            else if(stage_count == 4)
            {
                //Gattling gun & Shot gun. 2 types of enemy, 4 rows of enemy
                stage.load_stage(2, 2, 4);
                // Set spaceship HP to 15.
                stage.spaceship.set_n_hits(15);
                // Set spaceship reload time for gattling gun to 2.
                stage.spaceship.set_reload_time(0, 2);
                // Set spaceship reload time for shot gun to 10.
                stage.spaceship.set_reload_time(1, 10);
                // Set the hp of Craft X to 10.
                stage.enemy.set_n_hits(0, 10);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(5);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(100);
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
            else if(stage_count == 5)
            {
                //Gattling gun, Shot gun and laser. 3 types of enemy, 5 rows of enemy
                stage.load_stage(3, 3, 5);
                // Set spaceship HP to 20.
                stage.spaceship.set_n_hits(20);
                // Set spaceship reload time for gattling gun to 2.
                stage.spaceship.set_reload_time(0, 2);
                // Set spaceship reload time for shot gun to 10.
                stage.spaceship.set_reload_time(1, 10);
                // Set the hp of Craft X to 15.
                stage.enemy.set_n_hits(0, 15);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(5);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(90);
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
            else if(stage_count == 6)
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
                // Set the hp of Craft X to 15.
                stage.enemy.set_n_hits(0, 15);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(5);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(90);
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
            // Stage 7
            else if(stage_count == 7)
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
                // Set the hp of Craft X to 20.
                stage.enemy.set_n_hits(0, 20);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(3);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(80);
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
            else if(stage_count == 8)
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
                // Set the hp of Craft X to 20.
                stage.enemy.set_n_hits(0, 20);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(3);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(80);
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
            else if(stage_count == 9)
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
                // Set the hp of Craft X to 20.
                stage.enemy.set_n_hits(0, 20);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(3);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(75);
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
            else if(stage_count == 10)
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
                // Set the hp of Craft X to 20.
                stage.enemy.set_n_hits(0, 20);
                // Set horizontal speed of enemy.
                stage.enemy.set_n_frames_required_to_move_hor(1);
                //Set vertical speed of enemy.
                stage.enemy.set_n_frames_required_to_move_vert(70);
                // Set enemy fire limit to 10.
                stage.enemy.set_n_fire_limit(10);
                // Set enemy fire speed.
                stage.enemy.set_n_frames_required_to_fire(15);

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

            // Execution of the each stage.
            while (input != 'm')
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
                    stage_count = 1;
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
                    stage_count = stage_count + 1;
                    if(stage_count <= 10)
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
        }
        //Selection 2
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
                // Initialize a variable to indicate the current level.
                int stage_count = 1;
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

                // Gattling gun, Shot gun and laser. 3 types of enemy, 9 rows of enemy. Shield is available.
                while(input != 'm' && game_state != 1)
                {
                    stage.load_stage(4, 3, row_of_enemies);
                    // Set spaceship HP.
                    stage.spaceship.set_n_hits(spaceship_hp);
                    // Set spaceship reload time for gattling gun.
                    stage.spaceship.set_reload_time(0, gattling_gun_reload_time);
                    // Set spaceship reload time for shot gun.
                    stage.spaceship.set_reload_time(1, shot_gun_reload_time);
                    // Increase the duration of laser.
                    stage.spaceship.set_frame_elasped_limit(2, duration_of_laser);
                    // Increase the duration of shield.
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
                            stage_count = 1;
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
                            stage_count = stage_count + 1;
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
                        cout << "||   Life Points: " << stage.spaceship.spaceship_lifepoint() << "    ||    Current Wave: " << stage_count << "    ||" << endl;
                        cin.clear();
                        input = '\0';
                        usleep(75000);
                    }
                }
                if(game_state == 0)
                    stage_count = 1;
            }
        }
        //Selection 3 (Load Saved Game)
        else if(input == '3')
        {

        }
        //Selection 4 (Show Instructions)
        else if(input == '4')
        {
            pages_fill_frame(&frame, instructions, height, width);
            display(frame, height, width);
            while(input != 'm')
            {

            }
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
