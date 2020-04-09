#ifndef SPACESHIP_H
#define SPACESHIP_H

class Gun
{
public:
    // Using a queue to store coordinates of each bullet.
    struct Bullet
    {
        int X;
        int Y;
        Bullet *next;
    };

    void load_gun(int);
    void fire(int);
    void move_bullet(char ***, int);
    void pop_bullet();
    void destroy_target(char ***, int, int, char);
    void display_bullets(char ***, int);

    int shape[3];

private:
    int time_charge;
    int time_between_fire;
    int bullet_width;
    char icon;
    Bullet *head;
};


class Spaceship
{
public:
    void load_spaceship();
    void move(char, char ***, int);
    void fill_frame(char ***, int);
    void switch_gun();

private:
    int x_coor;
    int ship_width;
    int n_guns;
    int current_gun;
    Gun available_guns[3];
};

#endif
