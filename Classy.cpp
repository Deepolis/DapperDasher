#include "raylib.h"
#include "raymath.h"

class Character
{   
public:
    Vector2 getWorldPos() {return worldPos;}
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    //direction
    float rightLeft{1.f};
    //animation variables
    float runningTime{};
    const float updateTime{1.f/12.f};
    int frame{};
    const int maxFrames{6};
    const float speed{4.f};
};

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {(float)winWidth/2.0f - 4.0f * (0.5f * (float)texture.width/6.0f),
                 (float)winHeight/2.0f - 4.0f * (0.5f * (float)texture.height)};
}

void Character::tick(float deltaTime)
{
   Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (Vector2Length(direction) != 0.0)
        {    
            //We normalize because the diagonal magnitude would be > 1.
            // mapPos - direction moves the map opposite the direction to give running appearance 
            worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
            //if we have an if/else each with 1 statement, we can use a turnary operator, used on 3 arguments.
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            texture = run;
        }
        else
        {
            texture = idle;
        }
    //get the delta time
        runningTime += deltaTime;
        //iterate through frames overtime
        if(runningTime >= updateTime)
        {
            frame++;
            runningTime = 0;
            if (frame > maxFrames) frame = 0;
        }
        //location on sprite sheet. multiply rightLeft to reverse the width of the sprite sheet. Flipping it.
        Rectangle knightSource{frame * (float)texture.width/6.f, 0.f, rightLeft * (float)texture.width/6.f, (float)texture.height};
        //location to draw on map
        Rectangle knightDest{screenPos.x, screenPos.y, 4.0f * (float)texture.width/6.0f, 4.0f *(float)texture.height};
        // Vector2 is the origin used as a reference point for scaling and rotation
        DrawTexturePro(texture, knightSource, knightDest, Vector2{}, 0.f, WHITE);
}

int main()
{
    const int windowWidth{600};
    const int windowHeight{600};
    InitWindow(windowWidth, windowHeight, "Classy");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);
    // Coordinates of knight factoring in scaling
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
        knight.tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow();
}
