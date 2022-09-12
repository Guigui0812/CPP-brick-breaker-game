#ifndef Ball_hpp
#define Ball_hpp

#include <vector>
#include <cmath>
#include "GameObject.hpp"
#include "BrickWall.hpp"
#include "Paddle.hpp"
#include "Constants.hpp"

class Ball:public GameObject
{
    private:
        bool BallLock, collisionV, collisionH;
        int BotTouching;
        std::vector <SDL_Rect> CollisionBox;
        SDL_Rect UpdateBox(int x, int y, int w, int h);
        void BoxMoving();
        void BallLockMove(int PadPosX);
        void ScreenCollisions();
        void PaddleCollisions(int PadPosX);
        void Ball_Wall_Collision(BrickWall &Wall);
        void BallVel();

    public:
        Ball(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h);
        ~Ball();
        void BallMove(Paddle, BrickWall &Wall);
        void BallUnlock();
        void Render();
        int GetBotTouching() const;
};

#endif