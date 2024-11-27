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

        Texture2D sprite;


        Enemy() : pos({0,0}) {}
        Enemy(Vector2 pos, Texture2D sprite)
        {
            this->pos = pos;
            size = 48;
            type = AVERAGE;
            isAlive = true;
            waitTime = GetRandomValue(0,10);
            counter = 0;
            this->sprite = sprite;
        }

        void DrawEnemies();
    };

void UpdateEnemyBehavior(vector<Enemy*> &enemyList, int enemyCount,Texture2D sprite);
Enemy* PopulateEnemies(vector<Enemy*> &enemyList,Texture2D sprite);

#endif