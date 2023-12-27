#include "raylib.h"

typedef enum ScreenColor { white = 0, skyblue, purple, lime } ScreenColor;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    ScreenColor currentColor = white;


    int framesCounter = 0;
    int refreshPerSec = 10;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        switch(currentColor){
            case white: 
            {
                framesCounter++;
                if (framesCounter == refreshPerSec){
                    currentColor = skyblue;
                    framesCounter = 0;
                }
            } break;
            case skyblue:
            {
                framesCounter++;
                if (framesCounter == refreshPerSec){
                    currentColor = purple;
                    framesCounter = 0;
                }
            } break;
            case purple:
            {
                framesCounter++;
                if (framesCounter == refreshPerSec){
                    currentColor = lime;
                    framesCounter = 0;
                }
            } break;
            case lime:
            {
                framesCounter++;
                if (framesCounter == refreshPerSec){
                    currentColor = white;
                    framesCounter = 0;
                }
            } break;
            default: break;
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
            switch(currentColor){
                case white: 
                {
                    DrawRectangle(0,0,screenWidth, screenHeight, WHITE);
                    DrawText("white", 20, 20, 40, LIGHTGRAY);
                } break;
                case skyblue:
                {
                    DrawRectangle(0,0,screenWidth, screenHeight, SKYBLUE);
                    DrawText("skyblue", 20, 20, 40, LIGHTGRAY);
                } break;
                case purple:
                {
                    DrawRectangle(0,0,screenWidth, screenHeight, PURPLE);
                    DrawText("purple", 20, 20, 40, LIGHTGRAY);
                } break;
                case lime:
                {
                    DrawRectangle(0,0,screenWidth, screenHeight, LIME);
                    DrawText("lime", 20, 20, 40, LIGHTGRAY);
                }break;
                default: break;
            }

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

