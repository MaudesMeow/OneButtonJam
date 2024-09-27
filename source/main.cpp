#include <raylib.h>
#include <math.h>

#define BASE_WIDTH 480
#define BASE_HEIGHT 480
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

    SetWindowMinSize(BASE_WIDTH, BASE_HEIGHT);

}
// ---------------------------------------------------------------------------UPDATE FUNCTION
void Update(void)
{



}
// ---------------------------------------------------------------------------Draw FUNCTION
void Draw(void)
{
    ClearBackground(BLACK);



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
