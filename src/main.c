#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "physics.h"

int main() {
    int screen_width = 800;
    int screen_height = 600;

    InitWindow(screen_width, screen_height, "nbody");
    /* SetWindowState(FLAG_VSYNC_HINT); */
    SetTargetFPS(20);

    const float gravity = 9.8f;

    float ball_radius = 30.0f;
    float coeff_restitution = 1.0f;
    Vector2 ball_position = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    Vector2 ball_speed = {0.0f, 0.0f};
    Vector2 ball_acceleration = {0.0f, 10000.0f};

    while (!WindowShouldClose()) {
        float delta_time = GetFrameTime();
        ball_position.x += ball_speed.x * delta_time;
        ball_position.y += ball_speed.y * delta_time;
        ball_speed.x += ball_acceleration.x / 2.0f * delta_time;
        ball_speed.y += ball_acceleration.y / 2.0f * delta_time;

        if (ball_position.y + ball_radius >= GetScreenHeight()) {
            float prev_speed_y = ball_speed.y - ball_acceleration.y / 2.0f * delta_time;
            float prev_position_y = ball_position.y - prev_speed_y * delta_time;
            float k = (screen_height - ball_radius - prev_position_y)
                        / (prev_speed_y * delta_time);
            /* goal_speed = prev_speed_y                                             */
            /*             + ball_acceleration.y * delta_time * k                    */
            /*             + ball_acceleration.y / 2.0f * delta_time;                */
            /* goal_speed = ball_speed.y - ball_acceleration.y / 2.0f * delta_time   */
            /*             + ball_acceleration.y * delta_time * k                    */
            /*             + ball_acceleration.y / 2.0f * delta_time;                */
            /* goal_speed = ball_speed.y + ball_acceleration.y * delta_time * k      */
            /* ball_speed.y = prev_speed_y + ball_acceleration.y * delta_time * k; */
                         /* + ball_acceleration.y / 2.0f * delta_time; */
            ball_speed.y += ball_acceleration.y * delta_time * k
                          - ball_acceleration.y * delta_time;
            ball_speed.y *= -coeff_restitution;
            ball_position.y = screen_height - ball_radius;
        }

        if ((ball_position.x - ball_radius <= 0 && ball_speed.x < 0) ||
            (ball_position.x + ball_radius >= GetScreenWidth() && ball_speed.x > 0)) {
            ball_speed.x *= -coeff_restitution;
        }

        ball_speed.x += ball_acceleration.x / 2.0f * delta_time;
        ball_speed.y += ball_acceleration.y / 2.0f * delta_time;

        BeginDrawing();
        {
            ClearBackground(BLACK);
            DrawCircleV(ball_position, (float)ball_radius, MAROON);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
