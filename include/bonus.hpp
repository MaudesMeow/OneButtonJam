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
    Vector2 pos;
    BonusType type;

    
    virtual ~Bonus() = default;

    
    virtual void DrawBonus() = 0;
};

class AmmosBonus : public Bonus
{
public:

    Vector2 p1,p2,p3;

    AmmosBonus() : Bonus()
    {
        type = AMMO;
        pos = { 0, 0 }; 
    }

    AmmosBonus(Vector2 trianglePos) : Bonus()
    {
        type = AMMO;
        p1 = {trianglePos.x -16, trianglePos.y + 32};
        p2 = {trianglePos.x +16, trianglePos.y + 32};
        p3 = {trianglePos.x, trianglePos.y };
    }

    void DrawBonus() override;
};

class Teleporter : public Bonus
{
public:
    Teleporter()
    {
        type = TELEPORTER;
    }

    
    void DrawBonus() override;
};


void HandleBonusCollisions(Player *player);
void PopulateBonuses();

#endif
