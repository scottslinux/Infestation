#include "missile.h"
#include "ATC.h"
#include "swarm.h"

Sound missile::lasershot={0};
//reserve memory for the static variable

//==============================================//
missile::missile()  //constructor defiition
{
    //initializing everything to zero at start

    rocket.pos.x=0;
    rocket.pos.y=0;
    rocket.vel.x=0;
    rocket.vel.y=0;

    rocket.theta=0;
    rocket.last_time=0;

    laserpower=250; //starting laser power

    //check to see
    
    initializeMissileSound();


}
//==============================================//
//   get a shot off passing hero pos and direction
void missile::fireshot(Vector2 pos, int direction,swarm& herd)
{
    if(GetGamepadAxisMovement(0,5)>0 && laserpower>0)
    {

        missile::playlasersound();


        fireflag=true;

        Vector2 correctedxypos;
        Vector2 startshot;
        Vector2 endshot;
        --laserpower;
        if (laserpower<=0)
            laserpower=0;


        if(direction==1)       //hero looking right
        {
            correctedxypos.x=pos.x+375;
            correctedxypos.y=pos.y+60;

            float gunangle=35*(M_PI/180.0);  //convert to radians
            startshot={correctedxypos.x,correctedxypos.y};

            endshot={correctedxypos.x+(2000*cos(gunangle)),
            correctedxypos.y-(2000*sin(gunangle))};
        }
        else       //hero looking left
        {
            correctedxypos.x=pos.x+20;
            correctedxypos.y=pos.y+50;

            float gunangle=145*(M_PI/180.0);  //convert to radians
            startshot={correctedxypos.x,correctedxypos.y};

            endshot={correctedxypos.x+(2000*cos(gunangle)),
            correctedxypos.y-(2000*sin(gunangle))};
        }
        Color shotcolor={255,186,49,100};
        Color lasercolor={255,138,253,150};
        Color lasercolor2={255,138,253,50};

        

        DrawLineEx(startshot,endshot,80,lasercolor2);
        DrawLineEx(startshot,endshot,GetRandomValue(10,60),lasercolor);

        DrawLineEx(startshot,endshot,GetRandomValue(3,20),WHITE);

        
        fireflag=false;

        ATC::collide(herd,startshot,endshot);   //check for a hit on the roaches

        
        
    }


}


//==============================================//
int missile::getremainlaser()
{   return laserpower; }

//==============================================
void missile::playlasersound()
{
    //missile::lasershot=LoadSound("resources/Laser.wav");
    PlaySound(missile::lasershot);
    //UnloadSound(lasershot);

}
//===============================================
void missile::initializeMissileSound()

//only load the sound if it has not already been loaded.
{   if (missile::lasershot.frameCount<=0)
        missile::lasershot=LoadSound("resources/Laser.wav");
    return;
}
