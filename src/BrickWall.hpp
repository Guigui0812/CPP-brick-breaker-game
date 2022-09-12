#ifndef BrickWall_hpp
#define BrickWall_hpp

#include "Brick.hpp"

class BrickWall
{
    private:
    Brick *Brick_Wall;
    int NbBrick;
    int NbBrickDestroyed;

    public:
        BrickWall(SDL_Renderer* renderer);
        ~BrickWall();
        void BrickCollision(int i);
        void Render();
        Brick* GetBrick_Wall() const;
        int GetNbBrick()const;
        int NbGetBrickDestroyed() const;
}; 

#endif