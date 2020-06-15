//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINFOGUI_H
#define ARGENTUM_PLAYERINFOGUI_H

#include "../Text/Text.h"

class PlayerInfoGUI {
private:
    Text info;
    SDL_Renderer& renderer;

public:
    PlayerInfoGUI(Font& font, SDL_Renderer& renderer);

    void updateHealth(unsigned int currHealth, unsigned int totalHealth);

    void updateMana(unsigned int currMana, unsigned int totalMana);

    void updateXP(unsigned int currXP, unsigned int nextLevelXP);

    void updateLevel(unsigned int newLevel);

private:
    void _renderInfo(unsigned int infoCurr, unsigned int infoTotal, int xOffset,
                     unsigned int barLen, SDL_Color color);
};


#endif //ARGENTUM_PLAYERINFOGUI_H
