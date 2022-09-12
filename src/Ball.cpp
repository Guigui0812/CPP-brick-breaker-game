#include <iostream>
#include "Ball.hpp"

using namespace std;

Ball::Ball(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h):GameObject(texturesheet, renderer, x, y, w, h)
{
    BallLock = true;
    BotTouching = 0;

    CollisionBox.push_back(UpdateBox(ObjectRect.x + 6, ObjectRect.y, 12, 2)); 
    CollisionBox.push_back(UpdateBox(ObjectRect.x + 3, ObjectRect.y + 3, 18, 2));
    CollisionBox.push_back(UpdateBox(ObjectRect.x + 1, ObjectRect.y + 6, 22, 2));
    CollisionBox.push_back(UpdateBox(ObjectRect.x + 1, (ObjectRect.y + BallDim - 7), 22, 2));
    CollisionBox.push_back(UpdateBox(ObjectRect.x + 3, (ObjectRect.y + BallDim - 4), 18, 2));
    CollisionBox.push_back(UpdateBox(ObjectRect.x + 6, (ObjectRect.y + BallDim - 1), 12, 2)); 
}

Ball::~Ball(){}

SDL_Rect Ball::UpdateBox(int x, int y, int w, int h)
{
    SDL_Rect Box;
    Box.x = x;
    Box.y = y;
    Box.w = w;
    Box.h = h;

    return Box;
}

void Ball::BoxMoving()
{
    CollisionBox.clear();
    CollisionBox.push_back(UpdateBox(ObjectRect.x + 6, ObjectRect.y, 12, 2)); 
    CollisionBox.push_back(UpdateBox(ObjectRect.x + 3, ObjectRect.y + 3, 18, 2));
    CollisionBox.push_back(UpdateBox(ObjectRect.x + 1, ObjectRect.y + 6, 22, 2));
    CollisionBox.push_back(UpdateBox(ObjectRect.x + 1, (ObjectRect.y + BallDim - 7), 22, 2));
    CollisionBox.push_back(UpdateBox(ObjectRect.x + 3, (ObjectRect.y + BallDim - 4), 18, 2));
    CollisionBox.push_back(UpdateBox(ObjectRect.x + 6, (ObjectRect.y + BallDim - 1), 12, 2)); 
}

void Ball::Render()
{
    SDL_RenderCopy(ObjectRend, ObjectTex, NULL, &ObjectRect);
}

void Ball::Ball_Wall_Collision(BrickWall &Wall)
{
    bool CheckCollision = false, CheckBrickExistense;
    int tmp_x, tmp_y, tmp_i = 0;
    Brick *ArrayBrick_tmp = Wall.GetBrick_Wall();

    for (int i = 0; i < Wall.GetNbBrick(); i++)
    {
        CheckBrickExistense = ArrayBrick_tmp[i].GetState();

        if (CheckBrickExistense == true)
        {
            tmp_x = ArrayBrick_tmp[i].GetBrickX();
            tmp_y = ArrayBrick_tmp[i].GetBrickY();
        

            //Collision bas de la brique : 
            if (((CollisionBox[0].x + CollisionBox[0].w) >= tmp_x) && ((CollisionBox[0].x + CollisionBox[0].w) <= (tmp_x + BrickW)) && (CollisionBox[0].y == (tmp_y + BrickH)))
            {
                Wall.BrickCollision(i);
                collisionV = false;
            }

            //Collision haut de la brique : Pas de gestion des coins car situation peu présente, donc code peu sollicité.
            else if ((ObjectRect.x >= tmp_x) && (ObjectRect.x <= (tmp_x + BrickW)) && ((ObjectRect.y + BallDim) == tmp_y))
            {
                Wall.BrickCollision(i);
                collisionV = true;
            }

            // Collision coins bas gauche brique : Pas de rebond opposé car trop frustrant. 

            else if (((CollisionBox[1].x + CollisionBox[1].w) >= tmp_x) && ((CollisionBox[1].x + CollisionBox[1].w) <= (tmp_x + BrickW + CollisionBox[1].w)) && ((CollisionBox[1].y == tmp_y + BrickH)))  
            {
                Wall.BrickCollision(i);
                collisionV = false;
            }

            else if (((CollisionBox[2].x + CollisionBox[3].w) >= tmp_x) && ((CollisionBox[2].x + CollisionBox[2].w) <= (tmp_x + BrickW)) && ((CollisionBox[2].y == tmp_y + BrickH)))  
            {
                Wall.BrickCollision(i);
                collisionV = false;
            }

            // Collision coins bas droit brique : 
            else if (((CollisionBox[1].x <= tmp_x + BrickW) && (CollisionBox[1].x > tmp_x)) && ((CollisionBox[1].y == tmp_y + BrickH)) )  
            {
                Wall.BrickCollision(i);
                collisionV = true;
            }

            else if (((CollisionBox[2].x <= tmp_x + BrickW) && (CollisionBox[2].x > tmp_x)) && ((CollisionBox[2].y == tmp_y + BrickH)) )  
            {
                Wall.BrickCollision(i);
                collisionV = true;
            }

            // Collision droite de la brique : 
            else if ((ObjectRect.x == tmp_x + BrickW) && ((ObjectRect.y >= tmp_y) && (ObjectRect.y <= tmp_y + BrickH)))
            {
                Wall.BrickCollision(i);
                collisionH = false;
            }

            //Collision gauche de la brique : 
            else if ((ObjectRect.x + BallDim == tmp_x) && ((ObjectRect.y >= tmp_y) && (ObjectRect.y <= tmp_y + BrickH)))
            {
                Wall.BrickCollision(i);
                collisionH = true;
            }

        }
    }
}

