#include <iostream>
#include "Paddle.hpp"

using namespace std;

Paddle::Paddle(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h):GameObject(texturesheet, renderer, x, y, w, h){}

void Paddle::MoveRight()
{

    if (ObjectRect.x != (WINDOW_WIDTH - PaddleW))
    {
        
        for (int i = 0; i < 5; i++)
        {
            ObjectRect.x++;
        }  
    }
}

Paddle::~Paddle(){}

void Paddle::MoveLeft()
{

    if (ObjectRect.x != 0)
    {
        
        for (int i = 0; i < 5; i++)
        {
            ObjectRect.x--;
        }
    }
}

void Paddle::Render()
{
    SDL_RenderCopy(ObjectRend, ObjectTex, NULL, &ObjectRect);
}

int Paddle::getX() const
{
    return ObjectRect.x;
}







