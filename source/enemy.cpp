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
    switch (type)
    {
    case FAST:
            frameWidth = (float)frameWidth *2; // Width of the drawn framed)
            frameHeight =(float)frameHeight *2; // Height of the drawn frame (scaled)
        break;
    
    case AVERAGE:
            frameWidth = (float)frameWidth *4; // Width of the drawn framed)
            frameHeight =(float)frameHeight *4; // Height of the drawn frame (scaled)
        break;
    default:
        break;

    }
    Rectangle dest = 
    {
        pos.x, // X position on the screen
        pos.y, // Y position on the screen
        (float)frameWidth, // Width of the drawn framed)
        (float)frameHeight // Height of the drawn frame (scaled)
    };

    DrawTexturePro(sprite,src,dest,{0,0},0,WHITE);
    
    DrawRectangleLinesEx(hitBox,1,RED);
    
}

void UpdateEnemyBehavior(vector<Enemy*> &enemyList, int enemyCount,Texture2D eyeSprite, Texture2D handSprite)
{
    // Add new enemies if needed
    if (enemyList.size() < enemyCount)
    {
        enemyList.push_back(PopulateEnemies(enemyList,eyeSprite,handSprite));
    }

    // Iterate over the enemy list and update behavior
    for (auto it = enemyList.begin(); it != enemyList.end(); )
    {
        Enemy* enemy = *it;
        enemy->counter += GetFrameTime();
        // Update enemy position
        if (enemy->counter > enemy->waitTime)
        {
            enemy->pos.y += (enemy->speed * GetFrameTime());
            enemy->hitBox.x = enemy->pos.x;
            enemy->hitBox.y = enemy->pos.y;
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


Enemy* PopulateEnemies(vector<Enemy*> &enemyList, Texture2D eyeSprite, Texture2D handSprite)
{
    int xPos, yPos;
    bool positionValid;
    int enemyChoice = GetRandomValue(0,1);

    do {
        
        xPos = GetRandomValue(92, GetScreenWidth() - 92);
        yPos = GetRandomValue(-128, -64);
        positionValid = true; // Assume position is valid

        
        // for (Enemy* enemy : enemyList)
        // {
        //      if (CheckCollisionRecs(Rectangle{(float)xPos,(float)yPos,32,32},enemy->hitBox))
        //     {
        //         positionValid = false; 
        //         break; 
        //     }
        // }
    } while (!positionValid); 

    if (enemyChoice == 0)
    {
        return new EyeEnemy(Vector2{(float)xPos, (float)yPos}, eyeSprite);
    }
    else 
    {
        return new HandEnemy(Vector2{(float)xPos, (float)yPos}, handSprite);      
    }

}

