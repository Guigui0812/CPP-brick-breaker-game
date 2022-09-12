#ifndef Paddle_hpp
#define Paddle_hpp

#include "GameObject.hpp"
#include "Constants.hpp"

class Paddle:public GameObject
{
    public:
        void MoveRight();
        void MoveLeft();
        void Render();
        Paddle(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h);
        ~Paddle();
        int getX() const;

};

#endif