#include <iostream>
#include "raylib.h"
#include <string>
#include <charconv>
#include <vector>
#include <unordered_set>
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

struct Snake
{
    Vector2 pos;
    Vector2 dir;
};


int main(void)
{

    // Initialization
    //------------------------------------------------------------------------------
    std::unordered_set<int> isPowerOfTen {10, 100, 1000, 10000, 100000};
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;
    const int GRID_SIZE = 20;
    int score = 0;
    int score_pos = 250;
    float speed = 2.0f;
    std::string score_string;
    SetTargetFPS(20);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My Game");
    std::vector<Snake> snake;
    Snake head = {{(float) SCREEN_WIDTH/2 - GRID_SIZE/2, (float) SCREEN_HEIGHT/2 - GRID_SIZE/2}, {GRID_SIZE, 0}};
    snake.push_back(head);

    Vector2 food = {(float) GetRandomValue(0, SCREEN_WIDTH / GRID_SIZE - 1) * GRID_SIZE, (float) GetRandomValue(0, SCREEN_HEIGHT / GRID_SIZE - 1) * GRID_SIZE };


    // GameLoop
    while(!WindowShouldClose()) {

        // Update
        //---------------------------------------------------------------------
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && snake[0].dir.x != -GRID_SIZE) {
            snake[0].dir = { GRID_SIZE, 0 };
        }
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && snake[0].dir.x != GRID_SIZE) {
            snake[0].dir = { -GRID_SIZE, 0 };
        }
        if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && snake[0].dir.y != GRID_SIZE) {
            snake[0].dir = { 0, -GRID_SIZE };
        }
        if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && snake[0].dir.y != -GRID_SIZE) {
            snake[0].dir = { 0, GRID_SIZE };
        }

        for (int i = snake.size() - 1; i > 0; i--) {
            snake[i].pos = snake[i - 1].pos;
        }

        snake[0].pos.x += snake[0].dir.x;
        snake[0].pos.y += snake[0].dir.y;


        if (snake[0].pos.x >= SCREEN_WIDTH + GRID_SIZE) {
            snake[0].pos.x = -50;
        } else if (snake[0].pos.x < -50) {
            snake[0].pos.x = SCREEN_WIDTH + GRID_SIZE;
        } else if (snake[0].pos.y < -50) {
            snake[0].pos.y = SCREEN_HEIGHT + GRID_SIZE;
        } else if (snake[0].pos.y >= SCREEN_HEIGHT + GRID_SIZE) {
            snake[0].pos.y = -50;
        }


        for (int i = 1; i < snake.size(); i++) {
            if (CheckCollisionRecs({ snake[0].pos.x, snake[0].pos.y, GRID_SIZE, GRID_SIZE },
                { snake[i].pos.x, snake[i].pos.y, GRID_SIZE, GRID_SIZE })) {
                snake.clear();
                snake.push_back(head);
                score = 0;
                score_pos = 250;
            }
        }



        if (CheckCollisionRecs({ snake[0].pos.x, snake[0].pos.y, GRID_SIZE, GRID_SIZE }, 
            { food.x, food.y, GRID_SIZE, GRID_SIZE })) {
            food = { (float)GetRandomValue(0, SCREEN_WIDTH / GRID_SIZE - 1) * GRID_SIZE, 
                     (float)GetRandomValue(0, SCREEN_HEIGHT / GRID_SIZE - 1) * GRID_SIZE };
            snake.push_back({ snake[snake.size() - 1].pos, {0, 0} });
            score++;
            if (isPowerOfTen.find(score) != isPowerOfTen.end()) {
                score_pos = score_pos - std::to_string(score).length() * 40;
            }
        }

        // Draw
        //------------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            score_string = std::to_string(score);
            DrawText(score_string.c_str(), score_pos, 50, 425, (Color){230, 31, 55, 150});
            DrawRectangle(food.x, food.y, GRID_SIZE, GRID_SIZE, RED);
            for (auto s : snake) {
                DrawRectangle(s.pos.x, s.pos.y, GRID_SIZE, GRID_SIZE, BLACK);
            }
        EndDrawing();
        
    }



    CloseWindow();
    
    return 0;
}
