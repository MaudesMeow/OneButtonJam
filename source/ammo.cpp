#include "ammo.hpp"

void DisplayAmmo(int ammoAmount) // Display function for side of screen to let player know how much ammo they have 
{
    for (int i = 0; i < ammoAmount; i++)
    {
        switch (i)
        {
        case 0:
            DrawTriangleLines((Vector2){8,48},(Vector2){24,48},(Vector2){16,32},WHITE);
            break;
        case 1:
            DrawTriangleLines((Vector2){32,48},(Vector2){48,48},(Vector2){40,32},WHITE);
            break;
        case 2:
            DrawTriangleLines((Vector2){56,48},(Vector2){72,48},(Vector2){64,32},WHITE);
            break;    
        default:
            break;
        }
    }
    

}

void AnimateFiredAmmo()
{

}