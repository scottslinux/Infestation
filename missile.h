#ifndef MISSILE_H
#define MISSILE_H

#include <iostream>
#include <math.h>
#include <vector>
#include "raylib.h"
#include "swarm.h"


static int laserpower;


struct shot
{
    Vector2 pos;
    Vector2 vel;
    float theta;
    float scale;
    double last_time;

    Rectangle colrect;


};
//==========================================
class missile
{


private:
    int activeshots;    //leave as a reminder of what could have been
    static Sound lasershot;


public:
    //keep it real...single rocket for now
    shot rocket;   //make publicly available






    missile(/* args */);    //constructor
    //fire a missile and provide the player pos and vel to determine pos
    void fireshot(Vector2 pos, int direction,swarm& herd); 
    void updatemissile();
    void drawmissile();
    void killroach();
    static int getremainlaser();
    bool fireflag;

    void playlasersound();
    static void initializeMissileSound();


};





















#endif