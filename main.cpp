#include <iostream>
#include "FileReader.h"
#include "Configuration.h"
#include "Calculator.h"
#include "SDL/SoundRepository.h"
#include <unistd.h>
#include <queue>
#include <random>

int main() {
    Modifiers classMods = Configuration::getInstance().configWarriorModifiers();
    Modifiers raceMods = Configuration::getInstance().configHumanModifiers();
    //WeaponStats weapon = Configuration::getInstance().configLongSwordStats();
    std::cout <<" candodge " << Calculator::canDodge(classMods, raceMods);

    /*SoundRepository test;
    test.playMusic();
    char sound;
    do {
        std::cin >> sound;
        if (sound == 'a')
         test.queueSound(Attack);
     if (sound == 'e')
         test.queueSound(Explotion);
    if (sound == 's')
        test.queueSound(StepDirt);
    if (sound == 'p')
        test.queueSound(Punch);
    if (sound == 'w')
        test.pauseMusic();
    if (sound == 'd')
        test.playMusic();
    }while (sound != 'q');

    test.playSounds();

    std::cin >> sound;
    return 0;*/
}
