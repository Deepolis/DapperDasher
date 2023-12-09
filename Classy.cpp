#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "prop.h"
#include "Enemy.h"

int main()
{
    const int windowWidth{1000};
    const int windowHeight{800};
    InitWindow(windowWidth, windowHeight, "Classy");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0};

    Character knight{windowWidth, windowHeight};

    Enemy goblin{
            Vector2{400.f, 500.f},
            LoadTexture("characters/goblin_idle_spritesheet.png"),
            LoadTexture("characters/goblin_run_spritesheet.png")};
    goblin.setTarget(&knight);

    Prop props[2]{
            Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
            Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}

    };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());

        //check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        //check prop collisions.
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }

        }

        goblin.tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow();
}
