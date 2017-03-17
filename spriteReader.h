#ifndef SPRITEREADER_H_
#define SPRITEREADER_H_
#include <SDL2/SDL.h>
#include <time.h>
enum direction {NONE,RIGHT,LEFT,UP,DOWN};
struct sprite {
    SDL_Texture *text;//full image of the sprite
    SDL_Rect oneChar;//h and w correspond to the h and w of any char and x y correspond to the position of the char on the image
    int offsetwh;
    int offsettop;
    enum direction direct;//current direction
    int step;

};
void initSprite();
void drawOnScreen(SDL_Renderer *renderer,enum direction direct,SDL_Rect pos,struct sprite *src);//none would do nothing than draw man waiting
#endif // SPRITEREADER_H_
