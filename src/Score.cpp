#include <iostream>
#include "Score.hpp"

Score::Score(SDL_Renderer* renderer)
{
    
    TextRend = renderer;

    Lato = TTF_OpenFont("Lato-Light.ttf", 12);

    Purple = {138,43,226};

    SDL_Surface *textSurface = TTF_RenderText_Solid(Lato, "Score : ", Purple);

    Text = SDL_CreateTextureFromSurface(TextRend, textSurface);

    SDL_FreeSurface(textSurface);

    TextRect.x = 0;
    TextRect.y = 560;
    TextRect.w = 100;
    TextRect.h = 40;
}

Score::~Score()
{

}

void Score::UpdateScore(int BrickBreak)
{
    std::string Points = std::to_string(BrickBreak);
    int len = Points.size();

    char *Pointschar = new char[len + 1];
    std::copy(Points.begin(), Points.end(), Pointschar);
    Pointschar[len] = '\0';


    ScoreSurface = TTF_RenderText_Solid(Lato, Pointschar, Purple);

    delete(Pointschar);

    ScoreText = SDL_CreateTextureFromSurface(TextRend, ScoreSurface);

    SDL_FreeSurface(ScoreSurface);

    ScoreRect.x = 100;
    ScoreRect.y = 560;
    ScoreRect.w = 20;
    ScoreRect.h = 40;

}

void Score::Render()
{
    SDL_RenderCopy(TextRend, ScoreText, NULL, &ScoreRect);
    SDL_RenderCopy(TextRend, Text, NULL, &TextRect);
}