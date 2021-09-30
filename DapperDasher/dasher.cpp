#include "raylib.h"
#include <algorithm>

using namespace std;

struct AnimData 
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight) {
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, const float deltaTime, const int maxFrame) {    
    data.runningTime += deltaTime;

    if (data.runningTime >= data.updateTime) {

        data.runningTime = 0.0;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;

        if (data.frame > maxFrame) {
            data.frame = 0;
        }
    }

    return data;
}

int updateBckground(Texture2D background, float x) {
    float newX = x;
     if (newX <= -background.width*2) {
        newX = 0.0;
    }

    Vector2 bg1Pos{newX, 0.0};
    DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
    Vector2 bg2Pos{newX + background.width * 2, 0.0};
    DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

    return newX;
}

int main() 
{
    const int windowDimensions[2]{512,380};
    const char title[] = "Dapper Dasher";

    InitWindow(windowDimensions[0], windowDimensions[1], title);

    Texture2D scarfyTexture = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{
        {0.0, 0.0, scarfyTexture.width/6, scarfyTexture.height},
        {windowDimensions[0] /2 - scarfyTexture.width/6 / 2, windowDimensions[1] - scarfyTexture.height},
        0,
        1.0 / 12.0,
        0.0
    };

    Texture2D nebulaTexture = LoadTexture("textures/12_nebula_spritesheet.png");
    int nebulaVelocity{-200};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};

    Texture2D midground = LoadTexture("Textures/back-buildings.png");
    float mgX{};

    Texture2D foreground = LoadTexture("Textures/foreground.png");
    float fgX{};

    const int sizeOfNebulae{1};
    AnimData nebulae[sizeOfNebulae]{};

    for(int i{0}; i < sizeOfNebulae; i++) {
        AnimData nebData{
        {0.0, 0.0, nebulaTexture.width/8, nebulaTexture.height/8},
        {windowDimensions[0] + i * 300, windowDimensions[1] - nebulaTexture.height / 8},
        0, 
        1.0 / (12.0 + i * 4), 
        0.0
        };

        nebulae[i] = nebData;
    }

    float finishLine{ nebulae[sizeOfNebulae - 1].pos.x + 200 };

    const int gravity{1000};

    int scarfyGroundHeight{windowDimensions[1] - scarfyData.rec.height};
    int velocity{0};
    int jumpVelocity{-600};
    bool isScarfyJumping{false};

    SetTargetFPS(60);
    float deltaTime{};

    bool collision{false};
    bool finished{false};

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(WHITE);

        deltaTime = GetFrameTime();

        bgX -= 20 * deltaTime;
        mgX -= 40 * deltaTime;
        fgX -= 80 * deltaTime;

        if (bgX <= -background.width*2) {
            bgX = 0.0;
        }

        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width * 2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        if (mgX <= -midground.width*2) {
            mgX = 0.0;
        }

        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX + midground.width * 2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        if (fgX <= -foreground.width*2) {
            fgX = 0.0;
        }

        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX + foreground.width * 2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);
        // bgX = updateBckground(background, bgX);
        // mgX = updateBckground(midground, mgX);
        // fgX = updateBckground(foreground, fgX);


        if (isOnGround(scarfyData, windowDimensions[1]))
        {
            //rectangle is on the ground
            velocity = 0;
            scarfyData.pos.y = scarfyGroundHeight;
            isScarfyJumping = false;
        }
        else
        {
            // rectangle is in the air
            velocity += gravity * deltaTime;
        }

        if(IsKeyPressed(KEY_SPACE) && !isScarfyJumping) {
            velocity += jumpVelocity;
            isScarfyJumping = true;
            scarfyData.frame = 0;
        }

        scarfyData.pos.y += velocity * deltaTime;
        
        for (AnimData nebula : nebulae) {
            float padding{50};
            Rectangle nebRec{
                nebula.pos.x + padding,
                nebula.pos.y + padding,
                nebula.rec.width - 2 * padding,
                nebula.rec.height - 2 * padding
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            
            // DrawRectangle(finishLine, windowDimensions[1] - 500, 200, 500, GREEN);
            if (CheckCollisionRecs(nebRec, scarfyRec)) {
                collision = true;
            }

            if (scarfyData.pos.x >= finishLine) {
                collision = true;
                finished = true;
            }
        }

        if (!collision) {
            if (!isScarfyJumping) {
                scarfyData = updateAnimData(scarfyData, deltaTime, 5);
            }        

            DrawTextureRec(scarfyTexture, scarfyData.rec, scarfyData.pos, WHITE);

            for(int i{0}; i < sizeOfNebulae; i++) {
                nebulae[i] = updateAnimData(nebulae[i], deltaTime, 7);    
                nebulae[i].pos.x += nebulaVelocity * deltaTime;
                DrawTextureRec(nebulaTexture, nebulae[i].rec, nebulae[i].pos, WHITE);        
            }

            finishLine += nebulaVelocity * deltaTime;

            // DrawRectangle(finishLine, windowDimensions[1] - 500, 200, 500, GREEN);
        }
        else
        {
            finished 
                ? DrawText("YOU WON", windowDimensions[0]/2 - 100, windowDimensions[1]/2 - 20, 40, RED)
                : DrawText("GAME OVER", windowDimensions[0]/2 - 150, windowDimensions[1]/2 - 20, 40, RED);
        }

        EndDrawing();
    }

    UnloadTexture(scarfyTexture);
    UnloadTexture(nebulaTexture);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);

    CloseWindow();
}