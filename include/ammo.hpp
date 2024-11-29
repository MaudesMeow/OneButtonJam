#ifndef AMMO_HEADER
#define AMMO_HEADER

#include "globals.hpp"



class Ammo
{
    public:
        Vector2 bulletPos,p1,p2,p3;
        float speed;
        bool hasCollided,hasFired;
        Rectangle hitBox;
        

        Ammo()
        {
            bulletPos = {0,0};
            hasCollided = false;
            speed = 680;
            
            hasFired = false;
            hitBox = Rectangle{bulletPos.x,bulletPos.y,16,16};
        };


        
        
        void SetAmmoPos(Vector2 pos,int direction);
    

};

void DisplayAmmo(int ammoCount);

void AnimateAmmo(vector<Ammo*> &ammo);  // Display function for side of screen to let player know how much ammo they have 
void UpdateAmmoBehavior();
Ammo* PopulateAmmo();




#endif