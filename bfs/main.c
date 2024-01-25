#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>


typedef enum ScreenColor { white = 0, skyblue, purple, lime } ScreenColor;

int main(void)
{
    const int screenWidth = 400;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    const int grid_size = 50;
    int grid[grid_size][grid_size] = { 0 }; // 0 == open, 1 == reserved
    int visited[grid_size][grid_size] = { 0 }; // 0 == not visited, 1 == visited
    const int grid_size_squared = grid_size * grid_size;
    int queue[grid_size_squared][2] = { 0 }; // 0 == x, 1 == y
    int going = 0; // 0 == not going, 1 == going

    // random walls for the grid
    for (int i = 0; i < 1500; i++) {
        grid[rand() % grid_size][rand() % grid_size] = 1;
    }


    int x = grid_size/2;
    int y = grid_size/2;
    queue[0][0] = x;
    queue[0][1] = y;
    visited[x][y] = 1;
    int queueSize = 1;
    int queueIndex = 0;
    int found = 0;


    // refresh rate
    SetTargetFPS(15);

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) {
            printf("spacebar pressed\n");
            // resetting the map
            for (int i = 0; i < grid_size; i++) {
                for (int j = 0; j < grid_size; j++){
                    visited[i][j] = 0;
                }
            }
            // resetting the queue
            for (int i = 0; i < grid_size*grid_size; i++) {
                queue[i][0] = 0;
                queue[i][1] = 0;
            }

            x = grid_size/2;
            y = grid_size/2;
            queue[0][0] = x;
            queue[0][1] = y;
            visited[x][y] = 1;
            queueSize = 1;
            queueIndex = 0;
            found = 0;
            going = 1;
        } 

        if (going) {

            printf("queueSize: %d\n", queueSize);
            printf("queueIndex: %d\n", queueIndex);
            printf("queue[queueIndex][0]: %d\n", queue[queueIndex][0]);
            printf("queue[queueIndex][1]: %d\n", queue[queueIndex][1]);
            printf("visited[queue[queueIndex][0]][queue[queueIndex][1] - 1]: %d\n", visited[queue[queueIndex][0]][queue[queueIndex][1] - 1]);
            printf("grid[queue[queueIndex][0]][queue[queueIndex][1] - 1]: %d\n", grid[queue[queueIndex][0]][queue[queueIndex][1] - 1]);

            // check if we are at the end
            if (queue[queueIndex][0] == grid_size-1 && queue[queueIndex][1] == grid_size-1) {
                going = 0;
                printf("found\n");
            }
            // check if we can go up
            if (grid[queue[queueIndex][0]][queue[queueIndex][1] - 1] == 0 && visited[queue[queueIndex][0]][queue[queueIndex][1] - 1] == 0) {
                queue[queueSize][0] = queue[queueIndex][0];
                queue[queueSize][1] = queue[queueIndex][1] - 1;
                visited[queue[queueIndex][0]][queue[queueIndex][1] - 1] = 1;
                queueSize++;
                queueIndex++;

            }
            // check if we can go down
            if (grid[queue[queueIndex][0]][queue[queueIndex][1] + 1] == 0 && visited[queue[queueIndex][0]][queue[queueIndex][1] + 1] == 0) {
                queue[queueSize][0] = queue[queueIndex][0];
                queue[queueSize][1] = queue[queueIndex][1] + 1;
                visited[queue[queueIndex][0]][queue[queueIndex][1] + 1] = 1;
                queueSize++, queueIndex++;
            }
            // check if we can go left
            if (grid[queue[queueIndex][0] - 1][queue[queueIndex][1]] == 0 && visited[queue[queueIndex][0] - 1][queue[queueIndex][1]] == 0) {
                queue[queueSize][0] = queue[queueIndex][0] - 1;
                queue[queueSize][1] = queue[queueIndex][1];
                visited[queue[queueIndex][0] - 1][queue[queueIndex][1]] = 1;
                queueSize++;
                queueIndex++;
            }
            // check if we can go right
            if (grid[queue[queueIndex][0] + 1][queue[queueIndex][1]] == 0 && visited[queue[queueIndex][0] + 1][queue[queueIndex][1]] == 0) {
                queue[queueSize][0] = queue[queueIndex][0] + 1;
                queue[queueSize][1] = queue[queueIndex][1];
                visited[queue[queueIndex][0] + 1][queue[queueIndex][1]] = 1;
                queueSize++;
                queueIndex++;
            }
        }

        // Draw
        BeginDrawing();

        for (int i = 0; i < grid_size; i++) {
            for (int j = 0; j < grid_size; j++){
                if (grid[i][j] == 1) {
                    DrawRectangle(i * 8, j * 8, 8, 8, BLACK);
                } else if (visited[i][j] == 1) {
                    DrawRectangle(i * 8, j * 8, 8, 8, LIME);
                }
            }
        }
        // start button
        //DrawText("Start with spacebar", 10, 10, 20, BLUE);


        ClearBackground(RAYWHITE);
                

        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

