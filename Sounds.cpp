#include "Sounds.h"

Sounds::Sounds() {
    _init();
    _loadSounds();

}

void Sounds::_init() {
    if( SDL_Init( SDL_INIT_AUDIO ) < 0 ) {
        throw SDLException("SDL could not initialize! SDL Error: %s\n",
                SDL_GetError() );
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2,
                                                2048 ) < 0 ){
        throw SDLException("SDL_mixer could not initialize!"
                           " SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void Sounds::_loadSounds() {
    gMusic = Mix_LoadMUS( "../Sounds/beat.wav" );//Carga la musica
    if( gMusic == NULL ) {
        throw SDLException("Failed to load beat music! SDL_mixer Error: "
                           "%s\n", Mix_GetError());
    }

    //Load sound effects
    gScratch = Mix_LoadWAV( "../Sounds/scratch.wav" );
    if( gScratch == NULL )
    {
        throw SDLException("Failed to load scratch sound effect! SDL_mixer "
                           "Error: %s\n",Mix_GetError() );
    }

    gHigh = Mix_LoadWAV( "../Sounds/high.wav" );
    if( gHigh == NULL )
    {
        throw SDLException("Failed to load high sound effect! SDL_mixer "
                           "Error: %s\n",Mix_GetError() );

    }

    gMedium = Mix_LoadWAV( "../Sounds/medium.wav" );
    if( gMedium == NULL )
    {
        throw SDLException("Failed to load medium sound effect! SDL_mixer "
                           "Error: %s\n",Mix_GetError() );

    }

    gLow = Mix_LoadWAV( "../Sounds/low.wav" );
    if( gLow == NULL )
    {
        throw SDLException("Failed to load low sound effect! SDL_mixer "
                           "Error: %s\n",Mix_GetError() );

    }
}

void Sounds::playScratchSound() {
    Mix_PlayChannel( -1, gScratch, 0 );
}

void Sounds::playHighSound() {
    Mix_PlayChannel( -1, gHigh, 0 );
}

void Sounds::playMediumSound() {
    Mix_PlayChannel( -1, gMedium, 0 );
}

void Sounds::playLowSound() {
    Mix_PlayChannel( -1, gLow, 0 );
}

void Sounds::playMusic() {
    if( Mix_PlayingMusic() == 0 ) {//Empieza musica si no habia
        Mix_PlayMusic(gMusic, -1);
    } else if (Mix_PausedMusic() == 1) {//Resume musica si estaba en pausa
        Mix_ResumeMusic();
    }
}

void Sounds::pauseMusic() {
    Mix_PauseMusic();
}

void Sounds::stopMusic(){
    Mix_HaltMusic();
}

Sounds::~Sounds() {
    //Libera los sonidos
    Mix_FreeChunk( gScratch );
    Mix_FreeChunk( gHigh );
    Mix_FreeChunk( gMedium );
    Mix_FreeChunk( gLow );
    Mix_FreeMusic( gMusic );

    //Cierra las cosas de SDL, esto probablemente haya que hacerlo en la clase
    //que maneje los graficos/sonidos
    Mix_Quit();
    SDL_Quit();
}
