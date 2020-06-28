//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINFOGUI_H
#define ARGENTUM_PLAYERINFOGUI_H

#include "../Text/Text.h"

struct PlayerInfo {
    int32_t totalHealth, totalMana, nextLevelXP;
    int32_t health, mana, xp;
    int32_t level;
    int32_t constitution, strength, agility, intelligence;
    int32_t xPos, yPos;
};

class PlayerInfoGUI {
private:
    Font infoFont;
    Text info;
    SDL_Renderer& renderer;
    PlayerInfo pInfo{};
public:
    explicit PlayerInfoGUI(SDL_Renderer& renderer);

    void updateHealth(int32_t currHealth);
    void updateTotalHealth(int32_t _totalHealth);
    void updateMana(int32_t currMana);
    void updateTotalMana(int32_t _totalMana);
    void updateXP(int32_t currXP);
    void updateNextLevelXP(int32_t _nextLevelXP);
    void updateLevel(int32_t newLevel);
    void updatePosition(int32_t x, int32_t y);
    //Capaz conviene hacer una que le sume 1 a todas las skills y listo
    void updateStrength(int32_t strength);
    void updateConstitution(int32_t constitution);
    void updateAgility(int32_t agility);
    void updateIntelligence(int32_t intelligence);

    int32_t getLevel() const;
    int32_t getXPos() const;
    int32_t getYPos() const;
    int32_t getStrength() const;
    int32_t getConstitution() const;
    int32_t getAgility() const;
    int32_t getIntelligence();

    void render();

private:
    void _renderInfoBar(int32_t infoCurr, int32_t infoTotal, int32_t xOffset,
                        int32_t barLen, SDL_Color color);
};


#endif //ARGENTUM_PLAYERINFOGUI_H
