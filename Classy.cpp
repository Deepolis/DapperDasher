#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth{500};
    const int windowHeight{400};
    InitWindow(windowWidth, windowHeight, "Classy");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0};

    Character knight{windowWidth, windowHeight};

    Enemy goblin{
            Vector2{100.f, 500.f},
            LoadTexture("characters/goblin_idle_spritesheet.png"),
            LoadTexture("characters/goblin_run_spritesheet.png")};
          
    Enemy slime{
        Vector2{1000.f, 900.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};

    goblin.setTarget(&knight);

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

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

        if (!knight.getAlive())
        {
            DrawText("!gAmE OvER!",  60.f, 50.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0 , 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);

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

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        for (auto enemy : enemies)
        {
            if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getCollisionRec()))
            {
                enemy->setAlive(false);
            }
        }
    }
        EndDrawing();
    }
    CloseWindow();
}
