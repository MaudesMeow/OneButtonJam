#ifndef AMMO_HEADER
#define AMMO_HEADER

#include "globals.hpp"

class Ammo
{
    Vector2 pos,p1,p2,p3;
    float speed;

};

void DisplayAmmo(int ammoAmount);
void AnimateFiredAmmo();



#endif