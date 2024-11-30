#include "stars.hpp"


static float randomFloat;
static float randomSizeFloat = 0.8;
int randomColor;

Color colors[7] =
{
    Color{240,228,066},
    Color{230,159,000},
    Color{204,121,167},
    Color{213,94,000},
    Color{86,180,233},
    Color{000,114,178},
    Color{000,158,115}

};
void InitStars(Stars star[], int starCount)
{
    for (int i = 0; i < starCount; i++)
    {
        randomColor = GetRandomValue(0,7);
        star[i].pos.x = GetRandomValue(96, GetScreenWidth()-96);  // Random X within the screen width
        star[i].pos.y = GetRandomValue(0, GetScreenHeight()); // Random Y within the screen height
        randomFloat = static_cast <float> (rand()+0.75) / (static_cast <float> (RAND_MAX/randomSizeFloat));
        star[i].size = randomFloat;
        star[i].color = (Color){ colors[randomColor].r,colors[randomColor].g,colors[randomColor].b, 255 };
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
            randomColor = GetRandomValue(0,7);
            star[i].pos.x = GetRandomValue(96, GetScreenWidth()-96);  // Random X within the screen width
            star[i].pos.y = 0;
            randomFloat = static_cast <float> (rand()+0.75) / (static_cast <float> (RAND_MAX/randomSizeFloat));
            star[i].size = randomFloat;
            star[i].color = (Color){ colors[randomColor].r,colors[randomColor].g,colors[randomColor].b, 255 };
        }
    }
}