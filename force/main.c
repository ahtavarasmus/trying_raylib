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


    SetTargetFPS(30);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        if (IsKeyDown(KEY_RIGHT)) {
            if (rightLen <= 10) rightLen++;
            rec.x += rightLen;
            if (rec.x > screenWidth - rec.width) rec.x = screenWidth - rec.width;
        } else if (IsKeyUp(KEY_RIGHT)){
            if (rightLen > 0) rightLen--;
            rec.x += rightLen;
            if (rec.x > screenWidth - rec.width) rec.x = screenWidth - rec.width;
        }
        printf("rightLen: %d\n", rightLen);
        if (IsKeyDown(KEY_LEFT)) {
            if (leftLen <= 10) leftLen++;
            rec.x -= leftLen;
            if (rec.x < 0) rec.x = 0;
        } else if (IsKeyUp(KEY_LEFT)){
            if (leftLen > 0) leftLen--;
            rec.x -= leftLen;
            if (rec.x < 0) rec.x = 0;
        }
        printf("leftLen: %d\n", leftLen);
        if (IsKeyDown(KEY_UP)) {
            if (upLen <= 10) upLen++;
            rec.y -= upLen;
            if (rec.y < 0) rec.y = 0;
        } else if (IsKeyUp(KEY_UP)){
            if (upLen > 0) upLen--;
            rec.y -= upLen;
            if (rec.y < 0) rec.y = 0;
        }
        printf("upLen: %d\n", upLen);
        if (IsKeyDown(KEY_DOWN)) {
            // speed is max 5 and kept in window
            if (downLen <= 10) downLen++;
            rec.y += downLen;
            if (rec.y > screenHeight - rec.height) rec.y = screenHeight - rec.height;
        } else if (IsKeyUp(KEY_DOWN)){
            if (downLen > 0) downLen--;
            rec.y += downLen;
            if (rec.y > screenHeight - rec.height) rec.y = screenHeight - rec.height;
        }
        printf("downLen: %d\n", downLen);


        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangleRec(rec, SKYBLUE);
        Vector2 center = {rec.x + rec.width / 2, rec.y + rec.height / 2};
        Vector2 endPos = {center.x, center.y};
        int arrowLen = 10;
        if (upLen > 0) {
            endPos.y -= arrowLen*upLen;
            DrawLineEx(center, (Vector2){center.x, center.y - arrowLen*upLen}, 5.0f, GREEN);
        }
        if (downLen > 0) {
            endPos.y += 10*downLen;
            DrawLineEx(center, (Vector2){center.x, center.y + arrowLen*downLen}, 5.0f, GREEN);
        }
        if (leftLen > 0) {
            endPos.x -= 10*leftLen;
            DrawLineEx(center, (Vector2){center.x - arrowLen*leftLen, center.y}, 5.0f, GREEN);
        }
        if (rightLen > 0) {
            endPos.x += 10*rightLen;
            DrawLineEx(center, (Vector2){center.x + arrowLen*rightLen, center.y}, 5.0f, GREEN);
        }

        DrawLineEx(center, endPos, 5.0f, RED);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

