#ifndef BONUS_HEADER
#define BONUS_HEADER

#include "globals.hpp"
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

        virtual void DrawBonus(BonusType type);
};



class AmmosBonus : public Bonus
{
    virtual void DrawBonus(BonusType type);
};

class Teleporter : public Bonus
{

};

#endif