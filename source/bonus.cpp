#include "bonus.hpp"

int bonusCount=0; 
int ammoBonusCounter=0;
int ammoBonusAmount=0;
int healthBonusCounter=0;
int healthBonusAmount=0;

void AmmosBonus::DrawBonus()
{
    

    

    DrawTriangleLines(p1, p2, p3, WHITE);
    DrawTriangleLines(p4,p5,p6,ColorAlpha(Color{255,255,255},0.5));
    DrawTriangleLines(p7,p8,p9,ColorAlpha(Color{255,255,255},0.3));
    // DrawRectangleLinesEx(hitBox,2,GREEN);
    

    p1.y += (320*GetFrameTime());
    p2.y += (320*GetFrameTime());
    p3.y += (320*GetFrameTime());
    hitBox.x = p1.x ;
    hitBox.y = p1.y-32;
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

void HealthBonus::DrawBonus()
{

    pos.y += (320*GetFrameTime());
    hitBox.y = pos.y;
    int numFrames = 1;
    int frameWidth = sprite.width / numFrames; // Width of a single frame
    int frameHeight = sprite.height; // Assuming all frames have the same height
    float frameTime = 0.3f; // Time per frame in seconds 
    int currentFrame = static_cast<int>(GetTime() / frameTime) % numFrames;

    
    Rectangle src = 
    {
        (float)(frameWidth * currentFrame), // X position of the current frame
        0, // Y position of the current frame (assuming a single row of frames)
        (float)frameWidth, // Width of the current frame
        (float)frameHeight // Height of the current frame  
    } ;

    Rectangle dest = 
    {
        pos.x, // X position on the screen
        pos.y, // Y position on the screen
        (float)frameWidth *2, // Width of the drawn framed)
        (float)frameHeight *2 // Height of the drawn frame (scaled)
    };


    DrawTexturePro(sprite,src,dest,{0,0},0,WHITE);
}

void TeleporterBonus::DrawBonus()
{

    // DrawCircleLines(pos.x,pos.y, 20, BLUE);
    pos.y += (240 *GetFrameTime());
    if (pos.y > GetScreenHeight()+16)
    {
        isValid = false;
    }
}

Bonus* PopulateBonuses(Texture2D sprite)
{

    int bonusOption = GetRandomValue(1,1);

    if (ammoBonusCounter != ammoBonusAmount)
    {
        ammoBonusCounter++;
        return new AmmosBonus(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),(float)GetRandomValue(-24,-16)});
    }
    else if (healthBonusCounter != healthBonusAmount)
    {
        healthBonusCounter++;
        return new HealthBonus(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),(float)GetRandomValue(-24,-16)},sprite);
    }
    else
    {
        switch (bonusOption)
        {
        case 1:
            return new AmmosBonus(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),(float)GetRandomValue(-128,-16)});
            break;
        case 2: 
            return new TeleporterBonus(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),-16});
            break;
        default:
            return NULL;
            break;
        }          
    }
    switch (bonusOption)
    {
    case 1:
        return new AmmosBonus(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),(float)GetRandomValue(-128,-16)});
        break;
    case 2: 
        return new TeleporterBonus(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),-16});
        break;
    default:
        return NULL;
        break;
    }  
    
}

void UpdateBonusBehavior(vector<Bonus*> &bonusList, Texture2D sprite, Player *player)
{
    // ------------------------------------------------------------------------------------------- HOW MANY BONUSES TO POPULATE


    int bonusCount = 0;
    if (player->score < 500)
    {
        bonusCount = 1;
        ammoBonusAmount = 1;
        healthBonusAmount = 0;
    }
    else if (player->score >= 500 && player->score < 1000)
    {
        bonusCount = 2;
        ammoBonusAmount = 1;
        healthBonusAmount = 1;
    }
    else if(player->score >= 1000 && player->score < 1500)
    {
        bonusCount = 4;
        ammoBonusAmount = 3;
        healthBonusAmount = 1;
    }
    else if(player->score >= 1500 && player->score < 2000)
    {
        bonusCount = 8;
        ammoBonusAmount = 5;
        healthBonusAmount = 3;
    }
    else
    {
        bonusCount = 16;
        ammoBonusAmount = 10;
        healthBonusAmount = 6;
    }

    if (bonusList.size() < bonusCount)
    {
        bonusList.push_back(PopulateBonuses(sprite));
    }


    // Iterate over the bonus list, handle validity, and update behavior in one pass
    for (auto it = bonusList.begin(); it != bonusList.end(); )
    {
        Bonus* bonus = *it;

        // Check bonus behavior based on type
        switch (bonus->type)
        {
        case AMMO:
            if (CheckCollisionRecs(player->hitBox,bonus->hitBox))
            {
                player->SetAmmoCount(3);
                player->canShoot = true;
                bonus->isValid = false;
                ammoBonusCounter--;
            }
            break;
        case HEALTH:
             if (CheckCollisionRecs(player->hitBox,bonus->hitBox))
            {
                
                if (player->GetPlayerHealth() < 3)
                {
                    player->SetPlayerHealth(3);
                }
                bonus->isValid = false;
                healthBonusCounter--;
            }
            break;           
        case TELEPORTER:
            if (CheckCollisionCircleRec(bonus->pos, bonus->radius, player->hitBox))
            {
                if (!player->hasTeleported)
                {
                    Vector2 tempBonus = bonusList[GetRandomValue(0, (bonusList.size()) - 1)]->pos;
                    player->pos = tempBonus;
                    player->hitBox.x = player->pos.x;
                    player->hitBox.y = player->pos.y;
                    player->hasTeleported = true;  // Mark as teleported
                    bonus->isValid = false;
                }
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

void ClearBonus(vector<Bonus*> &bonusList)
{
    bonusCount=0; 
    
    ammoBonusCounter=0;
    ammoBonusAmount=0;
    healthBonusCounter=0;
    healthBonusAmount=0;    
    for (Bonus* deleteBonus : bonusList) 
    {
        delete deleteBonus;
    }
    bonusList.clear();   
    
}

