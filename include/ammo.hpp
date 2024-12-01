#ifndef AMMO_HEADER
#define AMMO_HEADER

#include "globals.hpp"



class Ammo {
public:
    bool hasFired = false;
    bool hasCollided = false;
    bool isActive = false; // New: Controls ammo state
    Vector2 bulletPos = {0, 0};
    Rectangle hitBox = {0, 0, 16, 16};
    int speed = 300;
    Vector2 p1, p2, p3;

    void Reset() {
        hasFired = false;
        hasCollided = false;
        isActive = false; // Reset to inactive state
        bulletPos = {0, 0};
    }

    void SetAmmoPos(Vector2 pos, int direction);
    
};


void DisplayAmmo(int ammoCount);

void AnimateAmmo(vector<Ammo*> &ammo);  // Display function for side of screen to let player know how much ammo they have 
void UpdateAmmoBehavior();
Ammo* PopulateAmmo();




#endif