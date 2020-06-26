//
// Created by ivan on 13/6/20.
//

#include "PlayerInfoGUI.h"
#include "../../GameConstants.h"

PlayerInfoGUI::PlayerInfoGUI(SDL_Renderer &renderer) : infoFont("../SDL/Text/medieval.ttf", 25),
                                                    info(infoFont, renderer), renderer(renderer) {
    totalHealth = 100;
    totalMana = 100;
    nextLevelXP = 100;
    health = totalHealth;
    mana = totalMana;
    xp = nextLevelXP;
}


void PlayerInfoGUI::updateHealth(uint32_t currHealth){
    health = currHealth;
}

void PlayerInfoGUI::updateTotalHealth(uint32_t _totalHealth){
    totalHealth = _totalHealth;
}

void PlayerInfoGUI::updateMana(uint32_t currMana){
    mana = currMana;
}

void PlayerInfoGUI::updateTotalMana(uint32_t _totalMana){
    totalMana = _totalMana;
}

void PlayerInfoGUI::updateXP(uint32_t currXP){
    xp = currXP;
}

void PlayerInfoGUI::updateNextLevelXP(uint32_t _nextLevelXP){
    nextLevelXP = _nextLevelXP;
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

void PlayerInfoGUI::render(){
    info.updateText("HEALTH: " + std::to_string(health) + "/" + std::to_string(totalHealth));
    _renderInfoBar(health, totalHealth, HEALTH_BAR_X_OFFSET, 265,{0x99, 0x00,0x00});

    info.updateText("MANA: " + std::to_string(mana) + "/" + std::to_string(totalMana));
    _renderInfoBar(mana, totalMana, MANA_BAR_X_OFFSET, 250,{0x00, 0x33, 0x66});

    info.updateText("XP: " + std::to_string(xp) + "/" + std::to_string(nextLevelXP));
    _renderInfoBar(xp, nextLevelXP, XP_BAR_X_OFFSET, 265,{0x00, 0x66, 0x00});
}

void PlayerInfoGUI::updateLevel(uint32_t newLevel) {
    info.updateText(std::to_string(newLevel));
    info.render(70, 50, SDL_Color{0xFF,0xFF,0xFF});
}

void PlayerInfoGUI::updateSkills(uint32_t strength, uint32_t agility,
                                 uint32_t intelligence, uint32_t constitution){
    info.updateText("STRENGTH : " + std::to_string(strength));
    info.render(40, 660, SDL_Color{0xFF,0xFF,0xFF});

    info.updateText("CONSTITUTION : " + std::to_string(constitution));
    info.render(40, 700, SDL_Color{0xFF,0xFF,0xFF});

    info.updateText("INTELLIGENCE : " + std::to_string(intelligence));
    info.render(40, 740, SDL_Color{0xFF,0xFF,0xFF});

    info.updateText("AGILITY : " + std::to_string(agility));
    info.render(40, 780, SDL_Color{0xFF,0xFF,0xFF});
}

void PlayerInfoGUI::updatePosition(int32_t x, int32_t y) {

    info.updateText("MyX: " + std::to_string(x) + "   " + "MyY: " +
                    std::to_string(y));
    info.render(200, 880, {0xFF, 0xFF, 0xFF});
}


