#ifndef ARGENTUM_SOUNDREPOSITORY_H
#define ARGENTUM_SOUNDREPOSITORY_H


#include <iostream>
#include <unordered_map>

#include "SDLException.h"
#include "Sound.h"

enum SoundID {Attack, Explotion};

class SoundRepository {
private:
    //Mix_Music *Music = NULL;
    /*Mix_Chunk *attack = NULL;
    Mix_Chunk *explotion = NULL;*/
    //Ver si agregamos mas sonidos, por ejemplo "punch" para cuando ataca sin
    // tener equipada un arma
    std::unordered_map<SoundID, Sound> sounds;
public:
    /* Constructor */
    SoundRepository();
    /* Reproduce el sonido de ataque con espada */
    void playAttackSound();
    /* Reproduce el sonido de explosion */ /* No olvidarse de cambiar el
 * actual por el que va a ir en la version final */
    void playExplotionSound();
    /* Reproduce la musica, por ahora es la del hk, ver si hay que cambiarla*/
   // void playMusic();
    /* Pausa la musica */
    //void pauseMusic();
    /* Termina la reproduccion de la musica. Esta capaz no sirve*/
    //void stopMusic();
    /* Destructor */
    ~SoundRepository();

private:
    void _init();
    void _loadSounds();
    void _loadSoundFile(Mix_Chunk **sound, const char *path);
    void _loadMusicFile(Mix_Music **music, const char *path);
};


#endif //ARGENTUM_SOUNDREPOSITORY_H
