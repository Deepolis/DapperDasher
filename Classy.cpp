#include "raylib.h"
#include "raymath.h"

int main()
{
    const int windowWidth{600};
    const int windowHeight{600};
    InitWindow(windowWidth, windowHeight, "Stephen's Top Down");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    float speed{4.0};

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{ 
        (float)windowWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6.0),
        (float)windowHeight/2.0f - 4.0f * (0.5f * (float)knight.height)
    };
    Rectangle knightSource{0.f, 0.f, (float)knight.width/6.f, (float)knight.height};
    Rectangle knightDest{knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f *(float)knight.height};

    Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

    Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (Vector2Length(direction) != 0.0)
        {
            Vector2Normalize(direction); //We normalize because the diagonal magnitude would be > 1.
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
        }

        DrawTexturePro(knight, knightSource, knightDest, Vector2{}, 0.f, WHITE);

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    CloseWindow();
}
