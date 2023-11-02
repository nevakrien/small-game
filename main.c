#include "raylib.h"
#include <stdio.h>
#include <math.h>

int main(void) {
    // Initialization
    const int initialScreenWidth = 800;
    const int initialScreenHeight = 450;
    InitWindow(initialScreenWidth, initialScreenHeight, "Raylib Resizable Window with Zoom");

    // Set our window to be resizable
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Define squares properties
    const float redSquareSize = 50.0f; // Size of the red square
    const float blueSquareSize = 30.0f; // Size of the blue square
    Vector2 redSquarePosition = { initialScreenWidth / 2.0f, initialScreenHeight / 2.0f };
    Vector2 blueSquarePosition = { 0.0f, 0.0f }; // This will be updated to follow the mouse

    // Define movement speed for the red square
    const float squareSpeed = 200.0f;

    // Initialize the camera
    Camera2D camera = { 0 };
    camera.target = redSquarePosition;
    camera.offset = (Vector2){ initialScreenWidth / 2, initialScreenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Set Target FPS (Frames per second)
    SetTargetFPS(60);

    // Main game loop
    float lastTime = GetTime();
    while (!WindowShouldClose()) {
        // Update
        // Handle zoom with mouse wheel
        camera.zoom += GetMouseWheelMove() * 0.05f;
        camera.zoom = fmaxf(camera.zoom, 0.1f); // Prevent zoom from going too small
        camera.zoom = fminf(camera.zoom, 3.0f); // Prevent zoom from going too large

        // Check if the window has been resized
        if (IsWindowResized()) {
            camera.offset = (Vector2){ GetScreenWidth() / 2, GetScreenHeight() / 2 };
        }

        // Calculate the delta time (time since last frame)
        float currentTime = GetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime; // Update lastTime for the next frame

        // Update the red square's position based on arrow key input
        if (IsKeyDown(KEY_RIGHT)) redSquarePosition.x += squareSpeed * GetFrameTime();
        if (IsKeyDown(KEY_LEFT)) redSquarePosition.x -= squareSpeed * GetFrameTime();
        if (IsKeyDown(KEY_UP)) redSquarePosition.y -= squareSpeed * GetFrameTime();
        if (IsKeyDown(KEY_DOWN)) redSquarePosition.y += squareSpeed * GetFrameTime();

        // Update camera target to follow the red square
        //camera.target = redSquarePosition;

        // Convert mouse position to world space
        blueSquarePosition = GetScreenToWorld2D(GetMousePosition(), camera);
        blueSquarePosition.x -= blueSquareSize / 2; // Center the square on the mouse
        blueSquarePosition.y -= blueSquareSize / 2;

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                // Draw the red square
                DrawRectangleV(redSquarePosition, (Vector2){ redSquareSize, redSquareSize }, RED);

                // Draw the blue square
                DrawRectangleV(blueSquarePosition, (Vector2){ blueSquareSize, blueSquareSize }, BLUE);
            EndMode2D();
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
