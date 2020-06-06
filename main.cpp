#include "Sounds.h"

int main( int argc, char* args[] )//Para probar la carga y reproduccion de
// sonidos
{
    try {
        Sounds sounds;
        char soundToPlay;
        do {
            std::cout << "Que sonido queres papa" << std::endl;
            std::cin >> soundToPlay;
            switch (soundToPlay) {
                case 'e':
                    sounds.playExplotionSound();
                    break;
                case 'a':
                    sounds.playAttackSound();
                    break;
                case 'm':
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
