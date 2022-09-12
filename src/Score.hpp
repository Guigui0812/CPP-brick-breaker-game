#ifndef Score_hpp
#define Score_hpp

#include <SDL.h>
#include <SDL_ttf.h>

class Score
{
    private:
        SDL_Texture* Text;
        SDL_Texture* ScoreText;
        TTF_Font* Lato;
        SDL_Color Purple;
        SDL_Rect TextRect;
        SDL_Renderer* TextRend;
        SDL_Rect ScoreRect;
        SDL_Surface *ScoreSurface;
        int life;
        int points;

    public:
        Score(SDL_Renderer* renderer);
        ~Score();
        void UpdateScore(int BrickBreak);
        void Render();

};

#endif