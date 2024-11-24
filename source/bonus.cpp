#include "bonus.hpp"

   Vector2 p1, p2, p3;
void AmmosBonus::DrawBonus()
{
    
    
    DrawTriangleLines(p1, p2, p3, WHITE);
}


void Teleporter::DrawBonus()
{

    DrawCircleV(pos, 20, BLUE);
}

void HandleBonusCollisions(Player *player)
{

}
void PopulateBonuses()
{
    
}