void Ball::BallLockMove(int PadPosX)
{

    ObjectRect.x = PadPosX + 34;

}

void Ball::BallUnlock()
{
    if (BallLock == true)
    {
        BallLock = false;
        collisionV = true;
        collisionH =  true;
    }
}

void Ball::ScreenCollisions()
{
    //Collisions verticales :
    if (ObjectRect.y == 0)
    {
        collisionV = false;
    }
    else if (ObjectRect.y == (WINDOW_HEIGHT - BallDim))
    {
        collisionV = true;
        BotTouching++;
    } 

    //Collisions horizontales : 
    if (ObjectRect.x == 0)
    {
        collisionH = false;
    }    
    else if (ObjectRect.x == (WINDOW_WIDTH - BallDim))
    {
        collisionH = true;
    } 

}

void Ball::BallVel()
{
    if (collisionH == true) //Gère la direction.
    {
        ObjectRect.x--;
    }
    else
    {
        ObjectRect.x++;
    }  

    if (collisionV == true) //Gère la direction.
    {
        ObjectRect.y--;
    }
    else 
    {
        ObjectRect.y++;
    }  
}

void Ball::PaddleCollisions(int PadPosX)
{

    //Collision basique horizontale basique :
    if (((CollisionBox[5].x + CollisionBox[5].w) >= PadPosX) && (CollisionBox[5].x <= (PadPosX + PaddleW)) && ((CollisionBox[5].y + CollisionBox[5].h) == PaddleY))
    {
       collisionV = true;
    } 

    // Collision simplifiée en bas car jugé trop frustrant si la collision était mise en place avec les boîtes.
    if ((ObjectRect.x + ObjectRect.w >= PadPosX) && (ObjectRect.x <= (PadPosX + PaddleW)) && ObjectRect.y == (PaddleY + PaddleH))
    {
        collisionV = false;
    } 

    //Collision sur le côté gauche :
    if(((ObjectRect.x + BallDim) == PadPosX) && (((ObjectRect.y + BallDim) >= PaddleY) && ((ObjectRect.y + BallDim/2) <= PaddleY + PaddleH)))
    {
        collisionH =  true;
    }

    //Collision sur le côté droit : 
    if((ObjectRect.x == (PadPosX + PaddleW)) && (((ObjectRect.y + (BallDim / 2)) >= PaddleY) && ((ObjectRect.y + BallDim/2) <= PaddleY + PaddleH)))
    {
        collisionH =  false;
    }

    //Collisions coin haut gauche :
    if (((CollisionBox[4].x + CollisionBox[4].w) >= PadPosX) && ((CollisionBox[4].x + CollisionBox[4].w) <= (PadPosX + PaddleW + CollisionBox[4].w)) && ((CollisionBox[4].y + CollisionBox[4].h) == PaddleY) )  
    {
        collisionH =  true;
        collisionV = true;
    }

    if (((CollisionBox[3].x + CollisionBox[3].w) >= PadPosX) && ((CollisionBox[3].x + CollisionBox[3].w) <= (PadPosX + PaddleW)) && ((CollisionBox[3].y + CollisionBox[3].h) == PaddleY) )  
    {
        collisionH =  true;
        collisionV = true;
    }

    //Collisions coin haut droit : 
    if (((CollisionBox[4].x <= PadPosX + PaddleW) && (CollisionBox[4].x > PadPosX)) && ((CollisionBox[4].y + CollisionBox[4].h) == PaddleY) )  
    {
        collisionH =  false;
        collisionV = true;
    }

    if (((CollisionBox[3].x <= PadPosX + PaddleW) && (CollisionBox[3].x > PadPosX)) && ((CollisionBox[3].y + CollisionBox[3].h) == PaddleY) )  
    {
        collisionH =  false;
        collisionV = true;
    }
}

void Ball::BallMove(Paddle Pad, BrickWall &Wall)
{
    int PadPosX = Pad.getX();

    if (BallLock == true)
    {
        BallLockMove(PadPosX);
    }

    else
    {
        PaddleCollisions(PadPosX);
        ScreenCollisions();
        Ball_Wall_Collision(Wall);
        BallVel();
        BoxMoving();
    }
}

int Ball::GetBotTouching() const
{
    return BotTouching;
}