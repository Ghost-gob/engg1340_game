#ifndef GUN_H
#define GUN_H


class Gun
{
public:
    // Using a stack to store coordinates of each bullet.
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
    void bullet_hit(char ***, int, int);
    void laser_hit(char ***, int, int);
    void display_bullets(char ***, int);
    void display_laser(char ***, int);

    int shape[3];

private:
    int time_charge;
    int time_between_fire;
    int bullet_width;
    char icon;
    int delay;
    Bullet *head;
};

#endif
