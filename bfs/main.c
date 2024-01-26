#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


typedef enum ScreenColor { white = 0, skyblue, purple, lime } ScreenColor;

int d(int x_start, int y_start, int x_end, int y_end) {
    return abs(x_start - x_end) + abs(y_start - y_end);
}

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    const int grid_size = 50;
    const int grid_size_squared = grid_size * grid_size;

    // BFS
    int grid[grid_size][grid_size] = { 0 }; // 0 == open, 1 == reserved
    int visited[grid_size][grid_size] = { 0 }; // 0 == not visited, 1 == visited
    int queue[grid_size_squared][2] = { 0 }; // 0 == x, 1 == y
    int queueSize = 1;
    int queueIndex = 0;
    int going = 0; // 0 == not going, 1 == going

    // A*
    int gridAstar[grid_size][grid_size] = { 0 }; // 0 == open, 1 == reserved
    int visitedAstar[grid_size][grid_size] = { 0 }; // 0 == not visited, 1 == visited
    int queueAstar[grid_size_squared][2] = { 0 }; // 0 == x, 1 == y
    int queueSizeAstar = 1;
    int queueIndexAstar = 0;
    int goingAstar = 0; // 0 == not going, 1 == going

    // DFS
    int gridDfs[grid_size][grid_size] = { 0 }; // 0 == open, 1 == reserved
    int visitedDfs[grid_size][grid_size] = { 0 }; // 0 == not visited, 1 == visited
    int stackDfs[grid_size_squared][2] = { 0 }; // 0 == x, 1 == y
    int stackSizeDfs = 1;
    int goingDfs = 0; // 0 == not going, 1 == going



    // random walls for the grid
    int x,y;
    for (int i = 0; i < 1000; i++) {
        x = rand() % grid_size;
        y = rand() % grid_size;
        grid[x][y] = 1;
        gridDfs[x][y] = 1;
        gridAstar[x][y] = 1;
    }

    // random ending point
    x = rand() % grid_size;
    y = rand() % grid_size;
    grid[x][y] = 2;
    gridDfs[x][y] = 2;

    // starting point in the middle
    x = grid_size/2;
    y = grid_size/2;
    queue[0][0] = x;
    queue[0][1] = y;
    visited[x][y] = 1;
    stackDfs[0][0] = x;
    stackDfs[0][1] = y;
    visitedDfs[x][y] = 1;
    queueAstar[0][0] = x;
    queueAstar[0][1] = y;
    visitedAstar[x][y] = 1;


    // timer
    double timer = 0.0;
    double timerDfs = 0.0;
    double timerAstar = 0.0;
        
    // refresh rate
    SetTargetFPS(45);

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) {
            printf("spacebar pressed\n");
            // starting timer
            timer = GetTime();
            timerDfs = GetTime();
            timerAstar = GetTime();

            // resetting the map
            for (int i = 0; i < grid_size; i++) {
                for (int j = 0; j < grid_size; j++){
                    visited[i][j] = 0;
                    visitedDfs[i][j] = 0;
                    visitedAstar[i][j] = 0;
                }
            }
            // resetting the queue
            for (int i = 0; i < grid_size*grid_size; i++) {
                queue[i][0] = 0;
                queue[i][1] = 0;
                stackDfs[i][0] = 0;
                stackDfs[i][1] = 0;
                queueAstar[i][0] = 0;
                queueAstar[i][1] = 0;
            }

            x = grid_size/2;
            y = grid_size/2;

            queue[0][0] = x;
            queue[0][1] = y;
            visited[x][y] = 1;
            queueSize = 1;
            queueIndex = 0;
            going = 1;

            stackDfs[0][0] = x;
            stackDfs[0][1] = y;
            visitedDfs[x][y] = 1;
            stackSizeDfs = 0;
            goingDfs = 1;

            queueAstar[0][0] = x;
            queueAstar[0][1] = y;
            visitedAstar[x][y] = 1;
            queueSizeAstar = 1;
            queueIndexAstar = 0;
            goingAstar = 1;
        } 

        // BFS
        if (going) {
            // only update timer every 1000 frames
            timer = GetTime();
            // check if we are at the end
            if (grid[queue[queueIndex][0]][queue[queueIndex][1]] == 2) {
                going = 0;
                printf("found\n");
            } else {
                int in_grid = 0;
                // check if we can go up
                if (queue[queueIndex][1] - 1 >= 0) {
                    int up = grid[queue[queueIndex][0]][queue[queueIndex][1] - 1];
                    int up_visited = visited[queue[queueIndex][0]][queue[queueIndex][1] - 1];
                    if ((up == 0 || up == 2) && up_visited == 0) {
                        queue[queueSize][0] = queue[queueIndex][0];
                        queue[queueSize][1] = queue[queueIndex][1] - 1;
                        visited[queue[queueIndex][0]][queue[queueIndex][1] - 1] = 1;
                        queueSize++;
                    }
                }

                // check if we can go down
                if (queue[queueIndex][1] + 1 < grid_size) {
                    int down = grid[queue[queueIndex][0]][queue[queueIndex][1] + 1];
                    int down_visited = visited[queue[queueIndex][0]][queue[queueIndex][1] + 1];
                    if ((down == 0 || down == 2) && down_visited == 0) {
                        queue[queueSize][0] = queue[queueIndex][0];
                        queue[queueSize][1] = queue[queueIndex][1] + 1;
                        visited[queue[queueIndex][0]][queue[queueIndex][1] + 1] = 1;
                        queueSize++;
                    }
                }
                
                // check if we can go left
                if (queue[queueIndex][0] - 1 >= 0) {
                    int left = grid[queue[queueIndex][0] - 1][queue[queueIndex][1]];
                    int left_visited = visited[queue[queueIndex][0] - 1][queue[queueIndex][1]];
                    if ((left == 0 || left == 2) && left_visited == 0) {
                        queue[queueSize][0] = queue[queueIndex][0] - 1;
                        queue[queueSize][1] = queue[queueIndex][1];
                        visited[queue[queueIndex][0] - 1][queue[queueIndex][1]] = 1;
                        queueSize++;
                    }
                }
                
                // check if we can go right
                if (queue[queueIndex][0] + 1 < grid_size) {
                    int right = grid[queue[queueIndex][0] + 1][queue[queueIndex][1]];
                    int right_visited = visited[queue[queueIndex][0] + 1][queue[queueIndex][1]];
                    if ((right == 0 || right == 2) && right_visited == 0) {
                        queue[queueSize][0] = queue[queueIndex][0] + 1;
                        queue[queueSize][1] = queue[queueIndex][1];
                        visited[queue[queueIndex][0] + 1][queue[queueIndex][1]] = 1;
                        queueSize++;
                    }
                }
                queueIndex++;
            }
        }

        // A*
        if (goingAstar) {
            timerAstar = GetTime();
            // check if we are at the end
            if (gridAstar[queueAstar[queueIndexAstar][0]][queueAstar[queueIndexAstar][1]] == 2) {
                goingAstar = 0;
                printf("found\n");
            } else {
                int in_grid = 0;
                // check if we can go up
                if (queueAstar[queueIndexAstar][1] - 1 >= 0) {
                    int up = gridAstar[queueAstar[queueIndexAstar][0]][queueAstar[queueIndexAstar][1] - 1];
                    int up_visited = visitedAstar[queueAstar[queueIndexAstar][0]][queueAstar[queueIndexAstar][1] - 1];
                    if ((up == 0 || up == 2) && up_visited == 0) {
                        queueAstar[queueSizeAstar][0] = queueAstar[queueIndexAstar][0];
                        queueAstar[queueSizeAstar][1] = queueAstar[queueIndexAstar][1] - 1;
                        visitedAstar[queueAstar[queueIndexAstar][0]][queueAstar[queueIndexAstar][1] - 1] = 1;
                        queueSizeAstar++;
                    }
                }

                // check if we can go down
                if (queueAstar[queueIndexAstar][1] + 1 < grid_size) {
                    int down = gridAstar[queueAstar[queueIndexAstar][0]][queueAstar[queueIndexAstar][1] + 1];
                    int down_visited = visitedAstar[queueAstar[queueIndexAstar][0]][queueAstar[queueIndexAstar][1] + 1];
                    if ((down == 0 || down == 2) && down_visited == 0) {
                        queueAstar[queueSizeAstar][0] = queueAstar[queueIndexAstar][0];
                        queueAstar[queueSizeAstar][1] = queueAstar[queueIndexAstar][1] + 1;
                        visitedAstar[queueAstar[queueIndexAstar][0]][queueAstar[queueIndexAstar][1] + 1] = 1;
                        queueSizeAstar++;
                    }
                }
                
                // check if we can go left
                if (queueAstar[queueIndexAstar][0] - 1 >= 0) {
                    int left = gridAstar[queueAstar[queueIndexAstar][0] - 1][queueAstar[queueIndexAstar][1]];
                    int left_visited = visitedAstar[queueAstar[queueIndexAstar][0] - 1][queueAstar[queueIndexAstar][1]];
                    if ((left == 0 || left == 2) && left_visited == 0) {
                        queueAstar[queueSizeAstar][0] = queueAstar[queueIndexAstar][0] - 1;
                        queueAstar[queueSizeAstar][1] = queueAstar[queueIndexAstar][1];
                        visitedAstar[queueAstar[queueIndexAstar][0] - 1][queueAstar[queueIndexAstar][1]] = 1;
                        queueSizeAstar++;
                    }
                
            }

        }

        // DFS 
        if (goingDfs) {
            // only update timer every 1000 frames
            timerDfs = GetTime();
            // check if we are at the end
            if (stackSizeDfs < 0) {
                goingDfs = 0;
                printf("not found\n");
            } else {
                int cur_x = stackDfs[stackSizeDfs][0];
                int cur_y = stackDfs[stackSizeDfs][1];
                stackSizeDfs--;
                printf("cur_x: %d, cur_y: %d\n", cur_x, cur_y);
                printf("after stackSizeDfs: %d\n", stackSizeDfs);
                if (gridDfs[cur_x][cur_y] == 2) {
                    goingDfs = 0;
                    printf("found\n");
                } else {
                    printf("not found yet\n");

                    // check if we add up
                    if (cur_y - 1 >= 0) {
                        int up = gridDfs[cur_x][cur_y - 1];
                        int up_visited = visitedDfs[cur_x][cur_y - 1];
                        if ((up == 0 || up == 2) && up_visited == 0) {
                            printf("up\n");
                            stackSizeDfs++;
                            visitedDfs[cur_x][cur_y] = 1;
                            stackDfs[stackSizeDfs][0] = cur_x;
                            stackDfs[stackSizeDfs][1] = cur_y - 1;
                        }
                    }

                    // check if we can go down
                    if (cur_y + 1 < grid_size) {
                        int down = gridDfs[cur_x][cur_y + 1];
                        int down_visited = visitedDfs[cur_x][cur_y + 1];
                        if ((down == 0 || down == 2) && down_visited == 0) {
                            printf("down\n");
                            visitedDfs[cur_x][cur_y] = 1;
                            stackSizeDfs++;
                            stackDfs[stackSizeDfs][0] = cur_x;
                            stackDfs[stackSizeDfs][1] = cur_y + 1;
                        }
                    }
                    
                    // check if we can go left
                    if (cur_x - 1 >= 0) {
                        int left = gridDfs[cur_x - 1][cur_y];
                        int left_visited = visitedDfs[cur_x - 1][cur_y];
                        if ((left == 0 || left == 2) && left_visited == 0) {
                            printf("left\n");
                            visitedDfs[cur_x][cur_y] = 1;
                            stackSizeDfs++;
                            stackDfs[stackSizeDfs][0] = cur_x - 1;
                            stackDfs[stackSizeDfs][1] = cur_y;
                        }
                    }
                    
                    // check if we can go right
                    if (cur_x + 1 < grid_size) {
                        int right = gridDfs[cur_x + 1][cur_y];
                        int right_visited = visitedDfs[cur_x + 1][cur_y];
                        if ((right == 0 || right == 2) && right_visited == 0) {
                            printf("right\n");
                            visitedDfs[cur_x][cur_y] = 1;
                            stackSizeDfs++;
                            printf("stackSizeDfs: %d\n", stackSizeDfs);
                            stackDfs[stackSizeDfs][0] = cur_x + 1;
                            stackDfs[stackSizeDfs][1] = cur_y;
                        }
                    }
                }
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
                } else if (grid[i][j] == 2) {
                    DrawRectangle(i * 8, j * 8, 8, 8, RED);
                } else {
                    DrawRectangle(i * 8, j * 8, 8, 8, WHITE);
                }
                if (gridDfs[i][j] == 1) {
                    DrawRectangle(i * 8 + grid_size*8, j * 8, 8, 8, BLACK);
                } else if (visitedDfs[i][j] == 1) {
                    DrawRectangle(i * 8 + grid_size*8, j * 8, 8, 8, LIME);
                } else if (gridDfs[i][j] == 2) {
                    DrawRectangle(i * 8 + grid_size*8, j * 8, 8, 8, RED);
                } else {
                    DrawRectangle(i * 8 + grid_size*8, j * 8, 8, 8, WHITE);
                }
            }
        }
        // timer on the corner in the bfs
        DrawText(TextFormat("%.2f", timer), 10, 20, 50, SKYBLUE);
        // timer on the corner in the dfs
        DrawText(TextFormat("%.2f", timerDfs), grid_size*8 + 10, 20, 50, SKYBLUE);
        // border between 
        DrawRectangle(grid_size*8, 0, 4, grid_size*8, SKYBLUE);
        // start button
        //DrawText("Start with spacebar", 10, 10, 20, BLUE);


        ClearBackground(RAYWHITE);
                

        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

