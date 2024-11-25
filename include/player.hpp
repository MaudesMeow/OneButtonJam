#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "globals.hpp"
#include "ammo.hpp"

class Player
{
    public:
        int direction;
        Vector2 pos;
        Texture2D playerSprite;
        float speed;
        int ammoCount;
        bool canShoot;
        vector<Ammo*> ammoInventory;

        Player() : playerSprite(), pos({0, 0}) {}
        Player(Texture2D playerSprite, Vector2 pos)
        {
            this->playerSprite = playerSprite;
            this->pos = pos;
            direction = 1;
            speed = 160;
            ammoCount = 2;
            canShoot = true;
        }


    
    void AnimatePlayer();
    void HandleInput();
    int GetAmmoCount(){return ammoCount;};
    void SetAmmoCount(int amount){ammoCount = amount;};

};

#endif 