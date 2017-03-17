#include "spriteReader.h"
#include <stdlib.h>

#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480

void drawOnScreen(enum direction direct,struct sprite *src)
{
    switch(direct){
    case NONE:
        switch(src->direct) {
        case RIGHT :
            src->step=0;
            src->oneChar.x=4*src->oneChar.w+4*src->offsetwh;
            src->oneChar.y=src->offsettop;
            SDL_RenderClear(src->renderer);
            SDL_RenderCopy(src->renderer,src->text,&(src->oneChar),&(src->pos));
            break;
        case LEFT :
            src->step=0;
            src->oneChar.x=4*src->oneChar.w+4*src->offsetwh;
            src->oneChar.y=2*src->offsettop+src->oneChar.h;
            SDL_RenderClear(src->renderer);
            SDL_RenderCopy(src->renderer,src->text,&(src->oneChar),&(src->pos));
            break;
        case UP:
            src->step=0;
            src->oneChar.x=0;
            src->oneChar.y=2*src->offsettop+src->oneChar.h;
            SDL_RenderClear(src->renderer);
            SDL_RenderCopy(src->renderer,src->text,&(src->oneChar),&(src->pos));
            break;
        case DOWN:
            src->step=0;
            src->oneChar.x=0;
            src->oneChar.y=src->offsettop;
            SDL_RenderClear(src->renderer);
            SDL_RenderCopy(src->renderer,src->text,&(src->oneChar),&(src->pos));
            break;
        default ://in case of bug
            src->step=0;
            src->direct=RIGHT;
            src->oneChar.x=4*src->oneChar.w+4*src->offsetwh;
            src->oneChar.y=src->offsettop;
            SDL_RenderClear(src->renderer);
            SDL_RenderCopy(src->renderer,src->text,&(src->oneChar),&(src->pos));
            break;
        }
        break;
    case RIGHT :
        src->direct=RIGHT;
        src->pos.x=(src->pos.x+5);
        if(src->pos.x>SCREEN_SIZE_X)
            src->pos.x =-src->pos.w;
        src->step=(src->step+1)%4;
        src->oneChar.x=(4+src->step)*src->oneChar.w+(4+src->step)*src->offsetwh;
        src->oneChar.y=src->offsettop;
        SDL_RenderClear(src->renderer);
        SDL_RenderCopy(src->renderer,src->text,&(src->oneChar),&(src->pos));
        break;
    case LEFT:
        src->direct=LEFT;
        src->pos.x=(src->pos.x-5);
        if(src->pos.x<-src->pos.w)
            src->pos.x = SCREEN_SIZE_X;
        src->step=(src->step+1)%4;
        src->oneChar.x=(4+src->step)*src->oneChar.w+(4+src->step)*src->offsetwh;
        src->oneChar.y=2*src->offsettop+src->oneChar.h;
        SDL_RenderClear(src->renderer);
        SDL_RenderCopy(src->renderer,src->text,&(src->oneChar),&(src->pos));
        break;
    case UP:
        src->direct=UP;
        src->pos.y=(src->pos.y-5);
        if(src->pos.y<-src->pos.h)
            src->pos.y = SCREEN_SIZE_Y;
        src->step=(src->step+1)%4;
        src->oneChar.x=(src->step)*src->oneChar.w+(src->step)*src->offsetwh;
        src->oneChar.y=2*src->offsettop+src->oneChar.h;
        SDL_RenderClear(src->renderer);
        SDL_RenderCopy(src->renderer,src->text,&(src->oneChar),&(src->pos));
        break;
    case DOWN:
        src->direct=DOWN;
        src->pos.y=(src->pos.y+5);
        if(src->pos.y>SCREEN_SIZE_Y)
            src->pos.y = -src->pos.h;
        src->step=(src->step+1)%4;
        src->oneChar.x=(src->step)*src->oneChar.w+(src->step)*src->offsetwh;
        src->oneChar.y=src->offsettop;
        SDL_RenderClear(src->renderer);
        SDL_RenderCopy(src->renderer,src->text,&(src->oneChar),&(src->pos));
        break;
    default :
        break;
    }
}
struct sprite *initSprite(SDL_Texture *text,SDL_Rect sizeofchar/*important w and h*/,SDL_Rect destination_size,int offsetwh,int offsettop,SDL_Renderer *renderer) {
    struct sprite *sp =(struct sprite*)malloc(sizeof(struct sprite));
    sp->text=text;
    sp->oneChar.x=sizeofchar.x;
    sp->oneChar.y=sizeofchar.y;
    sp->oneChar.h=sizeofchar.h;
    sp->oneChar.w=sizeofchar.w;
    sp->offsettop=offsettop;
    sp->offsetwh=offsetwh;
    sp->renderer = renderer;
    sp->pos.x=destination_size.x;
    sp->pos.y=destination_size.y;
    sp->pos.h=destination_size.h;
    sp->pos.w=destination_size.w;
    return sp;
}
