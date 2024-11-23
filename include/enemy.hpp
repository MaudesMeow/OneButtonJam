#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include "globals.hpp"

class Enemy
{
    public:
        Vector2 pos;
        int size;
        bool initiated;
        Enemy() : pos({0,0}) {}
        Enemy(Vector2 pos)
        {
            this->pos = pos;
            size = 12;

        }

        void EnemyBehavior();
    };



#endif