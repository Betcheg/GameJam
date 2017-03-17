#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#define SOUND_EFFECT "plasma_ar3.wav"
#define MUS_PATH "8 bit Aracde.mp3"

int main(int argc, char** argv)
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Création de la fenêtre */
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
        /* Création du rendu */
        SDL_Renderer *sdlRenderer = SDL_CreateRenderer(pWindow, -1, 0);
        //SDL_Renderer *renderer = SDL_CreateRenderer(pWindow, -1, 0);
        //SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_SHOWN, &pWindow, &sdlRenderer);
        SDL_SetRenderDrawBlendMode(sdlRenderer,SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 0,255);
        /* Création de texture */
        SDL_Surface *image = IMG_Load("char.bmp");
        SDL_Surface *image_part = SDL_CreateRGBSurface(0,50,50,32,0,0,0,0);
        SDL_BlitSurface(image,&(image->clip_rect),image_part,&(image_part->clip_rect));
        image->clip_rect.x=10;
        SDL_Texture *text = SDL_CreateTextureFromSurface(sdlRenderer,image_part);
        /* Mise à jour écran */
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer,text,NULL, &(image_part->clip_rect));
        SDL_RenderPresent(sdlRenderer);
        /* Création du son */
        Mix_VolumeMusic(MIX_MAX_VOLUME/2); //Mettre le volume à la moitié
        Mix_Music *musique; //Création d'un pointeur de type Mix_Music
        musique = Mix_LoadMUS("a.ogg"); //Chargement de la musique
        if(musique == NULL) {
            printf("impossible de charger la musique: %s\n",Mix_GetError());
        }
        Mix_PlayMusic(musique, -1);

        Mix_AllocateChannels(1024); //Allouer 32 canaux
        Mix_Volume(1, MIX_MAX_VOLUME/2); //Mettre à mi-volume le post 1
        Mix_Chunk *son;//Créer un pointeur pour stocker un .WAV
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
        SDL_Surface *mario_movement =SDL_CreateRGBSurface(0,20,40,32,0,0,0,0);
        mario_sprite->clip_rect.x=5;
        mario_sprite->clip_rect.y=20;
        SDL_BlitSurface(mario_sprite,&(mario_sprite->clip_rect),mario_movement,&(mario_movement->clip_rect));
        SDL_Texture *mario_text=SDL_CreateTextureFromSurface(sdlRenderer,mario_sprite);
        SDL_RenderClear(sdlRenderer);
        SDL_SetRenderDrawColor(sdlRenderer, 255, 255,0,255);
        SDL_RenderCopy(sdlRenderer,mario_text,NULL, &(mario_movement->clip_rect));
        SDL_RenderPresent(sdlRenderer);
        /* Mise à jour écran */
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer,text,NULL, &(image_part->clip_rect));
        SDL_RenderPresent(sdlRenderer);
        SDL_Rect essai={41,30,0,20};
        essai.h=41;
        essai.w=30;
        essai.x=0;
        essai.y=20;
        SDL_Rect mdr = {50,50,60,82};

        int i=0;
        while(continuer)
        {
            SDL_PollEvent(&event);
            switch(event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                SDL_DestroyWindow(pWindow);
                Mix_CloseAudio();
                break;
            case SDL_KEYDOWN:
                mdr.x=(mdr.x+3)%640;
                SDL_RenderClear(sdlRenderer);
                SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 0,255);
                SDL_RenderClear(sdlRenderer);
                SDL_RenderCopy(sdlRenderer,mario_text,&essai,&(mdr));
                SDL_RenderPresent(sdlRenderer);
            default :
                break;
            }
        }
    }

    SDL_Quit();

    return 0;
}
