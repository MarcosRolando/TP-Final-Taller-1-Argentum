//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINFOGUI_H
#define ARGENTUM_PLAYERINFOGUI_H

#include "../Text/Text.h"

struct PlayerInfo {
    uint32_t totalHealth, totalMana, nextLevelXP;
    uint32_t health, mana, xp;
    uint32_t level;
    uint32_t constitution, strength, agility, intelligence;
    uint32_t xPos, yPos;
};

class PlayerInfoGUI {
private:
    Font infoFont;
    Text info;
    SDL_Renderer& renderer;
    PlayerInfo pInfo{};
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
    //Capaz conviene hacer una que le sume 1 a todas las skills y listo
    void updateStrength(uint32_t strength);
    void updateConstitution(uint32_t constitution);
    void updateAgility(uint32_t agility);
    void updateIntelligence(uint32_t intelligence);

    uint32_t getLevel() const;
    uint32_t getXPos() const;
    uint32_t getYPos() const;
    uint32_t getStrength() const;
    uint32_t getConstitution() const;
    uint32_t getAgility() const;
    uint32_t getIntelligence();

    void render();

private:
    void _renderInfoBar(uint32_t infoCurr, uint32_t infoTotal, int32_t xOffset,
                        uint32_t barLen, SDL_Color color);
};


#endif //ARGENTUM_PLAYERINFOGUI_H
