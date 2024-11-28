#ifndef BONUS_HEADER
#define BONUS_HEADER

#include "globals.hpp"
#include "player.hpp"

enum BonusType
{
    AMMO,
    TELEPORTER
};

class Bonus
{
public:
    Vector2 pos,p1,p2,p3;
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
        Vector2 p4,p5,p6,p7,p8,p9;
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


void HandleBonusCollisions(Player *player);
void UpdateBonusBehavior(vector<Bonus*> &bonusList, Player *player);
Bonus* PopulateBonuses();

#endif
