#ifndef INSECT_H
#define INSECT_H

#include<iostream>
#include<cmath>
#include "raylib.h"


enum life {Dead,Alive,Dying};   //GLOBAL life flag 0-2
constexpr float SPRITESQRSIZE=128.0F;

class insect
{

private:
    static Texture2D bug;           // Shared sprite sheet for all instances
    static bool isSpritesheetLoaded; // Flag to track if the sprite sheet is loaded
    int spritedimension;

    Vector2 pos;        //x,y coordinates
    Vector2 vel;        //x,y vel
    float rotation;     //sprite rotation
    float scale;
    double last_time;   //time stamp for last movement
    int frame;          //current frame of animation
    double frametimer;
    Vector2 spritecntr;

    life vitality;      //create variable of type life
    bool colliding;
    bool alive;


public:
    Rectangle colrec;   //this sprites collision rectangle
    

    insect();     //constructor

    void updateroachpos();
    void killroach();       //maybe in swarm manager
    void drawroach();
    double radians2degrees(double rads);
    void adjustroachsize();
    Vector2 getbugpos();
    float getbugscale();


};








#endif