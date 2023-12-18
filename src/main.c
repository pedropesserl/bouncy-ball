#include <stdio.h>
#include <math.h>
#include "raylib.h"

int main() {

    int screen_width = 800;
    int screen_height = 600;

    InitWindow(screen_width, screen_height, "nbody");
    SetTargetFPS(60);

    float ball_radius = 40.0f;
    float coeff_restitution = 1.0f;
    Vector2 ball_position = {GetScreenWidth()/2.0f, ball_radius};
    Vector2 ball_speed = {0.0f, 0.0f};
    Vector2 ball_acceleration = {0.0f, 0.5f};

    const float gravity = 9.8f;

    while (!WindowShouldClose()) {
        ball_position.x += ball_speed.x;
        ball_position.y += ball_speed.y;
        ball_speed.x += ball_acceleration.x / 2;
        ball_speed.y += ball_acceleration.y / 2;

        if (ball_position.y >= GetScreenHeight() - ball_radius) {
            ball_position.y = screen_height - ball_radius;
            ball_speed.y *= -coeff_restitution;
        }

        ball_speed.x += ball_acceleration.x / 2;
        ball_speed.y += ball_acceleration.y / 2;

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawCircleV(ball_position, (float)ball_radius, MAROON);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
