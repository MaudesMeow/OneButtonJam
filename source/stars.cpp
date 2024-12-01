#include "stars.hpp"

static const Color colors[7] = {
    {240, 228, 66, 255},
    {230, 159, 0, 255},
    {204, 121, 167, 255},
    {213, 94, 0, 255},
    {86, 180, 233, 255},
    {0, 114, 178, 255},
    {0, 158, 115, 255}
};

void InitStars(Stars star[], int starCount)
{
    for (int i = 0; i < starCount; i++)
    {
        int randomColor = GetRandomValue(0, 6);  // Adjusted max to 6 (array indices)
        star[i].pos.x = GetRandomValue(96, GetScreenWidth() - 96);
        star[i].pos.y = GetRandomValue(0, GetScreenHeight());
        star[i].size = static_cast<float>(rand()) / RAND_MAX * 2.2f + 0.75f;  // Avoid repeated static casts
        star[i].color = colors[randomColor];
    }
}

void DrawStars(Stars star[], int starCount)
{
    for (int i = 0; i < starCount; i++)
    {
        DrawCircleV(star[i].pos, star[i].size, star[i].color);  // Simpler DrawCircle variant
    }
}

void UpdateStars(Stars star[], int starCount)
{
    float speed = 160 * GetFrameTime();
    for (int i = 0; i < starCount; i++)
    {
        star[i].pos.y += speed;

        // Reset the star's position if it goes off the bottom
        if (star[i].pos.y > GetScreenHeight())
        {
            int randomColor = GetRandomValue(0, 6);
            star[i].pos.x = GetRandomValue(96, GetScreenWidth() - 96);
            star[i].pos.y = 0;
            star[i].size = static_cast<float>(rand()) / RAND_MAX * 2.2f + 0.75f;
            star[i].color = colors[randomColor];
        }
    }
}
