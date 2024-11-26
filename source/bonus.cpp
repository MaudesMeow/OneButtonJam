#include "bonus.hpp"



void AmmosBonus::DrawBonus()
{
    

    

    DrawTriangleLines(p1, p2, p3, WHITE);
    DrawTriangleLines(p4,p5,p6,ColorAlpha(Color{255,255,255},0.5));
    DrawTriangleLines(p7,p8,p9,ColorAlpha(Color{255,255,255},0.3));
    

    p1.y += (320*GetFrameTime());
    p2.y += (320*GetFrameTime());
    p3.y += (320*GetFrameTime());
    p4 = {p1.x+8 ,p1.y-6};
    p5 = {p2.x-8,p2.y-6};
    p6 = {p3.x ,p3.y+8};
    p7 = {p4.x+4 ,p4.y-4};
    p8 = {p5.x-4,p5.y-4};
    p9 = {p6.x ,p6.y+4};


    if (p1.y > GetScreenHeight()+16)
    {
        isValid = false;
    }

}


void TeleporterBonus::DrawBonus()
{

    DrawCircleLines(pos.x,pos.y, 20, BLUE);
    pos.y += (240 *GetFrameTime());
    if (pos.y > GetScreenHeight()+16)
    {
        isValid = false;
    }
}

Bonus* PopulateBonuses()
{

    int bonusOption = GetRandomValue(1,2);
    switch (bonusOption)
    {
    case 1:
        return new AmmosBonus(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),-16});
        break;
    case 2: 
        return new TeleporterBonus(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),-16});
        break;
    default:
        return NULL;
        break;
    }  
    
}

void UpdateBonusBehavior(std::vector<Bonus*> &bonusList, Player *player)
{
    // Populate bonuses if needed
    while (bonusList.size() < 3)
    {
        Bonus* newBonus = PopulateBonuses();
        if (newBonus)  // Ensure newBonus is not nullptr
        {
            bonusList.push_back(newBonus);
        }
    }

    // Iterate over the bonus list, handle validity, and update behavior in one pass
    for (auto it = bonusList.begin(); it != bonusList.end(); )
    {
        Bonus* bonus = *it;

        // Check bonus behavior based on type
        switch (bonus->type)
        {
        case AMMO:
            if (CheckCollisionPointTriangle(Vector2{player->pos.x + 16, player->pos.y}, bonus->p1, bonus->p2, bonus->p3))
            {
                player->SetAmmoCount(2);
                player->canShoot = true;
                bonus->isValid = false;
            }
            break;
        
        default:
            break;
        }

        // Remove invalid bonuses after updating behavior
        if (!bonus->isValid)
        {
            delete bonus;  // Free memory to prevent leaks
            it = bonusList.erase(it);  // Erase and update iterator
        }
        else
        {
            ++it;  // Move to the next element if no removal occurred
        }
    }
}

