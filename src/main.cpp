#include <iostream>
#include <SDL.h>

#include "Paddle.hpp"
#include "Ball.hpp"
#include "BrickWall.hpp"
#include "Constants.hpp"
#include "Score.hpp"

using namespace std;

void update(Paddle &Pad, Ball &Ball, BrickWall &Wall, Score &Points)
{
    Ball.BallMove(Pad, Wall);
    Points.UpdateScore(Wall.NbGetBrickDestroyed());
}
       
void events(SDL_bool *program_launched, Paddle &Pad, Ball &Ball, BrickWall &Wall) // Passage par réf a cause du tableau.
{
    SDL_Event Event;

    while(SDL_PollEvent(&Event))
    {
        switch(Event.type)
        {
            case SDL_KEYDOWN:   
                switch(Event.key.keysym.sym)
                {
                    case SDLK_q:

                        Pad.MoveLeft();
                        continue;

                    case SDLK_d:

                        Pad.MoveRight();         
                        continue;

                    case SDLK_SPACE:

                        Ball.BallUnlock();
                        continue;

                    default:
                        continue;
                }

            case SDL_QUIT:
                *program_launched = SDL_FALSE;
                break;

            default:
                break;
        }
    }
    if (Ball.GetBotTouching() == 4)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"DEFAITE", "Vous avez perdu !", NULL);
        *program_launched = SDL_FALSE;
    }

    if (Wall.NbGetBrickDestroyed() == Wall.GetNbBrick())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"VICTOIRE", "Vous avez gagné !", NULL);
        *program_launched = SDL_FALSE;
    }
}
      
void render(SDL_Renderer *renderer, Paddle Paddle, Ball Ball, BrickWall &BrickWall, Score Points) 
{
    SDL_RenderClear(renderer);

    Paddle.Render();
    Ball.Render();
    BrickWall.Render();
    Points.Render();

    SDL_RenderPresent(renderer);
}

int main (int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    int frameStart, frameTime;
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0){
        SDL_Log("ERREUR : Creation de la fenetre et du rendu echouee > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetWindowTitle(window, "Casse Brique");

    if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0){
        SDL_Log("ERREUR : Modification couleur du rendu echouee > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(TTF_Init() != 0)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    Paddle Pad("Paddle.bmp", renderer, PaddleX, PaddleY, PaddleW, PaddleH);
    Ball Ball("Balle.bmp", renderer, (PaddleX / 2) - (BallDim / 2), (PaddleY - BallDim), BallDim, BallDim);
    BrickWall Wall(renderer);
    Score Points(renderer);

    SDL_bool program_launched = SDL_TRUE;

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Commandes", "Commandes : q pour aller à gauche, d pour aller à droite, espace pour relâcher la balle ! Vous avez 3 vies. Bonne chance !", NULL);

    while (program_launched)
    {  
        frameStart = SDL_GetTicks();
        
        events(&program_launched, Pad, Ball, Wall);
        update(Pad, Ball, Wall, Points);
        render(renderer, Pad, Ball, Wall, Points);

        frameTime = SDL_GetTicks() - frameStart;

        //Limite la vitesse de jeu à 60 images secondes.
        
        if (frameDelay > frameTime)
        {
            SDL_Delay(6);
        }

    }

    // Sortie de la SDL : 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
