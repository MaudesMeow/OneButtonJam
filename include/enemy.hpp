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
        Rectangle hitBox;
        float speed;

        Texture2D sprite;

        virtual ~Enemy() = default;


        void DrawEnemies() ;
    };

class EyeEnemy : public Enemy
{
    public:
        EyeEnemy() : Enemy()
        {
            pos = {0,0};
        }
        EyeEnemy(Vector2 pos, Texture2D sprite) : Enemy()
        {
            this->pos = pos;
            size = 48;
            type = FAST;
            isAlive = true;
            waitTime = GetRandomValue(0,10);
            counter = 0;
            this->sprite = sprite;
            hitBox = Rectangle{pos.x,pos.y,32,32};
            speed = 480;
        }

};

class HandEnemy : public Enemy
{
    public:
        HandEnemy() : Enemy()
        {
            pos = {0,0};
        }
        HandEnemy(Vector2 pos, Texture2D sprite) : Enemy()
        {
            this->pos = pos;
            size = 48;
            type = AVERAGE;
            isAlive = true;
            waitTime = GetRandomValue(0,10);
            counter = 0;
            this->sprite = sprite;
            hitBox = Rectangle{pos.x,pos.y,64,64};
            speed = 240;
        }
};

void UpdateEnemyBehavior(vector<Enemy*> &enemyList, int enemyCount,Texture2D eyeSprite, Texture2D handSprite);
Enemy* PopulateEnemies(vector<Enemy*> &enemyList, Texture2D eyeSprite, Texture2D handSprite);

#endif