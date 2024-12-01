#include "player.hpp"


bool bulletfired = false;
Vector2 bulletPos;



void Player::HandleInput()
{
    if (!isReady)
    {
        pos.x = GetScreenWidth()/2 - 16;
        if (IsKeyPressed(KEY_SPACE))
        {
            isReady = true;
        }
        
    }
    else
    {
        pos.x += (speed*GetFrameTime() * direction);
        
        hitBox.x = pos.x;
        hitBox.y = pos.y;


        if (IsKeyPressed(KEY_SPACE) )
        {

            PlaySound(directionChange);
            direction *= -1;
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
        if (pos.y < GetScreenHeight() - 128)
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
}

void Player::AnimatePlayer()
{


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


void Player::BulletBehavior() {
    if (ammoInventory.empty()) {
        // Populate the fixed pool with 3 ammo objects
        for (int i = 0; i < 3; ++i) {
            ammoInventory.push_back(PopulateAmmo());
        }
    }

    // Handle firing
    if (IsKeyPressed(KEY_SPACE) && GetAmmoCount() > 0 && canShoot) {
        for (Ammo* ammo : ammoInventory) {
            if (!ammo->isActive) {
                PlaySound(fireAmmoSound);
                SetAmmoCount(GetAmmoCount() - 1);
                ammo->isActive = true;
                ammo->hasFired = true;
                ammo->bulletPos = pos; // Set initial position
                canShoot = false;
                shooterTimer = 0; // Reset timer
                break;
            }
        }
    }

    // Update timer
    shooterTimer += GetFrameTime();
    if (shooterTimer > 0.3f) {
        canShoot = true;
    }

    // Update ammo behavior
    for (Ammo* ammo : ammoInventory) {
        if (!ammo->isActive) continue;

        ammo->SetAmmoPos(pos, direction);

        if (ammo->hasCollided || ammo->bulletPos.y <= 0) {
            ammo->Reset(); // Reset ammo instead of deleting
        }
    }
}


void Player::UpdatePlayerBehavior()
{
    HandleInput();
    BulletBehavior();
   
 }

 void DisplayPlayerHealth(int healthAmount, Texture2D sprite)
 {
        for (int i = 0 ;  i < healthAmount; i++)
    {
        switch (i)
        {
        case 0:
            // DrawTriangleLines(Vector2{16,48},Vector2{32,48},Vector2{24,32},WHITE);
            DrawTexture(sprite,16,88,WHITE);
            break;
        case 1:
            DrawTexture(sprite,40,88,WHITE);
            break;
        case 2:
            DrawTexture(sprite,64,88,WHITE);
            break;    
        default:
            break;
        }
    }
 }
