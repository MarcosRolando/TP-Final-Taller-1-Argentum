#include "SoundRepository.h"

#define FREQUENCY 44100
#define CHUNKSIZE 2048

SoundRepository::SoundRepository() {
    _init();
    _loadSounds();
    //Mix_VolumeMusic(32);
}

void SoundRepository::_init() {
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
/*void SoundRepository::_loadSoundFile(Mix_Chunk** sound, const char* path){
    *sound = Mix_LoadWAV(path);
    if(*sound == NULL ){
        throw SDLException("Failed to load sound effect! SDL_mixer "
                           "Error: %s\n",Mix_GetError() );
    }
}

//Carga la musica con el archivo en path
void SoundRepository::_loadMusicFile(Mix_Music** music, const char* path){
    *music = Mix_LoadMUS(path);
    if(*music == NULL ) {
        throw SDLException("Failed to load beat music! SDL_mixer Error: "
                           "%s\n", Mix_GetError());
    }
}*/

/* Carga todos los sonidos */
/*void SoundRepository::_loadSounds() {
    _loadMusicFile(&Music, "../SoundRepository/hkost.wav");
    _loadSoundFile(&attack, "../SoundRepository/attack.wav");
    _loadSoundFile(&explotion, "../SoundRepository/meguminExplotion.wav");
}*/

void SoundRepository::_loadSounds(){
    sounds.emplace(Explotion, "../Sounds/explotion.wav");
    sounds.emplace(Attack,"../Sounds/attack.wav");
}

void SoundRepository::playAttackSound() {
    Mix_PlayChannel(-1, sounds.at(Attack).getSound(), 0 );
}

void SoundRepository::playExplotionSound() {
    Mix_PlayChannel(-1, sounds.at(Explotion).getSound(), 0 );
}


/*void SoundRepository::playMusic() {
    if( Mix_PlayingMusic() == 0 ) {//Empieza musica si no habia
        Mix_PlayMusic(Music, -1);
    } else if (Mix_PausedMusic() == 1) {//Resume musica si estaba en pausa
        Mix_ResumeMusic();
    }
}*/

/*void SoundRepository::pauseMusic() {
    Mix_PauseMusic();
}

void SoundRepository::stopMusic(){
    Mix_HaltMusic();
}*/

SoundRepository::~SoundRepository() {
    //Libera los sonidos
    /*Mix_FreeChunk(attack);
    Mix_FreeChunk(explotion);
    Mix_FreeMusic(Music);*/


    //Cierra el mixer
    Mix_Quit();
    SDL_Quit();//Esto iria en la clase SDL general
}
