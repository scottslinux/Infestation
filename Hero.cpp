#include "Hero.h"
#include <sstream>
#include <stdio.h>
#include <iomanip>  // For std::fixed and std::setprecision
#include <math.h>
#include "swarm.h"


Texture2D Hero::heroimage;
bool Hero::isSpritesheetLoaded=false;



//===============================================
//          constructor

Hero::Hero(){
    pos.x=1200; //starting character position
    pos.y=1200;
    vel.x=0;
    vel.y=0;
    directionflag=false;
    scale=0.75;
    origin={pos.x+512*scale/2,pos.y+512*scale/2};
    

    rotation=0;

    last_time=GetTime();
    frame=0;
    frametimer=0.0;
    const int spritesqr=512;
    delta_t=0;
    direction=1;

    vitality=1; //1-alive,2-dying,3-dead

    colrec={pos.x,pos.y,512*scale,512*scale};  //***dummy values */
    colliding=false;
    collisioneventcountdown=0;


    if(!isSpritesheetLoaded)    //hoperfully a single load
    {   isSpritesheetLoaded=true;
        heroimage=LoadTexture("resources/exterminator.png");
        //Load up the sound objects
        Sound man_oonoo;
        man_oonoo=LoadSound("resources/ooono.wav");
    }
        

}
//=============================================
void Hero::updateplayer()
{
    controllerinput();

    delta_t=GetTime()-last_time;
    frametimer+=delta_t;


    //check bounds before updating position.
    if((pos.x+delta_t*vel.x)>20 && 
        (pos.x+delta_t*vel.x)<GetScreenWidth()-300)
                pos.x+=delta_t*vel.x;

    if((pos.y+delta_t*vel.y)>20 && 
        (pos.y+delta_t*vel.y)<GetScreenHeight()-360)               
                pos.y+=delta_t*vel.y;

    last_time=GetTime();    //update last time moved

    if(frametimer>20/abs(vel.x) || frametimer>20/abs(vel.y))
    {
        
        if(++frame>3) frame=0;  //advance to next frame--reset if needed
        frametimer=0;
    }
    int scaleddim=512*scale;

    //  Painstakingly edited the HIT BOX to adjust the size around the Hero
    colrec={pos.x+(0.3f*scaleddim),pos.y+(0.15f*scaleddim),scaleddim-0.6f*scaleddim,(float)(scaleddim-100)};  //update collision rect
    
    
    //important to set velocity back to zero so walking stops
    vel.x=0;
    vel.y=0;

    

    return;
}

//=============================================
void Hero::drawplayer()
{
    int death;
    if(colliding)
        death=512;
            else   
                death=0;

    Rectangle source={512*frame,0+death,direction*512,512};
    Rectangle destin={pos.x,pos.y,512*scale,512*scale};
    

    DrawTexturePro(heroimage,source,destin,{0,0},0,WHITE);
    DrawRectangleLinesEx(colrec,5,RED);


    return;
}
//===========================================
void Hero::controllerinput()
{
    std::stringstream ss;
    std::stringstream direc;

    float x=GetGamepadAxisMovement(0,0);
    float y=GetGamepadAxisMovement(0,1);

    if(abs(x)<0.2)x=0;  //remove the jitter
    if(abs(y)<0.2)y=0;  

    

    

    vel.x=500*x;  //translate stick to velocity
    vel.y=500*y;

    //adjust player sprite direction
    if(vel.x>0) 
        {   
            directionflag=false;
            direction=1;
        }
    if(vel.x<0)
        direction=-1;

    /*Display the data
    Rectangle border={350,100,800,200};
    DrawRectangle(350,100,800,200,WHITE);
    DrawRectangleLinesEx(border,5,BLACK);

    ss << "X AXIS(0) : "<<std::fixed << std::setprecision(3) << x
    <<" Y AXIS(1): "<<std::fixed << std::setprecision(3)<<y;

        // Convert to string
    std::string formattedFloat = ss.str();

    DrawText(formattedFloat.c_str(),400,200,30,DARKBLUE);

    ss.str(""); //clear the stringstream variable
    ss.clear(); //and flags
    ss<<"Direction Flag: "<<direction;
    std::string dir=ss.str();
    DrawText(dir.c_str(),500,300,30,DARKGREEN);

if (!colliding)
{

    DrawCircle(1000,300,100,Color{0,245,0,50}); //lighting effect low alpha (very transparent)
    DrawCircle(1000,300,40,GREEN);
    DrawRing({1000,300},40,50,0,360,36,Color{222,222,255,255});
}
    else
    {
        DrawCircle(1000,300,100,Color{255,0,0,50}); //lighting effect low alpha (very transparent)
        DrawCircle(1000,300,40,RED);
        --collisioneventcountdown;

    }
*/


    return;

}
//============================================
Rectangle Hero::getplayerrect()
{
    return colrec;

}
//============================================
void Hero::killplayer()
{
    vitality=3; 
    collisioneventcountdown=1000;
    colliding=true;

}
//============================================
Vector2 Hero::getplayerpos()
{
    return(pos);
}
//============================================
Vector2 Hero::getplayervel()
{
    return(vel);
}
//============================================
int Hero::getplayerdirection()
{
    return(direction);

}