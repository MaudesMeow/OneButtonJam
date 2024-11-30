#include "ammo.hpp"

void DisplayAmmo(int ammoCount) // Display function for side of screen to let player know how much ammo they have 
{
    
    for (int i = 0 ;  i < ammoCount; i++)
    {
        switch (i)
        {
        case 0:
            DrawTriangleLines(Vector2{16,48},Vector2{32,48},Vector2{24,32},WHITE);
            break;
        case 1:
            DrawTriangleLines(Vector2{40,48},Vector2{56,48},Vector2{48,32},WHITE);
            break;
        case 2:
            DrawTriangleLines(Vector2{64,48},Vector2{80,48},Vector2{72,32},WHITE);
            break;    
        default:
            break;
        }
    }
    

}

void Ammo::SetAmmoPos(Vector2 pos,int direction)
{

    if (!hasFired)
    {
        bulletPos = pos;
        hitBox.x = bulletPos.x+8;
        hitBox.y = bulletPos.y-16;
        p1.x = bulletPos.x+8;
        p1.y = bulletPos.y;
        p2.x = bulletPos.x + 24;
        p2.y = bulletPos.y;
        p3.x = bulletPos.x + 16;
        p3.y = bulletPos.y - 16;
    }
    else
    {
        bulletPos.y -= (speed*GetFrameTime());
        hitBox.x = bulletPos.x+8;
        hitBox.y = bulletPos.y-16;
        p1.x = bulletPos.x+8;
        p1.y = bulletPos.y;
        p2.x = bulletPos.x + 24;
        p2.y = bulletPos.y;
        p3.x = bulletPos.x + 16;
        p3.y = bulletPos.y - 16;

    }
            

}
void AnimateAmmo(vector<Ammo*> &ammo) // Display function for side of screen to let player know how much ammo they have 
{

        // if (!ammo.empty())
        // {
        //     for (Ammo *am : ammo)
        //     {
                for (int i = 0; i < ammo.size(); i++)
                {
                Ammo *am = ammo[i];
                
                if (am->hasFired)
                {

                    DrawRectangleLinesEx(am->hitBox,1,RED);
                    DrawTriangleLines(am->p1, am->p2, am->p3, WHITE);
                    DrawRectangleLines(am->bulletPos.x+14,am->bulletPos.y+16, 4,4,ColorAlpha(Color{255,255,255},1.0));
                    
                    DrawRectangleLines(am->bulletPos.x+14,am->bulletPos.y+24, 4,4,ColorAlpha(Color{255,255,255},0.8));
                    
                    DrawRectangleLines(am->bulletPos.x+14,am->bulletPos.y+32, 4,4,ColorAlpha(Color{255,255,255},0.5));
                    
                    DrawRectangleLines(am->bulletPos.x+14,am->bulletPos.y+36, 4,4,ColorAlpha(Color{255,255,255},0.5));
                    DrawRectangleLines(am->bulletPos.x+14,am->bulletPos.y+40, 4,4,ColorAlpha(Color{255,255,255},0.3));
                    DrawRectangleLines(am->bulletPos.x+14,am->bulletPos.y+44, 4,4,ColorAlpha(Color{255,255,255},0.3));
                    // DrawRectangleLines(am->p1.x-2,am->p1.y+9, 4,4,ColorAlpha(Color{255,255,255},0.03));
                    // DrawRectangleLines(am->p1.x-2,am->p1.y+10, 4,4,ColorAlpha(Color{255,255,255},0.01));  
                }
                else
                {
                    // cout << " drawing " << i << endl;
                    DrawRectangleLinesEx(am->hitBox,1,RED);
                    DrawTriangleLines(am->p1, am->p2, am->p3, WHITE);
                    
                }
                }
        //     }
        // }

}




Ammo* PopulateAmmo()
{
    return new Ammo();
}