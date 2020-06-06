#include "Sounds.h"

int main( int argc, char* args[] )
{
    try {
        Sounds sounds;

        char soundToPlay;
        do {
            std::cout << "Que sonido queres papa" << std::endl;
            std::cin >> soundToPlay;
            switch (soundToPlay) {
                case 'h':
                    sounds.playHighSound();
                    break;
                case 'm':
                    sounds.playMediumSound();
                    break;
                case 'l':
                    sounds.playLowSound();
                    break;
                case 's':
                    sounds.playScratchSound();
                    break;
                case 'M':
                    sounds.playMusic();
                    break;
                case 'p':
                    sounds.pauseMusic();
                    break;
                default:
                    soundToPlay = 'q';
            }
        } while (soundToPlay != 'q');
        sounds.stopMusic();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

	return 0;
}
