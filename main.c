#include "raylib.h"
#include <stdio.h>
#include <math.h>

int main(void) {
    // Initialization
    // Get the primary monitor's width and height
    //MONITOR_DEFAULT_PRIMARY=GetCurrentMonitor();

    InitWindow(0, 0, "Raylib Blue Square Example - Adaptive Resolution");

    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);
    const int screenArea=screenWidth*screenHeight;
    const float screenDiagonal = sqrt((float)screenArea);

    printf("Key Square Position: X: %d, Y: %d\n", screenWidth, screenHeight);

    // Define the size of the squares as a percentage of the screen width
    const float MouseSquareSizePercent = 0.05f; // 20% of the screen width for the blue square
    const float KeySquareSizePercent = 0.02f; // 5% of the screen width for the red square

    const float MouseSquareSize = screenWidth * MouseSquareSizePercent;
    const float KeySquareSize = screenWidth * KeySquareSizePercent;
    
    Color MouseColor = BLUE;
    Color KeyColor = RED;

    Vector2 MouseSquarePosition = { (screenWidth - MouseSquareSize) / 2, (screenHeight - MouseSquareSize) / 2 };
    Vector2 KeySquarePosition = { (screenWidth - KeySquareSize) / 2, (screenHeight - KeySquareSize) / 2 };
    
  

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        Vector2 mousePosition = GetMousePosition();
        MouseSquarePosition.x = mousePosition.x - MouseSquareSize / 2;
        MouseSquarePosition.y = mousePosition.y - MouseSquareSize / 2;

        //moving the red square

        float deltaTime = GetFrameTime();
        const float moveSpeed = screenDiagonal*0.3f; // Units per second
        if (IsKeyDown(KEY_RIGHT)) KeySquarePosition.x += moveSpeed * deltaTime;
        if (IsKeyDown(KEY_LEFT))  KeySquarePosition.x -= moveSpeed * deltaTime;
        if (IsKeyDown(KEY_UP))    KeySquarePosition.y -= moveSpeed * deltaTime;
        if (IsKeyDown(KEY_DOWN))  KeySquarePosition.y += moveSpeed * deltaTime;

        // if (IsKeyDown(KEY_SPACE)) {
        //     printf("Key Square Position: X: %f, Y: %f\n", KeySquarePosition.x, KeySquarePosition.y);
        // }

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangleV(MouseSquarePosition, (Vector2){ MouseSquareSize, MouseSquareSize }, MouseColor);
            DrawRectangleV(KeySquarePosition, (Vector2){ KeySquareSize, KeySquareSize }, KeyColor);
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
