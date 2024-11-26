#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include "globals.hpp"

enum EnemyType
{
    FAST,
    SLOW,
    AVERAGE
};

class Enemy
{
    public:
        Vector2 pos;
        int size;
        bool initiated;
        EnemyType type;
        bool isAlive;
        float waitTime;
        float counter;


        Enemy() : pos({0,0}) {}
        Enemy(Vector2 pos)
        {
            this->pos = pos;
            size = 48;
            type = AVERAGE;
            isAlive = true;
            waitTime = GetRandomValue(0,10);
            counter = 0;
        }

        void DrawEnemies();
    };

void UpdateEnemyBehavior(vector<Enemy*> &enemyList, int enemyCount);
Enemy* PopulateEnemies();

#endif