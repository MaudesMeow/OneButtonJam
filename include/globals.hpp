#ifndef GLOBALS_HEADER
#define GLOBALS_HEADER

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <cstdlib>
#include <vector>

#include "raylib.h"

using namespace std;

#define BASE_WIDTH 400
#define BASE_HEIGHT 400



extern float globalScore;
extern int globalHighScore;

extern Sound explosion,ammoCollect,healthCollect,directionChange,enemyCollision,enemyDeath,playerDeath,fireAmmoSound;

#endif