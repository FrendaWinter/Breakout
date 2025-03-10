#include "raylib.h"
#include <math.h>

// Function to check collision side (returns "long" or "short" side)
int GetCollisionSide(Vector2 circlePos, Rectangle rect) {
    // Find the closest point on the rectangle to the circle
    float closestX = fmax(rect.x, fmin(circlePos.x, rect.x + rect.width));
    float closestY = fmax(rect.y, fmin(circlePos.y, rect.y + rect.height));

    // Calculate distances from the center of the circle
    float distX = fabs(circlePos.x - closestX);
    float distY = fabs(circlePos.y - closestY);

    // Determine if collision happens on the long or short side
    if ((rect.width >= rect.height && distY > distX) || 
        (rect.height > rect.width && distX > distY)) {
		// Long side
        return 1;
    } else {
		// Shor side
        return 2;
    }
}


#define WIDTH 800
#define HEIGHT 450

int main () {
	// Enables 4x Multi-Sample Anti-Aliasing (MSAA), which smooths edges and reduces aliasing effects. (If supported)
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(WIDTH, HEIGHT, "Breakout!");

	// Ball
    Vector2 ballPosition = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    int ballRadius = 20;
	// Platform
	Vector2 platformPos = {350, 420};
	Vector2 platformSize = {100, 30};
	Rectangle platform = {platformPos.x, platformPos.y, platformSize.x, platformSize.y};
	int platformSpeed = 5;

	// Game variable
    bool pause = 0;
    int framesCounter = 0;
	bool ballPlatformCollision = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;

        if (!pause)
        {
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;

            // Check walls collision for bouncing
            if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
            if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.0f;
			
			if (IsKeyDown(KEY_A) && platform.x >= 0)
			{
				platform.x -= platformSpeed;	
			}

			if (IsKeyDown(KEY_D) && platform.x <= 700)
			{
				platform.x += platformSpeed;
			}
			
			ballPlatformCollision = CheckCollisionCircleRec(ballPosition, ballRadius, platform);
			int collisionSide = ballPlatformCollision ? GetCollisionSide(ballPosition, platform) : 0;
			if (collisionSide == 1)
			{
				ballSpeed.y *= -1.0f;
			} 
			if (collisionSide == 2) {
				ballSpeed.x *= -1.0f;
			}
        }
        else framesCounter++;

        //-----------------------------------------------------

        // Draw
        //-----------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawCircleV(ballPosition, (float)ballRadius, MAROON);
			DrawRectangleRec(platform, RED);

            // On pause, we draw a blinking message
            if (pause && ((framesCounter/30)%2)) DrawText("PAUSED", 350, 200, 30, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

	return 0;
}
