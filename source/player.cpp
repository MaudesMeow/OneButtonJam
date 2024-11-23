#include "player.hpp"


bool bulletfired = false;
Vector2 bulletPos;
int lastX;

void Player::HandleInput()
{
    if (!bulletfired)
    {
        bulletPos = pos;
    } else
    {
        DrawRectangle(lastX,bulletPos.y+16, 4,4,WHITE);
        bulletPos.y -= (640*GetFrameTime());
        if (bulletPos.y < 0)
        {
            bulletfired = false;
        }
        
    }
    pos.x += (160*GetFrameTime() * direction);
    if (IsKeyPressed(KEY_SPACE))
    {
        direction *= -1;
        if (bulletfired == false)
        {
        if (direction < 0 ? lastX = pos.x + 8*direction : lastX = pos.x + 32*direction);
        
        bulletfired = true;
        }
        

    }

    pos.x += (160*GetFrameTime() * direction);
    if (pos.x <= 32)
    {
        direction = 1;
    }
    if (pos.x >= GetScreenWidth() -64-8)
    {
       direction = -1;
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