//
// Created by ivan on 13/6/20.
//

#include "PlayerInfoGUI.h"
#include "../GameConstants.h"

PlayerInfoGUI::PlayerInfoGUI(Font &font, SDL_Renderer &renderer) : info(font,
                                                                        renderer), renderer(renderer) {}


void PlayerInfoGUI::updateHealth(unsigned int currHealth, unsigned int
totalHealth){
    info.updateText("HEALTH: " + std::to_string(currHealth)
                      + "/" + std::to_string(totalHealth));
    _renderInfo(currHealth, totalHealth, HEALTH_BAR_Y_OFFSET, {0xFF,0x00,0x00});
}

void PlayerInfoGUI::updateMana(unsigned int currMana, unsigned int totalMana){
    info.updateText("MANA: " + std::to_string(currMana)
                    + "/" + std::to_string(totalMana));
    _renderInfo(currMana, totalMana, MANA_BAR_Y_OFFSET, {0x00,0x00,0xFF});
}

void PlayerInfoGUI::updateXP(unsigned int currXP, unsigned int nextLevelXP){
    info.updateText("XP: " + std::to_string(currXP)
                    + "/" + std::to_string(nextLevelXP));
    _renderInfo(currXP, nextLevelXP, XP_BAR_Y_OFFSET, {0x00,0xFF,0x00});
}

void PlayerInfoGUI::_renderInfo(unsigned int infoCurr, unsigned int infoTotal,
                                int yOffset, SDL_Color color){
    float healthBar = BAR_WIDTH * ((float)infoCurr/(float)infoTotal);

    //Barra
    SDL_Rect fillRect = {BAR_X_OFFSET, yOffset, (int)healthBar, BAR_HEIGHT};
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, 0xFF);
    SDL_RenderFillRect( &renderer, &fillRect);

    //outline de la barra
    SDL_Rect outlineRect = { BAR_X_OFFSET, yOffset,BAR_WIDTH, BAR_HEIGHT };
    SDL_SetRenderDrawColor( &renderer, 0x00,0x00,0x00, 0xFF );
    SDL_RenderDrawRect( &renderer, &outlineRect );
    info.render(BAR_X_OFFSET, yOffset);
}

PlayerInfoGUI::~PlayerInfoGUI() {}

