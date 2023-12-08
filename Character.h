#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{   
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    Vector2 getScreenPos(){ return screenPos; };
    virtual Vector2 getScreenPos() override;
private:
    
};

#endif 