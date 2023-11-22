#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    int windowDimension[2];
    windowDimension[0] = 2000;
    windowDimension[1] = 1000;

    InitWindow(windowDimension[0], windowDimension[1], "Sophia's Run Game");

    // scarfy jump variables
    int velocity{0};
    const int gravity{1000};
    const int jumpVelocity{-600};
    bool isInAir{};

    //nebula Texture Variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    int nebulaVel{-600};

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

    AnimData nebulae[3]{};
    for (int i = 0; i < 3; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimension[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/16.0;
    }

    nebulae[0].pos.x = windowDimension[0];
    nebulae[1].pos.x = windowDimension[1] + 300;
    nebulae[2].pos.x = windowDimension[2] + 600;

    SetTargetFPS(60);
    while(!WindowShouldClose()) //Window should only close when X or ESC are hit
    {
        const float dT = GetFrameTime(); //Time between frames

        BeginDrawing();
        ClearBackground(WHITE);

        if(scarfyData.pos.y >= windowDimension[1] - scarfyData.rec.height) //if scarfy's position on the ground
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

        if (isInAir) //animation freezes when he is in the air
        {
            scarfyData.frame = 0;
        }

        //scary's vertical possible velocity is set due to delta time
        scarfyData.pos.y += velocity * dT;
        
        //scarfy animation update
        scarfyData.runningTime += dT;

        if (scarfyData.runningTime >= scarfyData.updateTime)
        {
                scarfyData.runningTime = 0.0; // actual time
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width; // scarfy rectangle posX is animation frame * the 
                //width of each rectangle
                scarfyData.frame++; //incrimenting the animation frame animates scarfy

            if(scarfyData.frame > 5)
            {
                scarfyData.frame = 0; // there are 6 animations so it resets to the first after animation frame 5
            }
        }

        //nebula animation update
        nebulae[0].runningTime += dT;
        if (nebulae[0].runningTime >= nebulae[0].updateTime)
        {
                nebulae[0].runningTime = 0.0;
                nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
                nebulae[0].frame++;

            if(nebulae[0].frame > 7) //8 total frames for the animation
            {
                nebulae[0].frame = 0;
            }
        }

        //nebula horizontal velocity is set with delta time
        nebulae[0].pos.x += nebulaVel *dT;

        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        //DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, WHITE);
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy); //properly unload scarfy texture
    UnloadTexture(nebula); //properly unload nebula texture 
    CloseWindow();
}