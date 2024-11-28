#ifndef AMMO_HEADER
#define AMMO_HEADER

#include "globals.hpp"

int ammoAmount = 0;

class Ammo
{
    Vector2 pos,p1,p2,p3;
    float speed;

    

};

void DisplayAmmo(int ammoAmount);  // Display function for side of screen to let player know how much ammo they have 
void UpdateAmmoBehavior();
void SetAmmoAmount(int amount){ammoAmount = amount;};
int GetAmmoAmount(){return ammoAmount;};



#endif