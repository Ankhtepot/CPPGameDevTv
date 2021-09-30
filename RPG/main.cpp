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

int main()
{
    const int windowDimensions[2]{384,384};
    const char title[] = "RPG";

    InitWindow(windowDimensions[0], windowDimensions[1], title);

    Texture2D map = LoadTexture("TileSets/worldMap.png");

    SetTargetFPS(60);
    float deltaTime{};

    bool collision{false};
    bool finished{false};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        deltaTime = GetFrameTime();

        Vector2 mapPos {0.0, 0.0};

        DrawTextureEx(map, mapPos, 0, 4.0, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();
}