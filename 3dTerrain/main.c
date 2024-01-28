#include "raylib.h"
#include <stdlib.h>
#include "raymath.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "terrain");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Image heightmap = LoadImage("image3.png"); // Load your heightmap image
    Vector3 size = { 100.0f, 100.0f, 100.0f }; // Define the size of your terrain

    Mesh mesh = GenMeshHeightmap(heightmap, size); // Generate the mesh

    Material material = LoadMaterialDefault();

    Texture2D heightmapTexture = LoadTextureFromImage(heightmap);

    material.maps[MATERIAL_MAP_ALBEDO].texture = heightmapTexture;

    MaterialMap map = { 0 };
    map.color = RED;

    // Create a Material struct and set its diffuse field
    material.maps[MATERIAL_MAP_DIFFUSE] = map;


    DisableCursor(); // Disable cursor for first person camera

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FREE);      // Update camera
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                //mesh, material, matrix
                DrawMesh(mesh, material, MatrixIdentity());

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawText("haha", 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    UnloadMesh(mesh); // Unload mesh data
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
