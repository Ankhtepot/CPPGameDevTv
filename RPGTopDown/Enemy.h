#include "raylib.h"

class Enemy
{
public:
    Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();

private:
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Texture2D texture{idle};

    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    float width{};
    float height{};

    // 1: facing right -1: facing left
    float rightLeft{1.f};
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f/12.f};
    float movementSpeed{4.0};
    float mapScale{4.f};
};