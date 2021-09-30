#include "raylib.h"

using namespace std;

int main()
{
    int width{800};
    int height{500};

    int circleX{200};
    int circleY{200};
    int circleRadius = 25;
    int circleMoveSpeed = 5;
    int lCircleX{circleX - circleRadius};
    int rCircleX{circleX + circleRadius};
    int uCircleY{circleY - circleRadius};
    int bCircleY{circleY + circleRadius};

    int axeX{400};
    int axeY{0};
    int axeWidth{50};
    int axeHeight{50};
    int axeDirection{10};
    int lAxeX{axeX};
    int rAxeX{axeX + axeWidth};
    int uAxeY{axeY};
    int bAxeY{axeY + axeHeight};

    char text[] = "Whatever bullshit";
    bool circleCollidesWithAxe = bAxeY >= uCircleY && 
                                 uAxeY <= bCircleY && 
                                 lAxeX <= rCircleX && 
                                 rAxeX >= lCircleX;

    InitWindow(width, height, text);

    SetTargetFPS(60);

    while (WindowShouldClose() != true) {
        BeginDrawing();
        ClearBackground(WHITE);
        
        if(circleCollidesWithAxe) {
            DrawText("Game Over!", 400, 200, 20, RED);
        } else {
            lCircleX = circleX - circleRadius;
            rCircleX = circleX + circleRadius;
            uCircleY = circleY - circleRadius;
            bCircleY = circleY + circleRadius;

            lAxeX = axeX;
            rAxeX = axeX + axeWidth;
            uAxeY = axeY;
            bAxeY = axeY + axeHeight;

            if (bAxeY >= uCircleY && uAxeY <= bCircleY && lAxeX <= rCircleX && rAxeX >= lCircleX) {
                circleCollidesWithAxe = true;
            };

            if(IsKeyDown(KEY_S) && circleY <= height - circleRadius) {
                circleY += circleMoveSpeed;
            }
            if(IsKeyDown(KEY_W) && circleY >= circleRadius) {
                circleY -= circleMoveSpeed;
            }
            if(IsKeyDown(KEY_D) && circleX <= width - circleRadius) {
                circleX += circleMoveSpeed;
            }
            if(IsKeyDown(KEY_A) && circleX >= circleRadius) {
                circleX -= circleMoveSpeed;
            }

            axeY += axeDirection;

            if(axeY > height - axeHeight || axeY < 0) {
                axeDirection = -axeDirection;
            }            

            DrawCircle(circleX, circleY, circleRadius, BLUE);

            DrawRectangle(axeX, axeY, axeWidth, axeHeight, RED);
        }

        EndDrawing();
    }
}