#include "spriteReader.h"
void drawOnScreen(SDL_Renderer *renderer,enum direction direct,SDL_Rect pos,struct sprite *src)
{
    switch(direct){
    case NONE:
        switch(src->direct) {
        case RIGHT :
            src->step=0;
            src->oneChar.x=4*src->oneChar.w+4*src->offsetwh;
            src->oneChar.y=src->offsettop;
            SDL_RenderClear(sdlRenderer);
            SDL_RenderCopy(sdlRenderer,src->text,&(src->oneChar),&pos);
            break;
        case LEFT :
            src->step=0;
            src->oneChar.x=4*src->oneChar.w+4*src->offsetwh;
            src->oneChar.y=src->2*offsettop+src->oneChar.h;
            SDL_RenderClear(sdlRenderer);
            SDL_RenderCopy(sdlRenderer,src->text,&(src->oneChar),&pos);
            break;
        case UP:
            src->step=0;
            src->oneChar.x=0;
            src->oneChar.y=src->2*offsettop+src->oneChar.h;
            SDL_RenderClear(sdlRenderer);
            SDL_RenderCopy(sdlRenderer,src->text,&(src->oneChar),&pos);
            break;
        case DOWN:
            src->step=0;
            src->oneChar.x=0;
            src->oneChar.y=src->offsettop;
            SDL_RenderClear(sdlRenderer);
            SDL_RenderCopy(sdlRenderer,src->text,&(src->oneChar),&pos);
        default ://in case of bug
            src->step=0;
            src->direct=RIGHT;
            src->oneChar.x=4*src->oneChar.w+4*src->offsetwh;
            src->oneChar.y=src->offsettop;
            SDL_RenderClear(sdlRenderer);
            SDL_RenderCopy(sdlRenderer,src->text,&(src->oneChar),&pos);
            break;
        }
        break;
    case RIGHT :
        src->step=(src->step+1)%4;
        src->oneChar.x=(4+src->step)*src->oneChar.w+(4+src->step)*src->offsetwh;
        src->oneChar.y=src->offsettop;
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer,src->text,&(src->oneChar),&pos);
        break;
    case LEFT:
        src->step=(src->step+1)%4;
        src->oneChar.x=(4+src->step)*src->oneChar.w+(4+src->step)*src->offsetwh;
        src->oneChar.y=src->2*offsettop+src->oneChar.h;
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer,src->text,&(src->oneChar),&pos);
        break;
    case UP:
        src->step=(src->step+1)%4;
        src->oneChar.x=(src->step)*src->oneChar.w+(src->step)*src->offsetwh;
        src->oneChar.y=src->2*offsettop+src->oneChar.h;
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer,src->text,&(src->oneChar),&pos);
        break;
    case DOWN:
        src->step=(src->step+1)%4;
        src->oneChar.x=(src->step)*src->oneChar.w+(src->step)*src->offsetwh;
        src->oneChar.y=src->offsettop;
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer,src->text,&(src->oneChar),&pos);
        break;
    default :
        break;
    }
}
