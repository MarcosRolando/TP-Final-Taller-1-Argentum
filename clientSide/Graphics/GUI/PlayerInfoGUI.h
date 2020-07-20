//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINFOGUI_H
#define ARGENTUM_PLAYERINFOGUI_H

#include "../Text/Text.h"
#include "PlayerStats.h"
#include "../../Map/Coordinate.h"
#include "../../Sound/SoundPlayer.h"

struct GUIInfoText {
    Text nickname;
    Text health;
    Text mana;
    Text xp;
    Text level;
    Text constitution, strength, agility, intelligence;
    Text gold;
    Text position;

    GUIInfoText(SDL_Renderer& renderer, Font& font) : nickname(font, renderer),
    health(font, renderer), mana(font, renderer),
    xp(font, renderer),level(font, renderer),
    constitution(font, renderer),
    strength(font, renderer), agility(font, renderer),
    intelligence(font, renderer), gold(font, renderer),
    position(font, renderer) {}
};

class PlayerInfoGUI {
private:
    Font infoFont;
    Text info;
    SDL_Renderer& renderer;
    PlayerStats pInfo{};
    SoundPlayer& soundPlayer;
    GUIInfoText infoText;

public:
    PlayerInfoGUI(SDL_Renderer& renderer, SoundPlayer& soundPlayer);

    Text& getLevelText();
    int32_t getXPos() const;
    int32_t getYPos() const;
    std::string& getNickname();
    Text& getStrengthText();
    Text& getConstitutionText();
    Text& getAgilityText();
    Text& getIntelligenceText();
    Text& getPositionText();
    Text& getNicknameText();
    Text& getGoldText();

    /* Actualiza todas las stats del jugador */
    void update(PlayerStats& generalInfo);

    /* Renderiza las barras de vida, xp y mana */
    void render();

private:
    void _renderInfoBar(Text& textToRender, int32_t infoCurr, int32_t infoTotal, int32_t xOffset,
                        int32_t barLen, SDL_Color color);
    void _updateHealth(int32_t currHealth, int32_t totalHealth);
    void _updateMana(int32_t currMana, int32_t totalMana);
    void _updateXP(int32_t currXP,int32_t nextLevelXP);
    void _updateLevel(int32_t newLevel);
    void _updatePosition(Coordinate position);
    void _updateStrength(int32_t strength);
    void _updateConstitution(int32_t constitution);
    void _updateAgility(int32_t agility);
    void _updateIntelligence(int32_t intelligence);
    void _updateNickname(std::string&& name);
    void _updateGold(int32_t gold, int32_t safeGold);
};


#endif //ARGENTUM_PLAYERINFOGUI_H
