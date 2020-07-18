#include "SoundRepository.h"

#define QUEUE_SIZE 3

#define SWORD_ATTACK_PATH "../../clientSide/Sounds/swordAttack.wav"
#define HEAVY_ATTACK_PATH "../../clientSide/Sounds/HeavyAttack.wav"
#define ATTACK_1_PATH "../../clientSide/Sounds/genericAttack1.wav"
#define ATTACK_2_PATH "../../clientSide/Sounds/genericAttack2.wav"
#define ARROW_PATH "../../clientSide/Sounds/arrow.wav"
#define DEATH_1_PATH "../../clientSide/Sounds/Death.wav"
#define DEATH_2_PATH "../../clientSide/Sounds/YodaDeath.wav"
#define STEP_PATH "../../clientSide/Sounds/Step.wav"
#define EXPLOTION_1_PATH "../../clientSide/Sounds/Explotion1.wav"
#define EXPLOTION_2_PATH "../../clientSide/Sounds/Explotion2.wav"
#define EXPLOTION_3_PATH "../../clientSide/Sounds/Explotion3.wav"
#define HEALING_PATH "../../clientSide/Sounds/heal.wav"
#define ZOMBIE_PATH "../../clientSide/Sounds/Zombie.mp3"
#define SPIDER_PATH "../../clientSide/Sounds/Spider.mp3"
#define SKELETON_PATH "../../clientSide/Sounds/Skeleton.mp3"
#define GOBLIN_PATH "../../clientSide/Sounds/Goblin.wav"

#define MUSIC_PATH "../../clientSide/Sounds/argentumOnlineOST.mp3"

SoundRepository::SoundRepository() {
    _loadSounds();
    _loadMusic();
}

void SoundRepository::_loadSounds() {
    try {
        sounds.emplace(SwordAttackSound, SWORD_ATTACK_PATH);
        sounds.emplace(HeavyAttackSound, HEAVY_ATTACK_PATH);
        sounds.emplace(Attack1Sound, ATTACK_1_PATH);
        sounds.emplace(Attack2Sound, ATTACK_2_PATH);
        sounds.emplace(ArrowSound, ARROW_PATH);
        sounds.emplace(Death1Sound, DEATH_1_PATH);
        sounds.emplace(Death2Sound, DEATH_2_PATH);
        sounds.emplace(StepSound, STEP_PATH);
        sounds.emplace(Explotion1Sound, EXPLOTION_1_PATH);
        sounds.emplace(Explotion2Sound, EXPLOTION_2_PATH);
        sounds.emplace(Explotion3Sound, EXPLOTION_3_PATH);
        sounds.emplace(HealingSound, HEALING_PATH);
        sounds.emplace(ZombieSound, ZOMBIE_PATH);
        sounds.emplace(SpiderSound, SPIDER_PATH);
        sounds.emplace(SkeletonSound, SKELETON_PATH);
        sounds.emplace(GoblinSound, GOBLIN_PATH);

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    Mix_Volume(-1, 25);
}

void SoundRepository::_loadMusic(){
    music = Mix_LoadMUS(MUSIC_PATH);
    Mix_VolumeMusic(20);
    if(music == nullptr ) {
        throw TPException("Failed to load beat music! SDL_mixer Error: "
                           "%s\n", Mix_GetError());
    }
}

SoundRepository::~SoundRepository() {
    //Cierra el mixer
    Mix_FreeMusic(music);
}

Mix_Music* SoundRepository::getMusic() {
    return music;
}

Mix_Chunk* SoundRepository::getSound(SoundID id) {
    return sounds.at(id).getSound();
}
