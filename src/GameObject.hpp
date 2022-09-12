#ifndef GameObject_hpp
#define GameObject_hpp

#include <SDL.h>

class GameObject
{
    protected:
        SDL_Texture* ObjectTex;
        SDL_Rect ObjectRect;
        SDL_Renderer* ObjectRend;

    public:
        GameObject();
        GameObject(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h);
        ~GameObject();
};

#endif