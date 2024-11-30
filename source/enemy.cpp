#include "enemy.hpp"

void Enemy::DrawEnemies()
{
    Rectangle dest, src;
    Vector2 origin;

    int numFrames = 4;
    int frameWidth = sprite.width / numFrames; // Width of a single frame
    int frameHeight = sprite.height; // Assuming all frames have the same height


    float frameTime = 0.3f; // Time per frame in seconds 
    int currentFrame = static_cast<int>(GetTime() / frameTime) % numFrames;

    src = 
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
            dest = 
            {
                pos.x, // X position on the screen
                pos.y, // Y position on the screen
                (float)frameWidth, // Width of the drawn framed)
                (float)frameHeight // Height of the drawn frame (scaled)
            };
            origin = 
            {
                dest.width / 2.0f, // X offset to the center of the destination rectangle
                dest.height / 2.0f // Y offset to the center of the destination rectangle
            };

        break;
    
    case AVERAGE:
            frameWidth = (float)frameWidth *4; // Width of the drawn framed)
            frameHeight =(float)frameHeight *4; // Height of the drawn frame (scaled)
            dest = 
            {
                pos.x, // X position on the screen
                pos.y, // Y position on the screen
                (float)frameWidth, // Width of the drawn framed)
                (float)frameHeight // Height of the drawn frame (scaled)
            };
            origin = {0,0};

        break;
    default:
        break;

    }

    DrawTexturePro(sprite,src,dest,origin,rotation,WHITE);
    
    
    // DrawRectangleLinesEx(hitBox,1,RED);
    
}

void UpdateEnemyBehavior(vector<Enemy*> &enemyList, Player *player,Texture2D eyeSprite, Texture2D handSprite, vector<Ammo*> &ammo)
{
    int enemyCount = 0;
    
    if (player->score < 1000)
    {
        enemyCount = 12;
    }
    else
    {
        enemyCount = 24;
    }

    if (enemyList.size() < enemyCount)
    {
        enemyList.push_back(PopulateEnemies(enemyList,eyeSprite,handSprite,player->score));
    }

    // Iterate over the enemy list and update behavior
    for (auto it = enemyList.begin(); it != enemyList.end(); )
    {
        Enemy* enemy = *it;
        enemy->counter += GetFrameTime();
        enemy->directionTimer += GetFrameTime();
        // Update enemy position

        switch (enemy->type)
        {
        case FAST:
            if (enemy->counter > enemy->waitTime)
            {
                if (enemy->pos.x <= 92 || enemy->pos.x >= GetScreenWidth()-92)
                {
                    enemy->direction *= -1;
                    enemy->directionTimer = 0;
                }
                if (enemy->directionTimer > 0.5)
                {
                    enemy->direction *= -1;
                    enemy->rotation = (enemy->direction > 0) ?  enemy->rotation = -45 : enemy->rotation = 45 ;

                    enemy->directionTimer = 0;
                }
                enemy->pos.y += (enemy->speed * GetFrameTime());
                enemy->pos.x += (enemy->speed*enemy->direction*GetFrameTime());
                enemy->hitBox.x = enemy->pos.x - 12;
                enemy->hitBox.y = enemy->pos.y -16;
            }
            break;
        case AVERAGE:
            if (enemy->counter > enemy->waitTime)
            {
                enemy->pos.y += (enemy->speed * GetFrameTime());
                enemy->hitBox.x = enemy->pos.x;
                enemy->hitBox.y = enemy->pos.y;
            }
            break;
        
        default:
            break;
        }


        // Check if the enemy is off-screen and mark it as dead
        if (enemy->pos.y > GetScreenHeight()) 
        {
            enemy->isAlive = false;
        }

        if (CheckCollisionRecs(player->hitBox,enemy->hitBox))
        {
            score = 0;
            player->SetPlayerScore(0);
        }

        for (Ammo *ammo : ammo)
        {
            if (CheckCollisionRecs(ammo->hitBox,enemy->hitBox) && ammo->hasFired)
            {
                
                ammo->hasCollided = true;
                enemy->SetHitCount(enemy->GetHitCount() - 1);

                if (enemy->hitCount <= 0)
                {
                    enemy->isAlive = false;
                }


            }
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


Enemy* PopulateEnemies(vector<Enemy*> &enemyList, Texture2D eyeSprite, Texture2D handSprite,int score)
{
    int xPos, yPos;
    bool positionValid;
    int enemyChoice = 0;

    if (score < 2000)
    {
        enemyChoice = 0;
    }
    else
    {
        enemyChoice = GetRandomValue(0,1);
    }


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

