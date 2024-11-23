#ifndef STARS_HEADER
#define STARS_HEADER

#include "globals.hpp"


class Stars
{
    public:
        Vector2 pos;
        float size;

        Color color;
        





};

void InitStars(Stars star[], int starCount);
void UpdateStars(Stars star[], int starCount);
void DrawStars(Stars star[], int starCount);

#endif
