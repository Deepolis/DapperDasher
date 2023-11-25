#include "raylib.h"
#include <cmath>

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    int windowDimension[2];
    windowDimension[0] = 1536;
    windowDimension[1] = 900;

    InitWindow(windowDimension[0], windowDimension[1], "Sophia's Run Game");

    // scarfy jump variables
    int velocity{0};
    const int gravity{2000};
    const int jumpVelocity{-700};
    bool isInAir{};

    //nebula Texture Variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    int nebulaVel{-400};

    //scarfy Texture Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    //AnimData for scarfy
    AnimData scarfyData
    {
        {0.0, 0.0, scarfy.width/6.0, scarfy.height}, // Rectangle initialize
        {windowDimension[0]/2 - scarfyData.rec.width, windowDimension[1] - scarfyData.rec.height}, // Rectangle position offset by 300
        0, // int nebAnimationFrame
        1.0/12.0, // float nebUpdateTime
        0.0  // int nebRunningTime
    };

    const int sizeOfNebulae{10};

    AnimData nebulae[sizeOfNebulae]{};
    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimension[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/16.0;
        nebulae[i].pos.x = windowDimension[0] + i * 450;
    }

    Texture2D foreground = LoadTexture("textures/foreground.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    float mgX{};
    float fgX{};

    float finishLine{nebulae[sizeOfNebulae -1].pos.x};

    bool collision{false};

    SetTargetFPS(60);
    while(!WindowShouldClose()) //Window should only close when X or ESC are hit
    {
        const float dT{GetFrameTime()}; //Time between frames

        BeginDrawing();
        ClearBackground(WHITE);

        //back, mid, & foreground creation
        bgX -= 200 * dT;
        mgX -= 400 * dT;
        fgX -= 600 * dT;

        if (bgX <= -background.width*6)
        {
            bgX = 0.0;
        }

        if (mgX <= -midground.width*6)
        {
            mgX = 0.0;
        }

        if (fgX <= -foreground.width*6)
        {
            fgX = 0.0;
        }

        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 6.0, WHITE);
        Vector2 bg2Pos{bgX + background.width*6, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 6.0, WHITE);

        Vector2 mgPos{mgX, 0.0};
        DrawTextureEx(midground, mgPos, 0.0, 6.0, WHITE);
        Vector2 mg2Pos{mgX + midground.width*6, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 6.0, WHITE);

        Vector2 fgPos{fgX, 0.0};
        DrawTextureEx(foreground, fgPos, 0.0, 6.0, WHITE);
        Vector2 fg2Pos{fgX + foreground.width*6, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 6.0, WHITE);
        //end creation

        if(isOnGround(scarfyData, windowDimension[1])) //if scarfy's position on the ground
        {
            velocity = 0;
            isInAir = false;
        }
        else //scary is in the air, so his velocity is gravity (1000 pixels/s^2). positive because down Y is positive
        {
            velocity += gravity * dT;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir) //is SPACE pressed will only work if he is on the ground
        {
            velocity += jumpVelocity;
            scarfyData.runningTime = 0;
        }

        scarfyData.pos.y += velocity * dT;

        finishLine += nebulaVel * dT;

        if (!isInAir) //animation freezes when he is in the air
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebulaVel * dT;
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        for (AnimData nebula : nebulae)
        {
            float pad{20};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.height - 2*pad,
                nebula.rec.width - 2*pad,
            };
            Rectangle scarfyRec{
                scarfyData.pos.x + pad,
                scarfyData.pos.y + pad,
                scarfyData.rec.height - 2*pad,
                scarfyData.rec.width - 2*pad,
            };
            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }

        if (collision)
        {
            DrawText("Game Over!!", windowDimension[0]/2, windowDimension[1]/2, 40, RED);
        }
        else if (scarfyData.rec.x >= finishLine)
        {
            DrawText("YOU WIN!!!!!!", windowDimension[0]/2, windowDimension[1]/2, 40, RED);
        }
        else
        {
            for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
        
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}