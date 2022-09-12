#include <iostream>
#include "Brick.hpp"
#include "Paddle.hpp"
#include "BrickWall.hpp"

using namespace std;

Brick::Brick():GameObject()
{
    BrickExist = false;
}

Brick::Brick(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h):GameObject(texturesheet, renderer, x, y, w, h)
{
    BrickExist = true;
}

Brick::~Brick(){}

void Brick::Render()
{
    SDL_RenderCopy(ObjectRend, ObjectTex, NULL, &ObjectRect);
}

Brick& Brick::operator=(Brick const& Brick)
{

    ObjectRect = Brick.ObjectRect;
    ObjectRend = Brick.ObjectRend;
    ObjectTex = Brick.ObjectTex;

    BrickExist = true;

    return *this;

}

int Brick::GetBrickX() const
{
    return ObjectRect.x;
}

int Brick::GetBrickY() const
{
    return ObjectRect.y;
}

bool Brick::GetState() const{
    return BrickExist;
}

void Brick::Destroy_Brick() 
{
    BrickExist = false;  
}






