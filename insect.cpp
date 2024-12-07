#include "insect.h"
#include <vector>
#include "swarm.h"

Texture2D insect::bug;           //reserves memory for the static var
bool insect::isSpritesheetLoaded=false;
//also sent this to github
//=====================================================
//                      constructor
insect::insect()
{
    spritedimension=128;

    if(!isSpritesheetLoaded)     //Load the sprite sheet only once
    {
        bug=LoadTexture("resources/Roach sprites.png");
        isSpritesheetLoaded=true;
    }

 
    pos.x=GetRandomValue(1200,1500);  //generate random x,y position
    pos.y=GetRandomValue(900,900);

    while(abs(vel.x)<100)           //prevents low or zero velocities
        vel.x=GetRandomValue(-300,300);
    while(abs(vel.y)<100)
        vel.y=GetRandomValue(-300,300);
    

    rotation=0;
    scale=GetRandomValue(1,3)*0.5f;   //random size
    spritecntr.x=(spritedimension/2*scale);
    spritecntr.y=(spritedimension/2*scale);

    //initial collision rect on creation
    colrec={pos.x-128/2*scale,pos.y=128/2*scale,128*scale,128*scale};



    last_time=GetTime();    //set the time stamp to birth
    frame=0;                //initial frame
    frametimer=0.0;
    vitality=Alive;
    alive=1;


    

    

    return;
}
//=====================================================
//update pos of individual roach. 
//adjust rotation and check boundries

void insect::updateroachpos()
{
    double delta_t=GetTime()-last_time;
    if(delta_t>0.1) delta_t=0.1;

    frametimer+=delta_t; // keep track of time between steps
    
    
    pos.x+=vel.x*delta_t;
    pos.y+=vel.y*delta_t;

    rotation=90+radians2degrees(atan2(vel.y,vel.x));
    last_time=GetTime(); //very important to update timestamp :|

    //bounds checking
    //----------------------
    if(pos.x<10)
    {
        pos.x+=2;
        vel.x*=-1;
    }
    if(pos.x>GetScreenWidth()-128)
    {
        pos.x-=2;
        vel.x*=-1;
    }
    if(pos.y<10)
    {
        pos.y+=2;
        vel.y*=-1;
    }
    if(pos.y>GetScreenHeight()-128)
    {
        pos.y-=2;
        vel.y*=-1;
    }

    
    //---------------------

    if(frametimer>=.05)
    {   
        frametimer=0;   //reset frame timer
        if(++frame>2)   //Increment and if past the last frame on the spritesheet
            frame=0;    //start at the first

    
    }




    return;
}
//=====================================================

void insect::killroach()
{
    alive=0;

    return;
}
//=====================================================

void insect::drawroach()
{
    //draws an individual roach and then again for the shadow

    Rectangle source={(128.0f*frame),0,128.0f,128.0f};
    Rectangle dest={pos.x,pos.y,128*scale,128*scale};
    //shadow rectangle is offset from the original
    Rectangle dest2={pos.x+15,pos.y+15,128*scale,128*scale}; //shadow position
    Color shadow={0,0,0,128};  //128 of 255 in alpha channel

    //calcualte collision rect position and size
    colrec={pos.x-128/2*scale,pos.y-128/2*scale,128*scale,128*scale};

    //draw the shadow first and then roach on top of it
    DrawTexturePro(bug,source,dest2,spritecntr,rotation,shadow);
    DrawTexturePro(bug,source,dest,spritecntr,rotation,WHITE);

    //Create a circle around each roach for collision detection
    //vary diameter according to the scale of the roach

    float radius=40*scale;
    DrawRing(pos,radius,radius+10,0,360,36,BLUE);

    if (alive==0)  //if the roach is dead make a mark--prelim red circle
        DrawRing(pos,radius,radius+10,0,360,36,RED);
        


    
    return;
}
//=====================================================
Vector2 insect::getbugpos()
     {
        
        return pos;
    }
//=====================================================

float insect::getbugscale()
{
    return scale;
}


//=====================================================

//=====================================================
//      utility for use with calculating roach rotation
//      from direction. (atan2 gives result in radians)
//      sprite rotation is in degrees


double insect::radians2degrees(double rads)
{
    return(rads*180.0f/M_PI);

}