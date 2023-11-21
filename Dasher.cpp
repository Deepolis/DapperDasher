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
    //window creation
    const int windowWidth{2000};
    const int windowHeight{1000};
    InitWindow(windowWidth, windowHeight, "Sophia's Run Game");

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
        {0.0, 0.0, scarfy.width/6, scarfy.height}, // Rectangle initialize
        {windowWidth/2 - scarfyData.rec.width, windowHeight - scarfyData.rec.height}, // Rectangle position offset by 300
        0, // int nebAnimationFrame
        1.0/12.0, // float nebUpdateTime
        0.0  // int nebRunningTime
    };

    //AnimData for nebula
    AnimData nebData
    {
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle initialize
        {windowWidth, windowHeight - nebula.height/8}, // Rectangle position offset by 300
        0, // int nebAnimationFrame
        1.0/12.0, // float nebUpdateTime
        0  // int nebRunningTime
    };

    //AnimData for nebula2
    AnimData neb2Data
    {
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle initialize
        {windowWidth + 800, windowHeight - nebula.height/8}, // Rectangle position
        0, // int neb2AnimationFrame
        1.0/16.0, // float neb2UpdateTime
        0  // int neb2RunningTime
    };

    SetTargetFPS(60);
    while(!WindowShouldClose()) //Window should only close when X or ESC are hit
    {
        const float dT = GetFrameTime(); //Time between frames

        BeginDrawing();
        ClearBackground(WHITE);

        if(scarfyData.pos.y >= windowHeight - scarfyData.rec.height) //if scarfy's position on the ground
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
        nebData.runningTime += dT;
        if (nebData.runningTime >= nebData.updateTime)
        {
                nebData.runningTime = 0.0;
                nebData.rec.x = nebData.frame * nebData.rec.width;
                nebData.frame++;

            if(nebData.frame > 7) //8 total frames for the animation
            {
                nebData.frame = 0;
            }
        }

        //nebula horizontal velocity is set with delta time
        nebData.pos.x += nebulaVel *dT;
        nebData.pos.x += nebulaVel *dT;

        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        //DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, WHITE);
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy); //properly unload scarfy texture
    UnloadTexture(nebula); //properly unload nebula texture 
    CloseWindow();
}