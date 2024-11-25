#include "enemy.hpp"

void Enemy::DrawEnemies()
{
    
    
        DrawRectangleLines(pos.x,pos.y,size,size,RED);
    
}

void UpdateEnemyBehavior(vector<Enemy*> &enemyList, int enemyCount)
{
    if (enemyList.size() < enemyCount)
    {
        // cout << "size of enemy list is " << enemyList.size() << endl;
        enemyList.push_back(PopulateEnemies());
    }
    for (Enemy *enemy : enemyList)
    {

        enemy->pos.y += (240*GetFrameTime());
        if (enemy->pos.y > GetScreenHeight()) 
        {
            enemy->isAlive = false;
        };

        for (auto it = enemyList.begin(); it != enemyList.end(); ) 
        {
            if (!(*it)->isAlive) 
                {
                it = enemyList.erase(it); 
                } else 
                {
                    ++it;
                }
        }


        
    }

}

Enemy* PopulateEnemies()
{
    return new Enemy((Vector2){GetRandomValue(92,GetScreenWidth()-92),GetRandomValue(-32,-8)});
}
