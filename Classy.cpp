#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    const int windowWidth{2000};
    const int windowHeight{1500};
    InitWindow(windowWidth, windowHeight, "Classy");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0};

    Character knight{windowWidth, windowHeight};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        knight.tick(GetFrameTime());

        //check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }
    CloseWindow();
}
