#include "swarm.h"
#include <vector>
#include "Hero.h"


//=======================================
swarm::swarm(int num)
{
    
    roaches.resize(num);    //create the roaches
    roachesinswarm=num;


    
    
   
}
//=======================================
void swarm::displayswarm()
{
    for(int i=0;i<roaches.size();i++)
    {
        roaches[i].updateroachpos();
        roaches[i].drawroach();

    }


    return;
}

//=======================================
bool check4collision()
{
    


}