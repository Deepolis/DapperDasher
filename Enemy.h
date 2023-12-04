#include "raylib.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    Vector2 getWorldPos() {return worldPos;}
    void tick(float deltaTime);

    void undoMovement();
    Rectangle getCollisionRec();

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    //direction
    float rightLeft{1.f};
    //animation variables
    float runningTime{};
    float updateTime{1.f/12.f};
    int frame{};
    int maxFrames{6};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};

};