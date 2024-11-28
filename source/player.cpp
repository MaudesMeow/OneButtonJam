#include "player.hpp"


bool bulletfired = false;
Vector2 bulletPos;



void Player::HandleInput()
{

    pos.x += (speed*GetFrameTime() * direction);
    
    hitBox.x = pos.x;
    hitBox.y = pos.y;


    if (IsKeyPressed(KEY_SPACE) )
    {
        direction *= -1;

        
        // if (GetAmmoCount() < 0){canShoot = false;};
        // if (canShoot)
        // {
            
        //     if (bulletfired == false)
        //     {
        //     (SetAmmoCount(GetAmmoCount()-1));
        //     lastX = (direction < 0) ? pos.x : pos.x + 32;
            
        //     bulletfired = true;
        //     }
        // }


    }

    if (IsKeyUp(KEY_SPACE))
    {
        
    }

    if (IsKeyDown(KEY_SPACE))
    {
        if (speed < 480)
        {
            speed += 16;
        }

    }
    else 
    {
        speed = 160;
    }

    pos.x += (160*GetFrameTime() * direction);
    if (pos.y < GetScreenHeight() - 64)
    {
        pos.y += (160*GetFrameTime());
    }
    else 
    {
        hasTeleported = false;
    }
    if (pos.x <= 96)
    {
        direction = 1;
    }
    if (pos.x >= GetScreenWidth() -96-32)
    {
       direction = -1;
    }  
}

void Player::AnimatePlayer()
{

    if (bulletfired)
    {
        Vector2 p1 = { (float)lastX - 4, bulletPos.y };
        Vector2 p2 = { (float)lastX + 4, bulletPos.y };
        Vector2 p3 = { (float)lastX, bulletPos.y - 16 };

        // Draw the triangle


        
        
    }
    int numFrames = 4;
    int frameWidth = playerSprite.width / numFrames; // Width of a single frame
    int frameHeight = playerSprite.height; // Assuming all frames have the same height
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
        (float)frameWidth *2, // Width of the drawn framed)
        (float)frameHeight *2 // Height of the drawn frame (scaled)
    };

    DrawTexturePro(playerSprite,src,dest,{0,0},0,WHITE);

}


void Player::BulletBehavior()
{
    if (ammoInventory.size() < ammoCount)
    {
        ammoInventory.push_back(PopulateAmmo());
    }
    
    for (auto it = ammoInventory.begin(); it != ammoInventory.end(); )
    {
        Ammo* ammo = *it;
        if (ammo->hasFired){ammo->SetAmmoPos(pos,Vector2{(float)lastX - 4, pos.y},direction);}
        else{ammo->bulletPos.y -= (ammo->speed*GetFrameTime());}
        
        
        if (!ammo->hasCollided)
        {
            // Delete the enemy object to prevent memory leaks
            delete ammo;  
            
            
            it = ammoInventory.erase(it);
        }
        else
        {
            // Increment the iterator if the enemy is still alive
            ++it;
        }
    }

}

void Player::UpdatePlayerBehavior()
{
    HandleInput();
   
 }
