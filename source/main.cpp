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
Texture2D heartSprite;


Font importedFont;

// ---- globals
float globalScore = 0;
int globalHighScore = 0;

Sound explosion,ammoCollect,healthCollect,directionChange,enemyCollision,enemyDeath,playerDeath;
Sound fireAmmoSound;
Music backgroundSong;


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
    InitAudioDevice();
    



    Texture2D playerSprite = LoadTexture("assets/player-bug.png");
    enemyOne = LoadTexture("assets/enemy-one.png");
    handEnemy = LoadTexture("assets/big-hand.png");
    player = Player(playerSprite, {(float)GetScreenWidth()/2,(float)GetScreenHeight()-64});
    importedFont = LoadFont("assets/Covenant5x5.ttf");
    heartSprite = LoadTexture("assets/heart.png");
    explosion = LoadSound("assets/explosion2.wav");
    ammoCollect = LoadSound("assets/ammo-collect.wav");
    healthCollect = LoadSound("assets/heal-sound.wav");
    backgroundSong = LoadMusicStream("assets/background-song.wav");
    directionChange = LoadSound("assets/beep1.wav");
    enemyCollision = LoadSound("assets/enemy-collision.wav");
    enemyDeath = LoadSound("assets/enemy-death.wav");
    playerDeath = LoadSound("assets/player-death.wav");
    fireAmmoSound = LoadSound("assets/fire-ammo.wav");

    SetSoundVolume(fireAmmoSound,0.2);
    SetSoundVolume(directionChange,0.1);
    SetSoundPitch(directionChange,0.1);
    SetSoundVolume(ammoCollect,0.3);
    SetSoundVolume(healthCollect,0.3);
    SetSoundVolume(enemyCollision,0.3);

    SetSoundVolume(explosion,0.3);

        
    

    InitStars(stars,starCount); 


}
// ---------------------------------------------------------------------------UPDATE FUNCTION
void Update(void)
{
    UpdateMusicStream(backgroundSong);
    if (!IsMusicStreamPlaying(backgroundSong))
    {

        SetMusicVolume(backgroundSong,0.3);

        PlayMusicStream(backgroundSong);
    }
    if (player.isReady)
    {
        StopMusicStream(backgroundSong);
    }

    if (!player.isReady)
    {
        UpdateStars(stars,starCount);
        player.UpdatePlayerBehavior();
               
    }
    else
    {
        globalScore += 0.25;
    
        player.SetPlayerScore((int)floor(globalScore));
        
        UpdateStars(stars,starCount);
        player.UpdatePlayerBehavior();
        UpdateBonusBehavior(bonusList,heartSprite, &player);
        UpdateEnemyBehavior(enemyList,&player,enemyOne,handEnemy,player.ammoInventory,bonusList);
    }


}
// ---------------------------------------------------------------------------Draw FUNCTION
void Draw(void)
{
    ClearBackground(BLACK);
    
    
    // cout << "get ammo is returning " << player.GetAmmoCount() << endl;
    
    DrawStars(stars,starCount);

    // --------------------------------------------------------------------- DRAW text     
    if (!player.isReady)
    {
        DrawTextEx(importedFont,"SPACE",{114,48},96,2,WHITE);

        DrawTextEx(importedFont,"MOTH",{160,124 },96,2,WHITE);
        DrawTextEx(importedFont, TextFormat("current high score is: %i", globalHighScore),{(float)GetScreenWidth()/2-184,(float)GetScreenHeight()-128},24,2,WHITE);
        DrawTextEx(importedFont, "the only available button is the space bar\nthe space bar will change your direction\nand shoot if you have ammo\nhold the space bar to gather more speed",{(float)GetScreenWidth()/2-192,320},16,2,WHITE);
        player.AnimatePlayer();
    }
    else
    {
        DrawTextEx(importedFont,"HEALTH",{8,56},14,4,WHITE);
        DrawTextEx(importedFont,"AMMO",{8,2},24,4,WHITE);
        DrawTextEx(importedFont,TextFormat("SCORE\n\n%i%",player.GetPlayerScore()),{8,128},20,2,WHITE);
        DrawTextEx(importedFont,TextFormat("SCORE\n\n%i%",GetFPS()),{8,164},20,2,WHITE);

        player.AnimatePlayer();
        AnimateAmmo(player.ammoInventory);
        DisplayAmmo(player.GetAmmoCount());
        DisplayPlayerHealth(player.GetPlayerHealth(),heartSprite);
        

        for (Bonus *bonus : bonusList)
        {
            bonus->DrawBonus();
        }
        for (Enemy *enemy: enemyList)
        {
            enemy->DrawEnemies();
        }
        
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
