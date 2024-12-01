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


Bonus* PopulateBonuses(Texture2D sprite)
{

    int bonusOption = GetRandomValue(1,1);

    if (ammoBonusCounter < ammoBonusAmount)
    {
        ammoBonusCounter++;
        return new AmmosBonus(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),-16});
    }
    else if (healthBonusCounter < healthBonusAmount)
    {
        healthBonusCounter++;
        return new HealthBonus(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),-16},sprite);
    }
    else
    {
        switch (bonusOption)
        {
        case 1:
            return new AmmosBonus(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),(float)GetRandomValue(-128,-16)});
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

    default:
        return NULL;
        break;
    }  
    
}

void UpdateBonusBehavior(vector<Bonus*> &bonusList, Texture2D sprite, Player *player)
{
    // ------------------------------------------------------------------------------------------- HOW MANY BONUSES TO POPULATE


    int bonusCount = 0;
    if (player->score < 5)
    {
        bonusCount = 0;
        ammoBonusAmount = 0;
        healthBonusAmount = 0;
    }
    else if (player->score >= 5 && player->score < 800)
    {
        bonusCount = 2;
        ammoBonusAmount = 1;
        healthBonusAmount = 1;
    }
    else if(player->score >= 800 && player->score < 1200)
    {
        bonusCount = 3;
        ammoBonusAmount = 2;
        healthBonusAmount = 1;
    }
    else if(player->score >= 1200 && player->score < 1600)
    {
        bonusCount = 4;
        ammoBonusAmount = 3;
        healthBonusAmount = 1;
    }
    else
    {
        bonusCount = 5;
        ammoBonusAmount = 3;
        healthBonusAmount = 2;
    }

    if (bonusList.size() < bonusCount)
    {
        bonusList.push_back(PopulateBonuses(sprite));
    }


    // Iterate over the bonus list, handle validity, and update behavior in one pass
    for (Bonus* bonus : bonusList)
    {
        
 

        // Check bonus behavior based on type
        switch (bonus->type)
        {
        case AMMO:
            if (bonus->pos.y > GetScreenHeight())
            {
                bonus->isValid = false;
                
            }
            if (CheckCollisionRecs(player->hitBox,bonus->hitBox))
            {
                player->SetAmmoCount(3);
                
                PlaySound(ammoCollect);
                player->canShoot = true;
                bonus->isValid = false;
                
            }
            break;
        case HEALTH:
            if (bonus->pos.y > GetScreenHeight())
            {
                bonus->isValid = false;
                
            }
             if (CheckCollisionRecs(player->hitBox,bonus->hitBox))
            {
                
                PlaySound(healthCollect);
                
                if (player->GetPlayerHealth() < 3)
                {
                    
                    
                    player->SetPlayerHealth(3);
                }
                bonus->isValid = false;
                
            }
            break;           

        default:
            break;
        }

        // -----------------------------------------------------------------------------Remove invalid bonuses after updating behavior
        if (!bonus->isValid)
        {
            bonus->pos = Vector2{(float)GetRandomValue(92, GetScreenWidth() - 92), (float)GetRandomValue(-128,-16)};
            bonus->hitBox.x = bonus->pos.x;
            bonus->hitBox.y = bonus->pos.y;
            // For AmmosBonus, reset the triangle points and hitbox
            if (bonus->type == AMMO)
            {
                
                bonus->p1 = bonus->pos;
                bonus->p1 = {bonus->pos.x -16, bonus->pos.y + 32};
                bonus->p2 = {bonus->pos.x +16, bonus->pos.y + 32};
                bonus->p3 = {bonus->pos.x, bonus->pos.y };
                bonus->p4 = {bonus->p1.x ,bonus->p1.y};
                bonus->p5 = {bonus->p2.x,bonus->p1.y};
                bonus->p6 = {bonus->p3.x ,bonus->p1.y};
                bonus->p7 = {bonus->p4.x+2 ,bonus->p4.y-2};
                bonus->p8 = {bonus->p5.x-2,bonus->p5.y-2};
                bonus->p9 = {bonus->p6.x ,bonus->p6.y+2};

            }

            bonus->isValid = true;
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

