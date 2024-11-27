#include "enemy.hpp"

void Enemy::DrawEnemies()
{
    int numFrames = 4;
    int frameWidth = sprite.width / numFrames; // Width of a single frame
    int frameHeight = sprite.height; // Assuming all frames have the same height
    float frameTime = 0.3f; // Time per frame in seconds 
    int currentFrame = static_cast<int>(GetTime() / frameTime) % numFrames;

    Rectangle src = 
    {
        (float)(frameWidth * currentFrame), // X position of the current frame
        0, // Y position of the current frame (assuming a single row of frames)
        (float)frameWidth, // Width of the current frame
        (float)frameHeight // Height of the current frame  
    } ;

    Rectangle dest = 
    {
        pos.x, // X position on the screen
        pos.y, // Y position on the screen
        (float)frameWidth *3, // Width of the drawn framed)
        (float)frameHeight *3 // Height of the drawn frame (scaled)
    };

    DrawTexturePro(sprite,src,dest,{0,0},0,WHITE);
    
    // DrawRectangleLines(pos.x,pos.y,48,48,RED);
    
}

void UpdateEnemyBehavior(vector<Enemy*> &enemyList, int enemyCount,Texture2D sprite)
{
    // Add new enemies if needed
    if (enemyList.size() < enemyCount)
    {
        enemyList.push_back(PopulateEnemies(enemyList,sprite));
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


Enemy* PopulateEnemies(vector<Enemy*> &enemyList, Texture2D sprite)
{
    int xPos, yPos;
    bool positionValid;

    do {
        
        xPos = GetRandomValue(92, GetScreenWidth() - 92);
        yPos = GetRandomValue(-96, -48);
        positionValid = true; // Assume position is valid

        
        for (Enemy* enemy : enemyList)
        {
            if ((xPos > enemy->pos.x && xPos <= enemy->pos.x + 48) &&
                (yPos > enemy->pos.y && yPos <= enemy->pos.y + 48))
            {
                positionValid = false; 
                break; 
            }
        }
    } while (!positionValid); 

    
    return new Enemy(Vector2{(float)xPos, (float)yPos}, sprite);
}

