#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "spriteReader.h"
#include "nothing.h"

#define SOUND_EFFECT "plasma_ar3.wav"
#define MUS_PATH "8 bit Aracde.mp3"

int main(int argc, char** argv)
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0 )
    {
        fprintf(stdout,"�chec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Cr�ation de la fen�tre */
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Ma premiere application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   640,
                                   480,
                                   SDL_WINDOW_SHOWN);

        /* Initialisation du son */
        if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 640) == -1) //Initialisation de l'API Mixer
        {
            printf("%s", Mix_GetError());
        }
        /* Cr�ation du rendu */
        SDL_Renderer *sdlRenderer = SDL_CreateRenderer(pWindow, -1, 0);
        //SDL_Renderer *renderer = SDL_CreateRenderer(pWindow, -1, 0);
        //SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_SHOWN, &pWindow, &sdlRenderer);
        SDL_SetRenderDrawBlendMode(sdlRenderer,SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 0,255);
        /* Cr�ation de texture */
        SDL_Surface *image = IMG_Load("char.bmp");
        SDL_Surface *image_part = SDL_CreateRGBSurface(0,50,50,32,0,0,0,0);
        SDL_BlitSurface(image,&(image->clip_rect),image_part,&(image_part->clip_rect));
        image->clip_rect.x=10;
        SDL_Texture *text = SDL_CreateTextureFromSurface(sdlRenderer,image_part);
        /* Mise � jour �cran */
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer,text,NULL, &(image_part->clip_rect));
        SDL_RenderPresent(sdlRenderer);
        /* Cr�ation du son */
        Mix_VolumeMusic(MIX_MAX_VOLUME/2); //Mettre le volume � la moiti�
        Mix_Music *musique; //Cr�ation d'un pointeur de type Mix_Music
        musique = Mix_LoadMUS("a.ogg"); //Chargement de la musique
        if(musique == NULL) {
            printf("impossible de charger la musique: %s\n",Mix_GetError());
        }
        Mix_PlayMusic(musique, -1);

        Mix_AllocateChannels(1024); //Allouer 32 canaux
        Mix_Volume(1, MIX_MAX_VOLUME/2); //Mettre � mi-volume le post 1
        Mix_Chunk *son;//Cr�er un pointeur pour stocker un .WAV
        Mix_Chunk *son2;
        son = Mix_LoadWAV(SOUND_EFFECT); //Charger un wav dans un pointeur
        son2 = Mix_LoadWAV("sample.wav");
        Mix_VolumeChunk(son, MIX_MAX_VOLUME/2); //Mettre un volume pour ce wav
        Mix_PlayChannel(1, son, -1);
        SDL_Delay(10);
        Mix_VolumeChunk(son2, MIX_MAX_VOLUME);
        Mix_PlayChannel(1, son2, 2);
        for(int i=1;i<=1024;i++)
            Mix_PlayChannel(i, son, 2);
        Mix_VolumeMusic(MIX_MAX_VOLUME/10);
        if(!pWindow)
        {
            printf("Error Create window!!!\n");
            return -1;
        }
        int continuer;
        SDL_Event event;


        SDL_Surface *mario_sprite = SDL_LoadBMP("char.bmp");
        SDL_SetColorKey(mario_sprite,SDL_TRUE,SDL_MapRGB(mario_sprite->format, 255, 255, 255));
        SDL_Surface *mario_movement =SDL_CreateRGBSurface(0,20,40,32,0,0,0,0);
        mario_sprite->clip_rect.x=5;
        mario_sprite->clip_rect.y=20;
        SDL_BlitSurface(mario_sprite,&(mario_sprite->clip_rect),mario_movement,&(mario_movement->clip_rect));
        SDL_Texture *mario_text=SDL_CreateTextureFromSurface(sdlRenderer,mario_sprite);
        //SDL_SetTextureAlphaMod(mario_text,0x00);
        SDL_RenderClear(sdlRenderer);
        SDL_SetRenderDrawColor(sdlRenderer, 255, 255,0,255);
        SDL_RenderCopy(sdlRenderer,mario_text,NULL, &(mario_movement->clip_rect));
        SDL_RenderPresent(sdlRenderer);
        /* Mise � jour �cran */
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer,text,NULL, &(image_part->clip_rect));
        SDL_RenderPresent(sdlRenderer);
        SDL_Rect mdr = {50,50,60,82};
        struct sprite* sp = initSprite(mario_text,(SDL_Rect){0,0,30,42},(SDL_Rect){50,50,60,82},2,22,sdlRenderer);
        SDL_TimerID timer;
        timer = SDL_AddTimer(100,updatePosition,(void*)sp);
        while(continuer)
        {
            //SDL_Delay(30);
            SDL_WaitEvent(&event);
            switch(event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                SDL_DestroyWindow(pWindow);
                Mix_CloseAudio();
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                case SDLK_q:
                    direct = LEFT;
                    break;
                case SDLK_s:
                    direct = DOWN;
                    break;
                case SDLK_d:
                    direct = RIGHT;
                    break;
                case SDLK_z:
                    direct = UP;
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym) {
                    case SDLK_q:
                    if(direct==LEFT)
                        direct=NONE;
                    break;
                case SDLK_s:
                    if(direct==DOWN)
                        direct=NONE;
                    break;
                case SDLK_d:
                    if(direct==RIGHT)
                        direct=NONE;
                    break;
                case SDLK_z:
                    if(direct==UP)
                        direct=NONE;
                    break;
                default:
                    break;
                }
            default :
                break;
            }
        }
    }

    SDL_Quit();

    return 0;
}
