#include <raylib.h>
#include <math.h>

#include "globals.hpp"
#include "player.hpp"
#include "stars.hpp"
#include "enemy.hpp"
#include "ammo.hpp"
#include "gameplay.cpp"

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
vector<Ammo> ammoCount;

Player player;
Enemy enemy;


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
    player = Player(playerSprite, {(float)GetScreenWidth()/2,(float)GetScreenHeight()-playerSprite.height*2-8});
    enemy = Enemy(Vector2{320,0});
    InitStars(stars,starCount); 


}
// ---------------------------------------------------------------------------UPDATE FUNCTION
void Update(void)
{
    UpdateStars(stars,starCount);
    player.HandleInput();



}
// ---------------------------------------------------------------------------Draw FUNCTION
void Draw(void)
{
    ClearBackground(BLACK);
    
    DisplayAmmo(player.ReturnAmmoCount());
    PopulateBonuses();
    DrawStars(stars,starCount);
    DrawText("AMMO: ",8,0,24,WHITE);
    player.AnimatePlayer();
    enemy.EnemyBehavior();





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
