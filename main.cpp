#include <iostream>
#include "FileReader.h"
#include "Configuration.h"
#include "SDL/SoundRepository.h"
#include <unistd.h>

int main() {
/*    std::cout <<"mindef "<< Configuration::getInstance()
    .configLeatherArmorStats().minDefense << std::endl;
    std::cout <<"maxdef "<< Configuration::getInstance()
            .configLeatherArmorStats().maxDefense << std::endl;*/

    SoundRepository test;
    char sound;
    std::cin >> sound;
    if (sound == 'a')
        test.playAttackSound();
    if (sound == 'e')
        test.playExplotionSound();

    return 0;
}
