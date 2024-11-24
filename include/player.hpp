#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "globals.hpp"

class Player
{
    public:
        int direction;
        Vector2 pos;
        Texture2D playerSprite;
        float speed;
        int ammoCount;

        Player() : playerSprite(), pos({0, 0}) {}
        Player(Texture2D playerSprite, Vector2 pos)
        {
            this->playerSprite = playerSprite;
            this->pos = pos;
            direction = 1;
            speed = 160;
            ammoCount = 3;
        }


    
    void AnimatePlayer();
    void HandleInput();
    int ReturnAmmoCount(){return ammoCount;};

};

#endif 