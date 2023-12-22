#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "physics.h"

int main() {
    int screen_width = 800;
    int screen_height = 600;

    InitWindow(screen_width, screen_height, "nbody");
    /* SetWindowState(FLAG_VSYNC_HINT); */
    SetTargetFPS(60);

    float ball_radius = 30.0f;
    float coeff_restitution = 1.0f;
    float initial_height = GetScreenHeight()/2.0f;
    float displacement = GetScreenHeight() - initial_height;
    Vector2 ball_position = {GetScreenWidth()/2.0f, initial_height};
    Vector2 ball_speed = {0.0f, 0.0f};
    Vector2 ball_acceleration = {0.0f, 20000.0f};

    while (!WindowShouldClose()) {
        float delta_time = GetFrameTime();
        ball_position.x += ball_speed.x * delta_time;
        ball_position.y += ball_speed.y * delta_time;

        ball_speed.x += ball_acceleration.x / 2.0f * delta_time;
        ball_speed.y += ball_acceleration.y / 2.0f * delta_time;


        // looks good in the ground, height issues
        if (ball_position.y + ball_radius >= GetScreenHeight()) {
            float prev_speed_y = ball_speed.y - ball_acceleration.y / 2.0f * delta_time;
            // v_f^2 = v_0^2 + 2*a*Δs
            ball_speed.y = sqrtf(prev_speed_y * prev_speed_y + 2 * ball_acceleration.y * delta_time * displacement);
            ball_speed.y *= -coeff_restitution;
            ball_position.y = screen_height - ball_radius;
        }

        // perfect height, goes through the ground
        /* if (ball_position.y + ball_radius >= GetScreenWidth() && ball_speed.y > 0) { */
        /*     ball_speed.y *= -coeff_restitution; */
        /* } */

        if ((ball_position.x - ball_radius <= 0 && ball_speed.x < 0) ||
            (ball_position.x + ball_radius >= GetScreenWidth() && ball_speed.x > 0)) {
            ball_speed.x *= -coeff_restitution;
        }

        ball_speed.x += ball_acceleration.x / 2.0f * delta_time;
        ball_speed.y += ball_acceleration.y / 2.0f * delta_time;

        BeginDrawing();
        {
            ClearBackground(BLACK);
            DrawCircleV(ball_position, ball_radius, MAROON);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
