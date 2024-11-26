#include "enemy.hpp"

void Enemy::DrawEnemies()
{
    
    
        DrawRectangleLines(pos.x,pos.y,size,size,RED);
    
}

void UpdateEnemyBehavior(std::vector<Enemy*> &enemyList, int enemyCount)
{
    // Add new enemies if needed
    if (enemyList.size() < enemyCount)
    {
        enemyList.push_back(PopulateEnemies());
    }

    // Iterate over the enemy list and update behavior
    for (auto it = enemyList.begin(); it != enemyList.end(); )
    {
        Enemy* enemy = *it;
        enemy->counter += GetFrameTime();
        // Update enemy position
        if (enemy->counter > enemy->waitTime)
        {
            enemy->pos.y += (240 * GetFrameTime());
        }


        // Check if the enemy is off-screen and mark it as dead
        if (enemy->pos.y > GetScreenHeight()) 
        {
            enemy->isAlive = false;
        }

        // Remove dead enemies from the list
        if (!enemy->isAlive)
        {
            // Delete the enemy object to prevent memory leaks
            delete enemy;  
            
            // Erase returns the next valid iterator
            it = enemyList.erase(it);
        }
        else
        {
            // Increment the iterator if the enemy is still alive
            ++it;
        }
    }
}


Enemy* PopulateEnemies()
{
    return new Enemy(Vector2{(float)GetRandomValue(92,GetScreenWidth()-92),-48});
}
