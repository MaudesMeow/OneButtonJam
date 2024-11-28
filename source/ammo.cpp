#include "ammo.hpp"

void DisplayAmmo(int ammoCount) // Display function for side of screen to let player know how much ammo they have 
{
    
    for (int i = 0 ;  i < ammoCount; i++)
    {
        switch (i)
        {
        case 0:
            DrawTriangleLines(Vector2{8,48},Vector2{24,48},Vector2{16,32},WHITE);
            break;
        case 1:
            DrawTriangleLines(Vector2{32,48},Vector2{48,48},Vector2{40,32},WHITE);
            break;
        case 2:
            DrawTriangleLines(Vector2{56,48},Vector2{72,48},Vector2{64,32},WHITE);
            break;    
        default:
            break;
        }
    }
    

}
void AnimateAmmo(vector<Ammo*> &ammo) // Display function for side of screen to let player know how much ammo they have 
{

        if (!ammo.empty())
        {
            for (Ammo *am : ammo)
            {
                if (am->hasFired)
                {

                
                    DrawTriangleLines(am->p1, am->p2, am->p3, WHITE);
                    DrawRectangleLines(am->lastX-2,am->bulletPos.y, 4,4,ColorAlpha(Color{255,255,255},0.8));
                    
                    DrawRectangleLines(am->lastX-2,am->bulletPos.y+2, 4,4,ColorAlpha(Color{255,255,255},0.5));
                    
                    DrawRectangleLines(am->lastX-2,am->bulletPos.y+4, 4,4,ColorAlpha(Color{255,255,255},0.3));
                    
                    DrawRectangleLines(am->lastX-2,am->bulletPos.y+6, 4,4,ColorAlpha(Color{255,255,255},0.15));
                    DrawRectangleLines(am->lastX-2,am->bulletPos.y+7, 4,4,ColorAlpha(Color{255,255,255},0.10));
                    DrawRectangleLines(am->lastX-2,am->bulletPos.y+8, 4,4,ColorAlpha(Color{255,255,255},0.05));
                    DrawRectangleLines(am->lastX-2,am->bulletPos.y+9, 4,4,ColorAlpha(Color{255,255,255},0.03));
                    DrawRectangleLines(am->lastX-2,am->bulletPos.y+10, 4,4,ColorAlpha(Color{255,255,255},0.01));  
                }
            }
        }

}




Ammo* PopulateAmmo()
{
    return new Ammo();
}