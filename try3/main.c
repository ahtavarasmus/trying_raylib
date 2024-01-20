#include "raylib.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int missileCount = 100;

    InitWindow(screenWidth, screenHeight, "raylib - Space Invaders");

    // Define the player and basic properties
    Rectangle player = { screenWidth / 2.0f, screenHeight - 30.0f, 20.0f, 20.0f };
    Rectangle missiles[missileCount] = { 0 };
    Rectangle ships[shipCount]
    bool missileActive[missileCount] = { false };
    float playerSpeed = 5.0f;
    float missileSpeed = 5.0f;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Player movement
        if (IsKeyDown(KEY_LEFT)) player.x -= playerSpeed;
        if (IsKeyDown(KEY_RIGHT)) player.x += playerSpeed;
        if (IsKeyPressed(KEY_SPACE)){
            for (int i = 0; i < missileCount; ++i){
                if (!missileActive[i]){
                    missiles[i].x = player.x+(player.width/2);
                    missiles[i].y = player.y;
                    missiles[i].width = 2.0f;
                    missiles[i].height = 10.0f;
                    missileActive[i] = true;
                    break;
                }
            }
        }

        // Keep the player inside the screen bounds
        if (player.x < 0) player.x = 0;
        if (player.x > screenWidth - player.width) player.x = screenWidth - player.width;

        // TODO: Update your game logic here (e.g., player shooting, enemy movement, collision detection)
        //----------------------------------------------------------------------------------
        for (int i = 0; i < missileCount; ++i){
            if (missileActive[i]){
                missiles[i].y -= missileSpeed;
                if (missiles[i].y < 0) missileActive[i] = false;
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        // Draw the player
        DrawRectangleRec(player, WHITE);
        for (int i = 0; i < missileCount; ++i){
            if (missileActive[i]){
                DrawRectangleRec(missiles[i], RED);
            }
        }

        // TODO: Draw your game here (e.g., bullets, enemies)

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
