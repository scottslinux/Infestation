#ifndef HERO_H
#define HERO_H

#include <raylib.h>
#include <iostream>




class Hero
{
private:
    static bool isSpritesheetLoaded;

    Vector2 pos;
    Vector2 vel;
    bool directionflag;
    Vector2 origin;
    float rotation;     //sprite rotation
    float scale;
    double last_time;   //time stamp for last movement
    int frame;          //current frame of animation
    double frametimer;
    int spritesqr;
    double delta_t;
    int direction;

    int vitality;      //create variable of type life

    Rectangle colrec;   //this sprites collision rectangle


public:
    static Texture2D heroimage;

    Hero(/* args */);  //Constructor

    int collisioneventcountdown;    //keep these public so other routines can mark collisions
    bool colliding;

    void updateplayer();
    void killplayer();
    void drawplayer();
    void controllerinput();
    Rectangle getplayerrect();
    Vector2 getplayerpos();
    Vector2 getplayervel();
    int getplayerdirection();

};

#endif