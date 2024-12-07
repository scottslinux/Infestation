#pragma once

#include <iostream>
#include "raylib.h"
#include "insect.h"
#include "Hero.h"
#include "swarm.h"

//This module will consist of static methods used to detect
//collisions and set flags. It may or may not end up implementing 
//the results of the collision..let's let it evolve.

class ATC
{

public:


    ATC();  // constructor....may not use as its all static

    static void collide(swarm& herd,Hero& player);    //pass the swarm by reference
    static void collide(swarm& herd,Vector2,Vector2);        //roach swarm and start/end of laser line



    


};

