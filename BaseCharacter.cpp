#include "BaseCharacter.h"

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
    screenPos.x,
    screenPos.y,
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
        //location on sprite sheet. multiply rightLeft to reverse the width of the sprite sheet. Flipping it.
        Rectangle knightSource{frame * width, 0.f, rightLeft * width, height};
        //location to draw on map
        Rectangle knightDest{screenPos.x, screenPos.y, scale * width, scale * height};
        // Vector2 is the origin used as a reference point for scaling and rotation
        DrawTexturePro(texture, knightSource, knightDest, Vector2{}, 0.f, WHITE);
}