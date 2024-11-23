#include "stars.hpp"


float randomFloat;
float randomSizeFloat = 0.8;
void InitStars(Stars star[], int starCount)
{
    for (int i = 0; i < starCount; i++)
    {
        star[i].pos.x = GetRandomValue(96, GetScreenWidth()-96);  // Random X within the screen width
        star[i].pos.y = GetRandomValue(0, GetScreenHeight()); // Random Y within the screen height
        randomFloat = static_cast <float> (rand()+0.75) / (static_cast <float> (RAND_MAX/randomSizeFloat));
        star[i].size = randomFloat;
        star[i].color = (Color){ (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 250), (unsigned char)GetRandomValue(0, 255), 255 };
    }
}

void DrawStars(Stars star[], int starCount)
{
    for (int i = 0; i < starCount; i++)
    {
        // DrawRectangle(star[i].pos.x,star[i].pos.y,star[i].size,star[i].size,star[i].color);
        DrawCircle(star[i].pos.x,star[i].pos.y,star[i].size,star[i].color);
    }
}

void UpdateStars(Stars star[], int starCount)
{
    for (int i = 0; i < starCount; i++)
    {
        star[i].pos.y += 0.5;

        // Reset the star's position if it goes off the bottom
        if (star[i].pos.y > GetScreenHeight())
        {
            star[i].pos.x = GetRandomValue(96, GetScreenWidth()-96);  // Random X within the screen width
            star[i].pos.y = 0;
            randomFloat = static_cast <float> (rand()+0.75) / (static_cast <float> (RAND_MAX/randomSizeFloat));
            star[i].size = randomFloat;
            star[i].color = (Color){ (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 250), (unsigned char)GetRandomValue(0, 255), 255 };
        }
    }
}