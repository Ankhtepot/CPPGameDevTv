#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width/maxFrames;
    height = texture.height;

    screenPos = {
        static_cast<float>(winWidth)/2.0f - mapScale * (0.5f * width),
        static_cast<float>(winHeight)/2.0f - mapScale * (0.5f * height)
    };
} 

void Character::tick(float deltaTime) {
    Vector2 direction{};
    if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))) {
        direction.x -= 1.0;
    }
    if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))) {
        direction.x += 1.0;
    }
    if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))) {
        direction.y -= 1.0;
    }
    if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))) {
        direction.y += 1.0;
    }

    if (Vector2Length(direction) != 0.0) {
        Vector2 normalizedDirection = Vector2Normalize(direction);
        worldPosLastFrame = worldPos;
        worldPos = Vector2Add(worldPos, Vector2Scale(normalizedDirection, movementSpeed));

        rightLeft = direction.x < 0.f 
            ? -1.f 
            : 1.f;

        texture = run;
    }
    else {
        texture = idle;
    }

    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        frame++;
        runningTime = 0.f;

        if (frame >= maxFrames) frame = 0;
    }

    Rectangle source{frame * width,
        0.f,
        rightLeft * width,
        height};
    Rectangle dest{screenPos.x,
        screenPos.y,
        mapScale * width,
        mapScale * height};
    DrawTexturePro(texture, source, dest, Vector2Zero(), 0.f, WHITE);
}

void Character::undoMovement() 
{
    worldPos = worldPosLastFrame;
}

Rectangle Character::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * mapScale,
        height * mapScale
    };
}