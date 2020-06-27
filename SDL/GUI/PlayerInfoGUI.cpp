//
// Created by ivan on 13/6/20.
//

#include "PlayerInfoGUI.h"
#include "../../GameConstants.h"

PlayerInfoGUI::PlayerInfoGUI(SDL_Renderer &renderer) : infoFont("../SDL/Text/medieval.ttf", 25),
                                                    info(infoFont, renderer), renderer(renderer) {
    /*totalHealth = 100;
    totalMana = 100;
    nextLevelXP = 100;
    health = totalHealth;
    mana = totalMana;
    xp = nextLevelXP;*/
    pInfo = {};
}


void PlayerInfoGUI::updateHealth(uint32_t currHealth){
    pInfo.health = currHealth;//Ver que pasa si me mandan una vida mayor a la total
}

void PlayerInfoGUI::updateTotalHealth(uint32_t _totalHealth){
    pInfo.totalHealth = _totalHealth;
}

void PlayerInfoGUI::updateMana(uint32_t currMana){
    pInfo.mana = currMana;
}

void PlayerInfoGUI::updateTotalMana(uint32_t _totalMana){
    pInfo.totalMana = _totalMana;
}

void PlayerInfoGUI::updateXP(uint32_t currXP){
    pInfo.xp = currXP;
}

void PlayerInfoGUI::updateNextLevelXP(uint32_t _nextLevelXP){
    pInfo.nextLevelXP = _nextLevelXP;
}

void PlayerInfoGUI::updateLevel(uint32_t newLevel) {
    pInfo.level = newLevel;
}

void PlayerInfoGUI::updateStrength(uint32_t strength){
    pInfo.strength = strength;
}

void PlayerInfoGUI::updateAgility(uint32_t agility) {
    pInfo.agility = agility;
}

void PlayerInfoGUI::updateConstitution(uint32_t constitution) {
    pInfo.constitution = constitution;
}

void PlayerInfoGUI::updateIntelligence(uint32_t intelligence) {
    pInfo.intelligence = intelligence;
}


void PlayerInfoGUI::updatePosition(int32_t x, int32_t y) {
    pInfo.xPos = x;
    pInfo.yPos = y;
}

void PlayerInfoGUI::render(){
    info.updateText("HEALTH: " + std::to_string(pInfo.health) + "/" + std::to_string(pInfo.totalHealth));
    _renderInfoBar(pInfo.health, pInfo.totalHealth, HEALTH_BAR_X_OFFSET, 265,{0x99, 0x00,0x00});

    info.updateText("MANA: " + std::to_string(pInfo.mana) + "/" + std::to_string(pInfo.totalMana));
    _renderInfoBar(pInfo.mana, pInfo.totalMana, MANA_BAR_X_OFFSET, 250,{0x00, 0x33, 0x66});

    info.updateText("XP: " + std::to_string(pInfo.xp) + "/" + std::to_string(pInfo.nextLevelXP));
    _renderInfoBar(pInfo.xp, pInfo.nextLevelXP, XP_BAR_X_OFFSET, 265,{0x00, 0x66, 0x00});
}

void PlayerInfoGUI::_renderInfoBar(uint32_t infoCurr, uint32_t infoTotal,
                                   int32_t xOffset, uint32_t barLen, SDL_Color color){
    float healthBar = barLen * ((float)infoCurr/(float)infoTotal);

    //Barra
    SDL_Rect fillRect = {xOffset, 10, (int)healthBar, BAR_HEIGHT};
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, 0xFF);
    SDL_RenderFillRect( &renderer, &fillRect);

    //outline de la barra
    SDL_Rect outlineRect = {xOffset, 10, (int)barLen, BAR_HEIGHT };
    SDL_SetRenderDrawColor( &renderer, 0x00,0x00,0x00, 0xFF );
    SDL_RenderDrawRect( &renderer, &outlineRect );
    //Texto de la barra
    info.render(xOffset, 10, SDL_Color{0xFF,0xFF,0xFF});
}

uint32_t PlayerInfoGUI::getLevel() const {
    return pInfo.level;
}

uint32_t PlayerInfoGUI::getXPos() const {
    return pInfo.xPos;
}

uint32_t PlayerInfoGUI::getYPos() const {
    return pInfo.yPos;
}

uint32_t PlayerInfoGUI::getStrength() const {
    return pInfo.strength;
}

uint32_t PlayerInfoGUI::getConstitution() const {
    return pInfo.constitution;
}

uint32_t PlayerInfoGUI::getAgility() const {
    return pInfo.agility;
}

uint32_t PlayerInfoGUI::getIntelligence() {
    return pInfo.intelligence;
}
