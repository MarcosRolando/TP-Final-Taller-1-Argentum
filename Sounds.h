#ifndef ARGENTUM_SOUNDS_H
#define ARGENTUM_SOUNDS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>

#include "SDLException.h"


class Sounds {
private:
    Mix_Music *gMusic = NULL;
    Mix_Chunk *gScratch = NULL;
    Mix_Chunk *gHigh = NULL;
    Mix_Chunk *gMedium = NULL;
    Mix_Chunk *gLow = NULL;
public:
    Sounds();
    void playScratchSound();
    void playHighSound();
    void playMediumSound();
    void playLowSound();
    void playMusic();
    void pauseMusic();
    void stopMusic();
    ~Sounds();

private:
    void _init();
    void _loadSounds();
};


#endif //ARGENTUM_SOUNDS_H
