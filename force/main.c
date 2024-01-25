#include "raylib.h"
#include <stdio.h>

typedef enum ScreenColor { white = 0, skyblue, purple, lime } ScreenColor;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Rectangle rec = { 0, 0, 30, 30 };
    int rightLen = 0;
    int leftLen = 0;
    int upLen = 0;
    int downLen = 0;
    bool right = false;
    bool left = false;
    bool up = false;
    bool down = false;


    SetTargetFPS(30);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        if (IsKeyDown(KEY_RIGHT)) {
            if (rightLen <= 10) rightLen++, leftLen--;
            rec.x += rightLen;
            right = true;
        } else {
            right = false;
        }
        printf("rightLen: %d\n", rightLen);
        if (IsKeyDown(KEY_LEFT)) {
            if (leftLen <= 10) leftLen++, rightLen--;
            rec.x -= leftLen;
            left = true;
        } else {
            left = false;
        }
        printf("leftLen: %d\n", leftLen);
        if (IsKeyDown(KEY_UP)) {
            if (upLen <= 10) upLen++, downLen--;
            up = true;
        } else {
            up = false;
        }
        printf("upLen: %d\n", upLen);
        if (IsKeyDown(KEY_DOWN)) {
            if (downLen <= 10) downLen++,upLen--;
            down = true;
        } else {
            down = false;
        }
        printf("downLen: %d\n", downLen);
        rec.x += rightLen - leftLen;
        rec.y += downLen - upLen;
        if (rec.x < 0) rec.x = 0;
        if (rec.x > screenWidth - rec.width) rec.x = screenWidth - rec.width;
        if (rec.y < 0) rec.y = 0;
        if (rec.y > screenHeight - rec.height) rec.y = screenHeight - rec.height;


        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangleRec(rec, SKYBLUE);
        Vector2 center = {rec.x + rec.width / 2, rec.y + rec.height / 2};
        if (up) {
            DrawLineEx(center, (Vector2){center.x, center.y - 50}, 5.0f, GREEN);
        }
        if (down) {
            DrawLineEx(center, (Vector2){center.x, center.y + 50}, 5.0f, GREEN);
        }
        if (left) {
            DrawLineEx(center, (Vector2){center.x - 50, center.y}, 5.0f, GREEN);
        }
        if (right) {
            DrawLineEx(center, (Vector2){center.x + 50, center.y}, 5.0f, GREEN);
        }

        //DrawLineEx(center, endPos, 5.0f, RED);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

