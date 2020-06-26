//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINFOGUI_H
#define ARGENTUM_PLAYERINFOGUI_H

#include "../Text/Text.h"

class PlayerInfoGUI {
private:
    Font infoFont;
    Text info;
    SDL_Renderer& renderer;
    uint32_t totalHealth, totalMana, nextLevelXP;
    uint32_t health, mana, xp;

public:
    explicit PlayerInfoGUI(SDL_Renderer& renderer);

    void updateHealth(uint32_t currHealth);
    void updateTotalHealth(uint32_t _totalHealth);

    void updateMana(uint32_t currMana);
    void updateTotalMana(uint32_t _totalMana);

    void updateXP(uint32_t currXP);
    void updateNextLevelXP(uint32_t _nextLevelXP);

    void updateLevel(uint32_t newLevel);

    void updatePosition(int32_t x, int32_t y);

    void updateSkills(uint32_t strength, uint32_t agility,
                      uint32_t intelligence, uint32_t constitution);

    void render();

private:
    void _renderInfoBar(uint32_t infoCurr, uint32_t infoTotal, int32_t xOffset,
                        uint32_t barLen, SDL_Color color);
};


#endif //ARGENTUM_PLAYERINFOGUI_H
