#include "enemy.hpp"


void Enemy::EnemyBehavior()
{
    
    if (pos.y > GetScreenHeight()) 
    {
        pos.y = 0;
        pos.x = GetRandomValue(0,GetScreenWidth());
    };
    pos.y += (240*GetFrameTime());
    DrawRectangle(pos.x,pos.y,size,size,RED);
}