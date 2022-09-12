#include <iostream>
#include "BrickWall.hpp"
#include <cstdlib>
#include <time.h>

using namespace std;

BrickWall::BrickWall(SDL_Renderer* renderer)
{
    int Brick_PosX = 0, Brick_PosY = 0, ii = 0, random;
    Brick_Wall = new Brick[NbBrickPerLine*NbLines];
    
    int yo = NbBrickPerLine*NbLines;

    NbBrickDestroyed = 0;

    srand(time(0));

    for (int i = 0; i < NbLines; i++)
    {
        for (int j = 0; j < NbBrickPerLine; j++)
        {
            random = rand()%(3-1) +1 ; 

            if (random == 1)
            {
                Brick_Wall[ii] = Brick ("BriqueVerte.bmp", renderer, Brick_PosX, Brick_PosY, BrickW, BrickH);

            }
            else
            {
                Brick_Wall[ii] = Brick ("BriqueJaune.bmp", renderer, Brick_PosX, Brick_PosY, BrickW, BrickH);
            }
            
            Brick_PosX = Brick_PosX + BrickW;
            ii++;
        }
        Brick_PosX = 0;
        Brick_PosY = Brick_PosY + BrickH; 
    }

    NbBrick = ii;
}

void BrickWall::Render()
{
    for (int i = 0; i < NbBrick; i++) 
    {
        if (Brick_Wall[i].GetState() == true)
            Brick_Wall[i].Render();
    }
}

BrickWall::~BrickWall()
{
    delete(Brick_Wall);
}

Brick* BrickWall::GetBrick_Wall() const
{
    return Brick_Wall;
}

void BrickWall::BrickCollision(int i)
{
    Brick_Wall[i].Destroy_Brick();
    NbBrickDestroyed++;
}

int BrickWall::GetNbBrick() const
{
    return NbBrick;
}
int BrickWall::NbGetBrickDestroyed() const
{
    return NbBrickDestroyed;
}