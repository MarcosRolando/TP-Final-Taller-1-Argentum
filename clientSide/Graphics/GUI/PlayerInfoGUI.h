//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINFOGUI_H
#define ARGENTUM_PLAYERINFOGUI_H

#include "../Text/Text.h"
#include "GUIPlayerInfo.h"
#include "../../Map/Coordinate.h"

class PlayerInfoGUI {
private:
    Font infoFont;
    Text info;
    SDL_Renderer& renderer;
    GUIPlayerInfo pInfo{};

public:
    explicit PlayerInfoGUI(SDL_Renderer& renderer);

    int32_t getLevel() const;
    int32_t getXPos() const;
    int32_t getYPos() const;
    int32_t getStrength() const;
    int32_t getConstitution() const;
    int32_t getAgility() const;
    int32_t getIntelligence() const;
    std::string getNickname() const;
    void update(GUIPlayerInfo& generalInfo);
    void render();

private:
    void _renderInfoBar(int32_t infoCurr, int32_t infoTotal, int32_t xOffset,
                        int32_t barLen, SDL_Color color);
    void _updateHealth(int32_t currHealth);
    void _updateTotalHealth(int32_t _totalHealth);
    void _updateMana(int32_t currMana);
    void _updateTotalMana(int32_t _totalMana);
    void _updateXP(int32_t currXP);
    void _updateNextLevelXP(int32_t _nextLevelXP);
    void _updateLevel(int32_t newLevel);
    void _updatePosition(Coordinate position);
    void _updateStrength(int32_t strength);
    void _updateConstitution(int32_t constitution);
    void _updateAgility(int32_t agility);
    void _updateIntelligence(int32_t intelligence);
    void _updateNickname(std::string&& name);
};


#endif //ARGENTUM_PLAYERINFOGUI_H
