//
// Created by ivan on 13/6/20.
//

#include "PlayerInfoGUI.h"

#include <utility>
#include "../../Client/GameConstants.h"

#define PLAYER_INFO_FONT_PATH "../../clientSide/Graphics/Text/medieval.ttf"

PlayerInfoGUI::PlayerInfoGUI(SDL_Renderer &renderer) : infoFont(PLAYER_INFO_FONT_PATH, 25),
                                                    info(infoFont, renderer), renderer(renderer) {
    pInfo = {};
}

void PlayerInfoGUI::_updateHealth(int32_t currHealth){
    pInfo.health = currHealth;
}

void PlayerInfoGUI::_updateTotalHealth(int32_t _totalHealth){
    pInfo.totalHealth = _totalHealth;
}

void PlayerInfoGUI::_updateMana(int32_t currMana){
    pInfo.mana = currMana;
}

void PlayerInfoGUI::_updateTotalMana(int32_t _totalMana){
    pInfo.totalMana = _totalMana;
}

void PlayerInfoGUI::_updateXP(int32_t currXP){
    pInfo.xp = currXP;
}

void PlayerInfoGUI::_updateNextLevelXP(int32_t _nextLevelXP){
    pInfo.nextLevelXP = _nextLevelXP;
}

void PlayerInfoGUI::_updateLevel(int32_t newLevel) {
    pInfo.level = newLevel;
}

void PlayerInfoGUI::_updateStrength(int32_t strength){
    pInfo.strength = strength;
}

void PlayerInfoGUI::_updateAgility(int32_t agility) {
    pInfo.agility = agility;
}

void PlayerInfoGUI::_updateConstitution(int32_t constitution) {
    pInfo.constitution = constitution;
}

void PlayerInfoGUI::_updateIntelligence(int32_t intelligence) {
    pInfo.intelligence = intelligence;
}


void PlayerInfoGUI::_updatePosition(Coordinate position) {
    pInfo.position = position;
}

void PlayerInfoGUI::_updateNickname(std::string&& name){
    pInfo.nickname = std::move(name);
}

void PlayerInfoGUI::render() {
    info.updateText("HEALTH: " + std::to_string(pInfo.health) + "/" + std::to_string(pInfo.totalHealth));
    _renderInfoBar(pInfo.health, pInfo.totalHealth, HEALTH_BAR_X_OFFSET, 265,{0x99, 0x00,0x00});

    info.updateText("MANA: " + std::to_string(pInfo.mana) + "/" + std::to_string(pInfo.totalMana));
    _renderInfoBar(pInfo.mana, pInfo.totalMana, MANA_BAR_X_OFFSET, 265,{0x00, 0x33, 0x66});

    info.updateText("XP: " + std::to_string(pInfo.xp) + "/" + std::to_string(pInfo.nextLevelXP));
    _renderInfoBar(pInfo.xp, pInfo.nextLevelXP, XP_BAR_X_OFFSET, 265,{0x00, 0x66, 0x00});
}

void PlayerInfoGUI::_renderInfoBar(int32_t infoCurr, int32_t infoTotal,
                                   int32_t xOffset, int32_t barLen, SDL_Color color) {
    float bar = 0;
    if (infoTotal != 0){
        bar = barLen * ((float)infoCurr / (float)infoTotal);
    }

    //Barra
    SDL_Rect fillRect = {xOffset, 10, (int)bar, BAR_HEIGHT};
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, 0xFF);
    SDL_RenderFillRect( &renderer, &fillRect);

    //outline de la barra
    SDL_Rect outlineRect = {xOffset, 10, (int)barLen, BAR_HEIGHT };
    SDL_SetRenderDrawColor( &renderer, 0x00,0x00,0x00, 0xFF );
    SDL_RenderDrawRect( &renderer, &outlineRect );
    //Texto de la barra
    info.render(xOffset, 10, SDL_Color{0xFF,0xFF,0xFF});
}

int32_t PlayerInfoGUI::getLevel() const {
    return pInfo.level;
}

int32_t PlayerInfoGUI::getXPos() const {
    return pInfo.position.j;
}

int32_t PlayerInfoGUI::getYPos() const {
    return pInfo.position.i;
}

int32_t PlayerInfoGUI::getStrength() const {
    return pInfo.strength;
}

int32_t PlayerInfoGUI::getConstitution() const {
    return pInfo.constitution;
}

int32_t PlayerInfoGUI::getAgility() const {
    return pInfo.agility;
}

int32_t PlayerInfoGUI::getIntelligence() const {
    return pInfo.intelligence;
}

std::string PlayerInfoGUI::getNickname() const {
    return pInfo.nickname;
}

void PlayerInfoGUI::update(GUIPlayerInfo &generalInfo) {
    _updateHealth(generalInfo.health);
    _updateTotalHealth(generalInfo.totalHealth);
    _updateMana(generalInfo.mana);
    _updateTotalMana(generalInfo.totalMana);
    _updateXP(generalInfo.xp);
    _updateNextLevelXP(generalInfo.nextLevelXP);
    _updateLevel(generalInfo.level);
    _updatePosition(generalInfo.position);
    _updateStrength(generalInfo.strength);
    _updateConstitution(generalInfo.constitution);
    _updateAgility(generalInfo.agility);
    _updateIntelligence(generalInfo.intelligence);
    _updateNickname(std::move(generalInfo.nickname));
}
