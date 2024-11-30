#include "enemy.hpp"

int smallEnemyCounter =0;
int smallEnemyAmount =0; 
int mediumEnemyCounter =0;
int mediumEnemyAmount=0;
int enemyCount = 0;

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

void UpdateEnemyBehavior(vector<Enemy*> &enemyList, Player *player,Texture2D eyeSprite, Texture2D handSprite, vector<Ammo*> &ammo,vector<Bonus*> &bonusList)
{
    // ------------------------------------------------------------------------------------------- HOW MANY ENEMIES TO POPULATE
    enemyCount = 0;
    
    if (player->score < 500)
    {
        enemyCount = 8;
        smallEnemyAmount = 8;
        mediumEnemyAmount = 0;
        mediumEnemyCounter =0;
        smallEnemyCounter = 0;
    }
    else if (player->score >= 500 && player->score < 1000)
    {
        enemyCount = 16;
        smallEnemyAmount = 14;
        mediumEnemyAmount = 2;
    }
    else if(player->score >= 1000 && player->score < 1500)
    {
        enemyCount = 24;
        smallEnemyAmount = 16;
        mediumEnemyAmount = 8;
    }
    else if(player->score >= 1500 && player->score < 2000)
    {
        enemyCount = 32;
        smallEnemyAmount = 18;
        mediumEnemyAmount = 14;
    }
    else
    {
        enemyCount = 40;
        smallEnemyAmount = 20;
        mediumEnemyAmount = 20;
    }

    if (enemyList.size() < enemyCount)
    {
        enemyList.push_back(PopulateEnemies(enemyList,eyeSprite,handSprite,player->score));
    }

    // ------------------------------------------------------------------------------------------- Iterate over the enemy list and update behavior
    for (auto it = enemyList.begin(); it != enemyList.end(); )
    {
        Enemy* enemy = *it;
        enemy->counter += GetFrameTime();
        enemy->directionTimer += GetFrameTime();
        // ------------------------------------------------------------------------------------------- Update enemy position

        switch (enemy->type)
        {
        case FAST:
            if (enemy->counter > enemy->waitTime)
            {
                if (enemy->pos.x <= 92 || enemy->pos.x >= GetScreenWidth()-92)
                {
                    enemy->direction *= -1;
                    enemy->directionTimer = 0;
                    enemy->rotation *= -1;
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


        // -------------------------------------------------------------------------------------------  Check if the enemy is off-screen and mark it as dead
        if (enemy->pos.y > GetScreenHeight()) 
        {
            enemy->isAlive = false;
        }
        // ------------------------------------------------------------------------------------------- CHECK IF COLLIDES WITH PLAYER
        if (CheckCollisionRecs(player->hitBox,enemy->hitBox) && enemy->isAlive)
        {
            player->SetPlayerHealth(player->GetPlayerHealth()-1);
            if (player->GetPlayerHealth() <= 0)
            {
                player->isReady = false;
                player->SetPlayerScore(0);
                player->SetPlayerHealth(3);
                player->SetAmmoCount(0);
               

                // Clear enemies
                for (Enemy* enemy : enemyList) 
                {
                    delete enemy;
                }
                enemyList.clear();

                // Reset counters
                smallEnemyCounter = 0;
                smallEnemyAmount = 0;
                mediumEnemyCounter = 0;
                mediumEnemyAmount = 0;
                enemyCount = 0;

                // Clear ammo
                for (Ammo* bullet : ammo) 
                {
                    delete bullet;
                }
                ammo.clear();

                // Reset global variables
                globalScore = 0;
                ClearBonus(bonusList);
                break;
               
            }
            enemy->isAlive = false;

            
            
        }
        // ------------------------------------------------------------------------------------------- CHECK IF ENEMY IS SHOT
        for (Ammo *ammo : ammo)
        {
            if (CheckCollisionRecs(ammo->hitBox,enemy->hitBox) && ammo->hasFired)
            {
                
                ammo->hasCollided = true;
                enemy->SetHitCount(enemy->GetHitCount() - 1);

                if (enemy->hitCount <= 0)
                {
                    // cout << "player score is " << player->GetPlayerScore() << endl;
                    enemy->isAlive = false;
                    if (enemy->type == FAST){player->SetPlayerScore(player->GetPlayerScore()+50);};
                    if (enemy->type == AVERAGE){player->SetPlayerScore(player->GetPlayerScore()+100);};
                    if (enemy->type == SLOW){player->SetPlayerScore(player->GetPlayerScore()+150);};
                    
                    // cout << "player score is " << player->GetPlayerScore() << endl;

                }


            }
        }

        // Remove dead enemies from the list
        if (!enemy->isAlive)
        {
            if (enemy->type == FAST)
            {
                smallEnemyCounter--;
            }
            if (enemy->type == AVERAGE)
            {
                mediumEnemyCounter--;
            }
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

// ------------------------------------------------------------------------------------------- POPULATE ENEMIES FUNCTION
Enemy* PopulateEnemies(vector<Enemy*> &enemyList, Texture2D eyeSprite, Texture2D handSprite,int score)
{
    int xPos, yPos;
    bool positionValid;
    int enemyChoice = 0;


    enemyChoice = GetRandomValue(0,1);
    

    xPos = GetRandomValue(92, GetScreenWidth() - 92);
    yPos = GetRandomValue(-128, -64);
 
    if (smallEnemyCounter != smallEnemyAmount)
    {
        smallEnemyCounter++;
        
        return new EyeEnemy(Vector2{(float)xPos, (float)yPos}, eyeSprite);
 
    }
    else if (mediumEnemyCounter != mediumEnemyAmount)
    {
        mediumEnemyCounter++;
        // cout << "going medium " << endl;
        return new HandEnemy(Vector2{(float)xPos, (float)yPos}, handSprite);  
    }
    else
    {
        // cout << "doing whatever! " << endl;
        enemyChoice = GetRandomValue(0,1);
        if (enemyChoice == 0)
        {
            
            return new EyeEnemy(Vector2{(float)xPos, (float)yPos}, eyeSprite);
        }
        else 
        {
            return new HandEnemy(Vector2{(float)xPos, (float)yPos}, handSprite);      
        }
    }

}

