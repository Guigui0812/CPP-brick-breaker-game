#ifndef Brick_hpp
#define Brick_hpp


#include "GameObject.hpp"
#include "Constants.hpp"

class Brick:public GameObject
{
    protected:
        bool BrickExist; 

    public:
        Brick();
        Brick(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h);
        ~Brick();
        Brick& operator=(Brick const &Brick);
        void Render();
        int GetBrickX() const;
        int GetBrickY() const;
        bool GetState() const;
        void Destroy_Brick();
};
#endif