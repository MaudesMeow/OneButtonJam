#ifndef BONUS_HEADER
#define BONUS_HEADER

#include "globals.hpp"
#include "player.hpp"

enum BonusType
{
    AMMO,
    TELEPORTER,
    HEALTH
};

class Bonus
{
public:
    Vector2 pos,p1,p2,p3;
    Vector2 p4,p5,p6,p7,p8,p9;
    BonusType type;
    bool isValid;
    int radius;
    Rectangle hitBox;

    
    virtual ~Bonus() = default;

    
    virtual void DrawBonus() = 0;
};

class AmmosBonus : public Bonus
{
public:
        
    AmmosBonus() : Bonus()
    {
        type = AMMO;
        pos = { 0, 0 }; 
        isValid = true;
    }

    AmmosBonus(Vector2 trianglePos) : Bonus()
    {
        type = AMMO;
        hitBox = Rectangle{pos.x-16,pos.y,32,32};
        
        p1 = {trianglePos.x -16, trianglePos.y + 32};
        p2 = {trianglePos.x +16, trianglePos.y + 32};
        p3 = {trianglePos.x, trianglePos.y };
        p4 = {p1.x ,p1.y};
        p5 = {p2.x,p1.y};
        p6 = {p3.x ,p1.y};
        p7 = {p4.x+2 ,p4.y-2};
        p8 = {p5.x-2,p5.y-2};
        p9 = {p6.x ,p6.y+2};

        isValid = true;
    }

    void DrawBonus() override;
};

class TeleporterBonus : public Bonus
{
public:

    TeleporterBonus()
    {
        type = TELEPORTER;
        isValid = true;
    }

    TeleporterBonus(Vector2 pos)
    {
        type = TELEPORTER;
        this->pos = pos;
        isValid = true;
        radius = 20;

    }

    
    void DrawBonus() override;
};

class HealthBonus : public Bonus
{
    public:

        Texture2D sprite;
        HealthBonus()
        {
            isValid = true;
            type = HEALTH;
        }

        HealthBonus(Vector2 pos,Texture2D sprite)
        {
            this->sprite = sprite;
            this->pos = pos;
            hitBox = Rectangle{pos.x-16,pos.y,32,32};
            isValid = true;
            type = HEALTH;
        }

        void DrawBonus() override;

};


void HandleBonusCollisions(Player *player);
void UpdateBonusBehavior(vector<Bonus*> &bonusList, Texture2D sprite,Player *player);
Bonus* PopulateBonuses(Texture2D sprite);

void ClearBonus(vector<Bonus*> &bonusList);

#endif
