//
// Created by ivan on 13/6/20.
//

#include "PlayerInfoGUI.h"
#include "../../GameConstants.h"

PlayerInfoGUI::PlayerInfoGUI(Font &font, SDL_Renderer &renderer) : info(font,
                                        renderer), renderer(renderer) {}


void PlayerInfoGUI::updateHealth(unsigned int currHealth, unsigned int
totalHealth){
    info.updateText("HEALTH: " + std::to_string(currHealth)
                      + "/" + std::to_string(totalHealth));
    _renderInfo(currHealth, totalHealth, HEALTH_BAR_X_OFFSET, 265, {0x99,0x00,
                                                                0x00});
}

void PlayerInfoGUI::updateMana(unsigned int currMana, unsigned int totalMana){
    info.updateText("MANA: " + std::to_string(currMana)
                    + "/" + std::to_string(totalMana));
    _renderInfo(currMana, totalMana, MANA_BAR_X_OFFSET, 250, {0x00,0x33,0x66});
}

void PlayerInfoGUI::updateXP(unsigned int currXP, unsigned int nextLevelXP){
    info.updateText("XP: " + std::to_string(currXP)
                    + "/" + std::to_string(nextLevelXP));
    _renderInfo(currXP, nextLevelXP, XP_BAR_X_OFFSET, 265,{0x00,0x66,0x00});
}

void PlayerInfoGUI::_renderInfo(unsigned int infoCurr, unsigned int infoTotal,
                                int xOffset, unsigned int barLen, SDL_Color
                                color){
    float healthBar = barLen * ((float)infoCurr/(float)infoTotal);

    //Barra
    SDL_Rect fillRect = {xOffset, 0, (int)healthBar, BAR_HEIGHT};
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, 0xFF);
    SDL_RenderFillRect( &renderer, &fillRect);

    //outline de la barra
    SDL_Rect outlineRect = {xOffset, 0, (int)barLen, BAR_HEIGHT };
    SDL_SetRenderDrawColor( &renderer, 0x00,0x00,0x00, 0xFF );
    SDL_RenderDrawRect( &renderer, &outlineRect );
    info.render(xOffset, 0, SDL_Color{0xFF,0xFF,0xFF});
}

void PlayerInfoGUI::updateLevel(unsigned int newLevel) {
    info.updateText(std::to_string(newLevel));
    info.render(70, 50, SDL_Color{0xFF,0xFF,0xFF});
}

