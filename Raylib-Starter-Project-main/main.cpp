#include "raylib.h"
#include <iostream>

using namespace std;

const int screenWidth = 800;
const int screenHeight = 450;
const int paddleWidth = 20;
const int paddleHeight = 100;
const int ballSize = 20;

Vector2 leftPaddlePos = { 20, screenHeight / 2 - paddleHeight / 2 };
Vector2 rightPaddlePos = { screenWidth - 20 - paddleWidth, screenHeight / 2 - paddleHeight / 2 };
Vector2 ballPos = { screenWidth / 2 - ballSize / 2, screenHeight / 2 - ballSize / 2 };
Vector2 ballSpeed = { 5, 5 };



int leftScore = 0;
int rightScore = 0;

int main()
{
    InitWindow(screenWidth, screenHeight, "Pong Game");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        if (IsKeyDown(KEY_W) && leftPaddlePos.y > 0)
            leftPaddlePos.y -= 5;
        if (IsKeyDown(KEY_S) && leftPaddlePos.y < screenHeight - paddleHeight)
            leftPaddlePos.y += 5;

        if (IsKeyDown(KEY_UP) && rightPaddlePos.y > 0)
            rightPaddlePos.y -= 5;
        if (IsKeyDown(KEY_DOWN) && rightPaddlePos.y < screenHeight - paddleHeight)
            rightPaddlePos.y += 5;

        ballPos.x += ballSpeed.x;
        ballPos.y += ballSpeed.y;


        if (CheckCollisionRecs({ ballPos.x, ballPos.y, ballSize, ballSize }, { leftPaddlePos.x, leftPaddlePos.y, paddleWidth, paddleHeight }) ||
            CheckCollisionRecs({ ballPos.x, ballPos.y, ballSize, ballSize }, { rightPaddlePos.x, rightPaddlePos.y, paddleWidth, paddleHeight }))
        {
            ballSpeed.x = -ballSpeed.x;
        }


        if (ballPos.y <= 0 || ballPos.y + ballSize >= screenHeight)
        {
            ballSpeed.y = -ballSpeed.y;
        }


        if (ballPos.x <= 0)
        {
            rightScore++;
            ballPos = { screenWidth / 2 - ballSize / 2, screenHeight / 2 - ballSize / 2 };
        }
        else if (ballPos.x + ballSize >= screenWidth)
        {
            leftScore++;
            ballPos = { screenWidth / 2 - ballSize / 2, screenHeight / 2 - ballSize / 2 };
        }


        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(TextFormat("%d", leftScore), screenWidth / 4, 20, 30, BLUE);
        DrawText(TextFormat("%d", rightScore), screenWidth * 3 / 4 - MeasureText(TextFormat("%d", rightScore), 30), 20, 30, RED);

        DrawRectangleRec({ leftPaddlePos.x, leftPaddlePos.y, paddleWidth, paddleHeight }, BLUE);
        DrawRectangleRec({ rightPaddlePos.x, rightPaddlePos.y, paddleWidth, paddleHeight }, RED);
        DrawRectangleRec({ ballPos.x, ballPos.y, ballSize, ballSize }, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}