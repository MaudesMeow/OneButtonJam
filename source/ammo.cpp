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

void Ammo::SetAmmoPos(Vector2 pos, int direction) {
    if (!isActive) return;

    if (!hasFired) {
        bulletPos = pos;
        hitBox.x = bulletPos.x + 8;
        hitBox.y = bulletPos.y - 16;
    } else {
        bulletPos.y -= (speed * GetFrameTime());
        hitBox.x = bulletPos.x + 8;
        hitBox.y = bulletPos.y - 16;
    }

    // Update triangle points
    p1 = {bulletPos.x + 8, bulletPos.y};
    p2 = {bulletPos.x + 24, bulletPos.y};
    p3 = {bulletPos.x + 16, bulletPos.y - 16};
}

void AnimateAmmo(std::vector<Ammo*>& ammoInventory) {
    for (Ammo* ammo : ammoInventory) {
        // Skip drawing if the ammo is inactive
        if (!ammo->isActive) continue;

        if (ammo->hasFired) {
            // Draw fired ammo
            DrawTriangleLines(ammo->p1, ammo->p2, ammo->p3, WHITE);
            DrawRectangleLines(ammo->bulletPos.x + 14, ammo->bulletPos.y + 16, 4, 4, ColorAlpha(WHITE, 1.0f));
            DrawRectangleLines(ammo->bulletPos.x + 14, ammo->bulletPos.y + 24, 4, 4, ColorAlpha(WHITE, 0.8f));
            DrawRectangleLines(ammo->bulletPos.x + 14, ammo->bulletPos.y + 32, 4, 4, ColorAlpha(WHITE, 0.5f));
            DrawRectangleLines(ammo->bulletPos.x + 14, ammo->bulletPos.y + 36, 4, 4, ColorAlpha(WHITE, 0.5f));
            DrawRectangleLines(ammo->bulletPos.x + 14, ammo->bulletPos.y + 40, 4, 4, ColorAlpha(WHITE, 0.3f));
            DrawRectangleLines(ammo->bulletPos.x + 14, ammo->bulletPos.y + 44, 4, 4, ColorAlpha(WHITE, 0.3f));
        } else {
            // Draw idle ammo
            DrawTriangleLines(ammo->p1, ammo->p2, ammo->p3, WHITE);
        }
    }
}




Ammo* PopulateAmmo()
{
    return new Ammo();
}