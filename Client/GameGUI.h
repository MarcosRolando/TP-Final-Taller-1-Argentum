//
// Created by marcos on 6/25/20.
//

#ifndef ARGENTUM_GAMEGUI_H
#define ARGENTUM_GAMEGUI_H

#include "../Screen/Window.h"
#include "../Texture/TextureRepository.h"
#include "../GameConstants.h"
#include "../Map/Map.h"
#include "../SDL/Minichat/Minichat.h"
#include "../SDL/Selector.h"

class GameGUI {
private:
    Window screen;
    SDL_Rect camera{ 0, 0, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT};
    TextureRepository repo;
    Map map;
    Minichat minichat;
    Selector selector;

public:
    GameGUI();
    void setMapSize();
    ~GameGUI();

private:
    static void _initializeSDL();
};


#endif //ARGENTUM_GAMEGUI_H
