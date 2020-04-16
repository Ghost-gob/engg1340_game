#ifndef GUN_H
#define GUN_H


class Gun
{
public:

    // Queue data structure to store information of each bullet fired.
    struct Bullet
    {
        // x and y coordinates of each bullet.
        int X, Y;
        Bullet *next;
    };

    // Pointer pointing to first bullet fired.
    Bullet *head;
    // Width of bullet;
    int bullet_width;
    // Direction of bullet fired.
    int bullet_direction;
    // Number of frames displayed before the bullets will be moved, creating a
    // delayed effect.
    int frame_elasped_limit;
    // Gun reload time.
    int reload_time;
    // Current reload duration that elasped.
    int current_reload_duration;
    // y-coordinate of gun.
    int y_coor;
    // Character representing the bullet fired;
    char icon;
    // Character array to store appearance of gun..
    char shape[3];

    // Member functions:
    void load_gun(int, int);
    void set_reload_time(int);
    void set_frame_elasped_limit(int);
    void increment_time();
    void move_bullet(int);
    void move_shield(int);
    void display_bullets(char ***, int);
    void display_laser(char ***, int);
    void pop_bullet();
    void clear_bullets();
    int fire(int);
    int bullet_hit(char ***, int, int);
    int laser_hit(char ***, int, int);
    int display_shield(char ***);
};

#endif
