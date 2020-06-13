//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINFO_H
#define ARGENTUM_PLAYERINFO_H

#include "Text.h"

class PlayerInfo {
private:
    Text info;
    SDL_Renderer& renderer;

public:
    PlayerInfo(Font& font, SDL_Renderer& renderer);
    ~PlayerInfo();

    void updateHealth(unsigned int currHealth, unsigned int totalHealth);

    void _renderInfo(unsigned int infoCurr, unsigned int infoTotal, int yOffset,
            SDL_Color color);

    void updateMana(unsigned int currMana, unsigned int totalMana);

    void updateXP(unsigned int currXP, unsigned int nextLevelXP);
};


#endif //ARGENTUM_PLAYERINFO_H
