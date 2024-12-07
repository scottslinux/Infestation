#include <iostream>
#include "raylib.h"
#include "insect.h"
#include "Hero.h"
#include "swarm.h"
#include "scoreboard.h"
#include "missile.h"
#include "ATC.h"



using namespace std;

void check4Collision(swarm,Hero);   //prototype

bool collisionFlag=false;


int main()
{
    SetTargetFPS(60);
    // Set flags for an undecorated window (borderless)
    //creates full screen without the artifacts of actual
    //fullscreen
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);


    InitWindow(GetMonitorWidth(0),GetMonitorHeight(0),"INFESTATION");
    InitAudioDevice();

    //**************************************/

    // Instantiate the core objects for the game

    Hero guy;           //instantiate player
    swarm myswarm(15);  //instantiate the roach swarm  
    scoreboard screen;  //screen boarder and scores
    missile blaster;
    //*************************************/

    Sound backgroundmusic;
    backgroundmusic=LoadSound("resources/Infestation Lullaby.wav");

    

   
    while(!WindowShouldClose())
    {
        BeginDrawing();

       if(!IsSoundPlaying(backgroundmusic))
           PlaySound(backgroundmusic); //ooooh nice!

    //Sound mysound=LoadSound("resources/Laser.wav");
    //PlaySound(mysound);

        screen.drawscreenframe();
        guy.updateplayer();

        ATC::collide(myswarm,guy);  //fucking STATIC FUNCTION !!!!!!!!
        
        guy.drawplayer();
        myswarm.displayswarm();
        blaster.fireshot(guy.getplayerpos(),guy.getplayerdirection(),myswarm);
        //call the laser and send it the swarm for roach deaths


        EndDrawing();


    }
    return 0;
    
}

