#ifndef GAMEPLAY_HEADER
#define GAMEPLAY_HEADER

#include "player.hpp"
#include "globals.hpp"

enum BonusType
{
    AMMO,
    TELEPORTER
};

void HandleBonusCollisions(Player *player);
void PopulateBonuses();

#endif