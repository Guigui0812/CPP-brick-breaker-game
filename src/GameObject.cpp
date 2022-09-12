#include <iostream>
#include "GameObject.hpp"

using namespace std;

GameObject::GameObject(){}

GameObject::GameObject(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h)
{

    ObjectRend = renderer;
    ObjectRect.w = w;
    ObjectRect.x = x;
    ObjectRect.y = y;
    ObjectRect.h = h;

    SDL_Surface *tmpSurface = SDL_LoadBMP(texturesheet); 

    if (tmpSurface == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_Log("ERREUR : Echec chargement balle > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    ObjectTex = SDL_CreateTextureFromSurface(ObjectRend, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    if (ObjectTex == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_Log("ERREUR : Echec création texture Paddle > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(SDL_QueryTexture(ObjectTex, NULL, NULL, &ObjectRect.w, &ObjectRect.h) != 0 )
    {
        SDL_DestroyRenderer(ObjectRend);
        SDL_Log("ERREUR : Echec création rectangle balle > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

}

GameObject::~GameObject(){}