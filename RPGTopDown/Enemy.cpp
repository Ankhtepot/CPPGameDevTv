#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture)
    : worldPos(pos), idle(idleTexture), run(runTexture)
{
    width = texture.width/maxFrames;
    height = texture.height;
}

void Enemy::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

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

void Enemy::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle Enemy::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * mapScale,
        height * mapScale
    };
}