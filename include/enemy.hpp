#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include "globals.hpp"
#include "ammo.hpp"
#include "player.hpp"
#include "bonus.hpp"

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
        int direction;
        float directionTimer;
        int rotation;
        int hitCount;

        Texture2D sprite;

        virtual ~Enemy() = default;


        void DrawEnemies();
        void SetHitCount(int count){hitCount = count;}
        int GetHitCount(){return hitCount;}
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
            speed = 280;
            direction = 1;
            directionTimer =0;
            rotation = 45;
            hitCount = 1;

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
            rotation = 0;
            hitCount = 2;
        }
};

void UpdateEnemyBehavior(vector<Enemy*> &enemyList, Player *player,Texture2D eyeSprite, Texture2D handSprite,vector<Ammo*> &ammo,vector<Bonus*> &bonusList);
Enemy* PopulateEnemies(vector<Enemy*> &enemyList, Texture2D eyeSprite, Texture2D handSprite, int score);

#endif