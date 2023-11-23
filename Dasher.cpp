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
    const int jumpVelocity{-1000};
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

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};

    SetTargetFPS(60);
    while(!WindowShouldClose()) //Window should only close when X or ESC are hit
    {
        const float dT{GetFrameTime()}; //Time between frames

        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= 200 * dT;

        if (bgX <= -background.width*6)
        {
            bgX = 0.0;
        }
        
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 6.0, WHITE);
        Vector2 bg2Pos{bgX + background.width*6, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 6.0, WHITE);

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
        //scary's vertical possible velocity is set due to delta time

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
        
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy); //properly unload scarfy texture
    UnloadTexture(nebula); //properly unload nebula texture 
    UnloadTexture(background);
    CloseWindow();
}