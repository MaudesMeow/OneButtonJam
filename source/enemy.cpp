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
    static float animationTime = 0.0f;
    animationTime += GetFrameTime()/2;
    int currentFrame = int(animationTime / frameTime) % numFrames;


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

    DrawTexturePro(sprite,src,dest,origin,0,WHITE);
    
    
    // DrawRectangleLinesEx(hitBox,1,RED);
    
}

void UpdateEnemyBehavior(vector<Enemy*> &enemyList, Player *player,Texture2D eyeSprite, Texture2D handSprite, vector<Ammo*> &ammo,vector<Bonus*> &bonusList)
{
    // ------------------------------------------------------------------------------------------- HOW MANY ENEMIES TO POPULATE
    enemyCount = 0;
    
    if (player->score < 150)
    {
        enemyCount = 2;
        smallEnemyAmount = 2;
        mediumEnemyAmount = 0;
        mediumEnemyCounter =0;
        smallEnemyCounter = 0;
    }
    else if (player->score >= 150 && player->score < 300)
    {
        enemyCount = 4;
        smallEnemyAmount = 3;
        mediumEnemyAmount = 1;
    }
    else if(player->score >= 300 && player->score < 450)
    {
        enemyCount = 6;
        smallEnemyAmount = 4;
        mediumEnemyAmount = 2;
    }
    else if(player->score >= 450 && player->score < 600)
    {
        enemyCount = 8;
        smallEnemyAmount = 5;
        mediumEnemyAmount = 3;
    }
    else
    {
        enemyCount = 12;
        smallEnemyAmount = 8;
        mediumEnemyAmount = 4;
    }

    if (enemyList.size() < enemyCount)
    {
        enemyList.push_back(PopulateEnemies(enemyList,eyeSprite,handSprite,player->score));
    }

    // ------------------------------------------------------------------------------------------- Iterate over the enemy list and update behavior
    for (Enemy* enemy: enemyList)
    {
        float deltaTime = GetFrameTime();
        enemy->counter += deltaTime;
        // enemy->directionTimer += GetFrameTime();
        // ------------------------------------------------------------------------------------------- Update enemy position

        switch (enemy->type)
        {
        case FAST:
            if (enemy->counter > enemy->waitTime)
            {

                enemy->pos.y += (enemy->speed * deltaTime);
                // enemy->pos.x += (enemy->speed*enemy->direction*deltaTime);
                enemy->hitBox.x = enemy->pos.x - 12;
                enemy->hitBox.y = enemy->pos.y -16;
            }
            break;
        case AVERAGE:
            if (enemy->counter > enemy->waitTime)
            {
                enemy->pos.y += (enemy->speed * deltaTime);
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
        if (enemy->pos.y > GetScreenHeight()/2)
        {

            
            if (CheckCollisionRecs(player->hitBox,enemy->hitBox) && enemy->isAlive)
            {
                if (enemy->type == AVERAGE)
                {
                    player->SetPlayerHealth(player->GetPlayerHealth()-2);
                }
                else if (enemy->type == FAST)
                {
                    player->SetPlayerHealth(player->GetPlayerHealth()-1);
                }

                if (player->GetPlayerHealth() <= 0)
                {
                    PlaySound(playerDeath);
                    if (player->GetPlayerScore() > globalHighScore)
                    {
                        globalHighScore = player->GetPlayerScore();
                    }
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
                PlaySound(enemyCollision);

                
                
            }
        }
        // ------------------------------------------------------------------------------------------- CHECK IF ENEMY IS SHOT
        for (Ammo *ammo : ammo)
        {

            if (ammo->hasFired)
            {
                if (CheckCollisionRecs(ammo->hitBox,enemy->hitBox))
                {

                    ammo->Reset();
                    
                    enemy->SetHitCount(enemy->GetHitCount() - 1);

                    if (enemy->hitCount <= 0)
                    {
                        PlaySound(explosion);
                        // cout << "player score is " << player->GetPlayerScore() << endl;
                        enemy->isAlive = false;
                        if (enemy->type == FAST){globalScore += 25;};
                        if (enemy->type == AVERAGE){globalScore += 75;};
                        if (enemy->type == SLOW){globalScore += 150;};


                    }


                }
            }
        }

        // Remove dead enemies from the list
        if (!enemy->isAlive)
        {
            if (enemy->type == AVERAGE)
            {
                enemy->pos = {(float)GetRandomValue(92, GetScreenWidth() - 92),-64};
                enemy->hitCount = 2;
            }
            else
            {
               enemy->pos = {(float)GetRandomValue(92, GetScreenWidth() - 92),-16};
               enemy->hitCount = 1;

            }
            enemy->counter = 0;
            enemy->isAlive = true;
            // cout << "there are small amoutn of enemies : " << smallEnemyAmount << endl;
            // cout << "there are medium amoutn of enemies : " << mediumEnemyAmount << endl;
        }

    }
}

// ------------------------------------------------------------------------------------------- POPULATE ENEMIES FUNCTION
Enemy* PopulateEnemies(vector<Enemy*> &enemyList, Texture2D eyeSprite, Texture2D handSprite, int score)
{
    int xPos, yPos;

    xPos = GetRandomValue(92, GetScreenWidth() - 92);
    yPos = GetRandomValue(-128, -64);

    // Prioritize adding medium enemies if needed
    if (mediumEnemyCounter < mediumEnemyAmount)
    {
        mediumEnemyCounter++;
        return new HandEnemy(Vector2{(float)xPos, (float)yPos}, handSprite);
    }
    else if (smallEnemyCounter < smallEnemyAmount)
    {
        smallEnemyCounter++;
        return new EyeEnemy(Vector2{(float)xPos, (float)yPos}, eyeSprite);
    }
    else
    {
        // If both limits are reached, randomly choose
        int enemyChoice = GetRandomValue(0, 1);
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

