#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}
void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
    getScreenPos().x,
    getScreenPos().y,
    width * scale,
    height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    //get the delta time
        runningTime += deltaTime;
        //iterate through frames overtime
        if(runningTime >= updateTime)
        {
            frame++;
            runningTime = 0;
            if (frame > maxFrames) frame = 0;
        }
        
        if (Vector2Length(velocity) != 0.0)
        {    
            worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
            velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            texture = run;
        }
        else
        {
            texture = idle;
        }
        velocity = {};

        //location on sprite sheet. multiply rightLeft to reverse the width of the sprite sheet. Flipping it.
        Rectangle knightSource{frame * width, 0.f, rightLeft * width, height};
        //location to draw on map
        Rectangle knightDest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
        // Vector2 is the origin used sdas a reference point for scaling and rotation
        DrawTexturePro(texture, knightSource, knightDest, Vector2{}, 0.f, WHITE);
}