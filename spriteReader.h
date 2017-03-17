#ifndef SPRITEREADER_H_
#define SPRITEREADER_H_
#include <SDL2/SDL.h>
#include <time.h>
enum direction {NONE,RIGHT,LEFT,UP,DOWN};
struct sprite {
    SDL_Texture *text;//full image of the sprite
    SDL_Rect oneChar;//h and w correspond to the h and w of any char and x y correspond to the position of the char on the image
    SDL_Rect pos; //position on the screen of this sprite :P
    int offsetwh;
    int offsettop;
    enum direction direct;//current direction
    int step;
    SDL_Renderer *renderer;

};
extern struct sprite *initSprite(SDL_Texture *text,SDL_Rect sizeofchar/*important w and h*/,SDL_Rect destination_size,int offsetwh,int offsettop,SDL_Renderer *renderer);
extern void drawOnScreen(enum direction direct,struct sprite *src);//none would do nothing than draw man waiting
#endif // SPRITEREADER_H_
