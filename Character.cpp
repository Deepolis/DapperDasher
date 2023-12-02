#include "Character.h"
#include "raymath.h"

Character::Character()
{
    width = texture.width / maxFrames;
    height = texture.height;
}

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {(float)winWidth/2.0f - 4.0f * (0.5f * width),
                 (float)winHeight/2.0f - 4.0f * (0.5f * height)};
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
        Rectangle knightSource{frame * width/6.f, 0.f, rightLeft * width/6.f, height};
        //location to draw on map
        Rectangle knightDest{screenPos.x, screenPos.y, 4.0f * width/6.0f, 4.0f * height};
        // Vector2 is the origin used as a reference point for scaling and rotation
        DrawTexturePro(texture, knightSource, knightDest, Vector2{}, 0.f, WHITE);
}
