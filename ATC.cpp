#include <iostream>
#include "raylib.h"
#include "insect.h"
#include "Hero.h"
#include "swarm.h"
#include "ATC.h"



//================================================================
//
//              ATC -Air Traffic Control Collision Monitor
//================================================================

ATC::ATC()      //constructor
{

}
//***********************************************************************************
void ATC::collide(swarm& herd,Hero& player)    //pass the swarm by reference and the player.
{
    
    //check if roach contacts and kills player
    for(int i=0;i<herd.roachesinswarm;i++)
    {
        if(CheckCollisionCircleRec({herd.roaches[i].getbugpos()}
            ,60*herd.roaches[i].getbugscale(),player.getplayerrect()))
            {
                player.killplayer();
                DrawCircle(900,900,300,BLUE);
            }
            
            
    }

    return;
}
//***********************************************************************************
void ATC::collide(swarm& herd,Vector2 startpt,Vector2 endpt)    
{
        ///roach swarm and start/end of laser line
        for(int i=0;i<herd.roachesinswarm;i++)
        {
            if(CheckCollisionCircleLine(herd.roaches[i].getbugpos(),
                60*herd.roaches[i].getbugscale(),startpt,endpt))
                {
                    herd.roaches[i].killroach();    //simple method sets alive to 0


                }



        }



}