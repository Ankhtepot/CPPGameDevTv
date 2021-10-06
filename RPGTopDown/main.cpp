#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

using namespace std;

int main()
{
    const int windowDimensions[2]{384,384};
    const char title[] = "RPG";

    InitWindow(windowDimensions[0], windowDimensions[1], title);

    Texture2D map = LoadTexture("TileSets/worldMap.png");
    Vector2 mapPos {0.0, 0.0};
    const float mapScale{4.0f};

    SetTargetFPS(60);
    float deltaTime{};

    Character knight{windowDimensions[0], windowDimensions[1]};

    Enemy goblin{
        {400.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Prop props[2]{
        Prop{{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{{500.f, 400.f}, LoadTexture("nature_tileset/Log.png")}
    };

    while (!WindowShouldClose())
    {
        BeginDrawing(); 
        ClearBackground(WHITE);

        deltaTime = GetFrameTime();

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f); // multiplying Vector2 by -1
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(deltaTime);
        goblin.tick(deltaTime);
        Vector2 knightWorldPos = knight.getWorldPos();
        if (knightWorldPos.x < 0.f 
            || knightWorldPos.y < 0.f 
            || knightWorldPos.x + windowDimensions[0] > map.width * mapScale
            || knightWorldPos.y + windowDimensions[1] > map.height * mapScale) 
        {
            knight.undoMovement();
        }

        for (auto prop : props)
        {
            if (CheckCollisionRecs(
                knight.getCollisionRec(),
                prop.getCollisionRec(knight.getWorldPos())))
            {
                knight.undoMovement();
            }
        }

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();
}