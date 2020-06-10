#include "Sounds.h"

#define FREQUENCY 44100
#define CHUNKSIZE 2048

Sounds::Sounds() {
    _init();
    _loadSounds();
    Mix_VolumeMusic(32);//Le bajo un poco el volumen a la musica
}

void Sounds::_init() {
    if( SDL_Init(SDL_INIT_AUDIO ) < 0 ) {//Esto iria en una clase SDL general
        throw SDLException("SDL could not initialize! SDL Error: %s\n",
                SDL_GetError() );
    }
    if( Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, 2,
                                                CHUNKSIZE) < 0 ){
        throw SDLException("SDL_mixer could not initialize!"
                           " SDL_mixer Error: %s\n", Mix_GetError());
    }
}

//Carga el sonido con el archivo en path
void Sounds::_loadSoundFile(Mix_Chunk** sound, const char* path){
    *sound = Mix_LoadWAV(path);
    if(*sound == NULL ){
        throw SDLException("Failed to load sound effect! SDL_mixer "
                           "Error: %s\n",Mix_GetError() );
    }
}

//Carga la musica con el archivo en path
void Sounds::_loadMusicFile(Mix_Music** music, const char* path){
    *music = Mix_LoadMUS(path);
    if(*music == NULL ) {
        throw SDLException("Failed to load beat music! SDL_mixer Error: "
                           "%s\n", Mix_GetError());
    }
}

/* Carga todos los sonidos */
void Sounds::_loadSounds() {
    _loadMusicFile(&Music, "../Sounds/hkost.wav");
    _loadSoundFile(&attack, "../Sounds/sword.wav");
    _loadSoundFile(&explotion, "../Sounds/meguminExplotion.wav");
}

void Sounds::playAttackSound() {
    Mix_PlayChannel(-1, attack, 0 );
}

void Sounds::playExplotionSound() {
    Mix_PlayChannel(-1, explotion, 0 );
}


void Sounds::playMusic() {
    if( Mix_PlayingMusic() == 0 ) {//Empieza musica si no habia
        Mix_PlayMusic(Music, -1);
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
    Mix_FreeChunk(attack);
    Mix_FreeChunk(explotion);
    Mix_FreeMusic(Music);

    //Cierra el mixer
    Mix_Quit();
    SDL_Quit();//Esto iria en la clase SDL general
}