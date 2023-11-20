#include "raylib.h"

int main()
{
    const int windowWidth{2000};
    const int windowHeight{1000};
    InitWindow(windowWidth, windowHeight, "Sophia's Run Game");

    // Character movement
    int velocity{0};
    const int gravity{1000};
    const int jumpVelocity{-600};
    bool isInAir{};

    //nebula Texture Variables weebd
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebulaPos{windowWidth, windowHeight - nebula.height/8};

    int nebulaVel{-600};

    //scarfy Texture Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = (windowWidth/2 - scarfyRec.width/2);
    scarfyPos.y = (windowHeight - scarfyRec.height);

    int animationFrame{};
    const float updateTime{1.0/12.0};
    float runningTime{};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        const float dT = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        if(scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity * dT;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
            runningTime = 0;
        }

        if (isInAir)
        {
            animationFrame = 0;
        }
        
        nebulaPos.x += nebulaVel *dT;

        scarfyPos.y += velocity * dT;
        
        runningTime += dT;
        if (runningTime >= updateTime)
        {
                runningTime = 0.0;
                scarfyRec.x = animationFrame * scarfyRec.width;
                animationFrame++;

            if(animationFrame > 5)
            {
                animationFrame = 0;
            }
        }

        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}