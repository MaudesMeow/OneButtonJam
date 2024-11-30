#include <raylib.h>
#include <math.h>

#include "globals.hpp"
#include "player.hpp"
#include "stars.hpp"
#include "enemy.hpp"
#include "ammo.hpp"
#include "gameplay.hpp"
#include "bonus.hpp"

#define PROJECT_NAME "Game"

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
    #define GLSL_VERSION (100)
#else
    #define GLSL_VERSION (330)
#endif

static int screen_width, screen_height, screen_scale;
static bool recalculate_screen_resolution;
static Shader shd_gradient;
static float hue_timer;

void Init(void);
void Update(void);
void Draw(void);
void Unload(void);
void UpdateDrawFrame(void);

float posX = 0;
int direction = 1;
const int starCount =  2000;
Stars stars[starCount];


Player player;
vector<Bonus*> bonusList;
vector<Enemy*> enemyList;
Texture2D enemyOne;
Texture2D handEnemy;

Font importedFont;


float score = 0;



// ---------------------------------------------------------------------------MAIN FUNCTION
int main(void)
{
    Init();

#ifdef PLATFORM_WEB
    // (main loop function, fps, simulate infinite loop)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif
    Unload();
    return 0;
}
// ---------------------------------------------------------------------------INIT FUNCTION
void Init(void)
{
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    InitWindow(BASE_WIDTH * 2, BASE_HEIGHT * 2, PROJECT_NAME);



    Texture2D playerSprite = LoadTexture("assets/player-bug.png");
    enemyOne = LoadTexture("assets/enemy-one.png");
    handEnemy = LoadTexture("assets/big-hand.png");
    player = Player(playerSprite, {(float)GetScreenWidth()/2,(float)GetScreenHeight()-64});
    importedFont = LoadFont("assets/Covenant5x5.ttf");
    

    InitStars(stars,starCount); 


}
// ---------------------------------------------------------------------------UPDATE FUNCTION
void Update(void)
{

    score += 0.25;
   
    player.SetPlayerScore((int)floor(score));
    
    UpdateStars(stars,starCount);
    player.UpdatePlayerBehavior();
    UpdateBonusBehavior(bonusList, &player);
    UpdateEnemyBehavior(enemyList,&player,enemyOne,handEnemy,player.ammoInventory);

}
// ---------------------------------------------------------------------------Draw FUNCTION
void Draw(void)
{
    ClearBackground(BLACK);
    
    DisplayAmmo(player.GetAmmoCount());
    // cout << "get ammo is returning " << player.GetAmmoCount() << endl;
    
    DrawStars(stars,starCount);
    // DrawText("AMMO: ",8,0,24,WHITE);
    DrawTextEx(importedFont,"AMMO",{8,2},24,4,WHITE);
    DrawTextEx(importedFont,TextFormat("SCORE\n\n%i%",player.GetPlayerScore()),{8,64},20,2,WHITE);
    // DrawText(TextFormat("SCORE:\n\n%d", (int)floor(score)), 8, 64, 22, WHITE);
    player.AnimatePlayer();
    AnimateAmmo(player.ammoInventory);
    

    for (Bonus *bonus : bonusList)
    {
        bonus->DrawBonus();
    }
    for (Enemy *enemy: enemyList)
    {
        enemy->DrawEnemies();
    }
   





}
// ---------------------------------------------------------------------------UNLOAD FUNCTION
void Unload(void)
{

#ifdef PLATFORM_WEB
    emscripten_exit_with_live_runtime();
#endif
    CloseWindow();
}
// ---------------------------------------------------------------------------UPDATE AND DRAW FUNCTION
void UpdateDrawFrame(void)
{
    Update();

    BeginDrawing();
        Draw();
    EndDrawing();
}
