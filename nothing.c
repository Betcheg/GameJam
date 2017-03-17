#include "nothing.h"
#include "spriteReader.h"
enum direction direct=NONE;
SDL_Rect charPos;
Uint32 updatePosition(Uint32 callback,void* parameter) {
    struct sprite* sp = (struct sprite*)parameter;
    SDL_SetRenderDrawColor(sp->renderer, 255, 255, 0,255);
    drawOnScreen(direct,sp);
    SDL_RenderPresent(sp->renderer);
    return callback;
}
