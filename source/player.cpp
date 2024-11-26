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
        
        bulletPos.y -= (680*GetFrameTime());
        if (bulletPos.y < 0)
        {
            bulletfired = false;
        }
        
    }
    pos.x += (speed*GetFrameTime() * direction);
    if (IsKeyPressed(KEY_SPACE) )
    {
        direction *= -1;

        
        if (GetAmmoCount() < 0){canShoot = false;};
        if (canShoot)
        {
            
            if (bulletfired == false)
            {
            (SetAmmoCount(GetAmmoCount()-1));
            lastX = (direction < 0) ? pos.x : pos.x + 32;
            
            bulletfired = true;
            }
        }


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
        DrawTriangleLines(p1, p2, p3, WHITE);
        DrawRectangleLines(lastX-2,bulletPos.y, 4,4,ColorAlpha(Color{255,255,255},0.8));
        
        DrawRectangleLines(lastX-2,bulletPos.y+2, 4,4,ColorAlpha(Color{255,255,255},0.5));
        
        DrawRectangleLines(lastX-2,bulletPos.y+4, 4,4,ColorAlpha(Color{255,255,255},0.3));
        
        DrawRectangleLines(lastX-2,bulletPos.y+6, 4,4,ColorAlpha(Color{255,255,255},0.15));
        DrawRectangleLines(lastX-2,bulletPos.y+7, 4,4,ColorAlpha(Color{255,255,255},0.10));
        DrawRectangleLines(lastX-2,bulletPos.y+8, 4,4,ColorAlpha(Color{255,255,255},0.05));
        DrawRectangleLines(lastX-2,bulletPos.y+9, 4,4,ColorAlpha(Color{255,255,255},0.03));
        DrawRectangleLines(lastX-2,bulletPos.y+10, 4,4,ColorAlpha(Color{255,255,255},0.01));

        
        
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