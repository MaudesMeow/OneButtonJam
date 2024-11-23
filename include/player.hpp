#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "globals.hpp"

class Player
{
    public:
        int direction;
        Vector2 pos;
        Texture2D playerSprite;

        Player() : playerSprite(), pos({0, 0}) {}
        Player(Texture2D playerSprite, Vector2 pos)
        {
            this->playerSprite = playerSprite;
            this->pos = pos;
            direction = 1;
        }


    
    void AnimatePlayer();
    void HandleInput();

};

#endif 