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
#include "../SDL/GUI/PlayerInventoryGUI.h"
#include "../SDL/GUI/PlayerInfoGUI.h"
#include "../Texture/PlayerEquipment.h"
#include "EntityData.h"
#include "CitizenData.h"

class GameGUI {
private:
    Window screen;
    SDL_Rect camera{0, 0, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT};
    TextureRepository repo;
    Map map;
    Minichat minichat;
    Selector selector;
    PlayerInfoGUI infoGUI;
    PlayerInventoryGUI inventoryGUI;
    Texture& background;//Esto capaz es mejor ponerlo en window u otra clase

public:
    GameGUI();
    void setMapSize(int rows, int columns);
    void loadTileData(Coordinate position, FloorTypeTexture floor, TextureID structure,
                      CitizenData& citizen);
    void createItem(Coordinate position, TextureID itemTexture);
    void addNPC(EntityData& entityData);
    void addPlayer(MapPlayerData& playerData);

    Window& getWindow();
    Minichat& getMinichat();
    Selector& getSelector();
    PlayerInfoGUI& getPlayerInfo();
    PlayerInventoryGUI& getPlayerInventory();
    Map& getMap();

    void setCameraOn(Coordinate position);

    void render(float timeStep);
};


#endif //ARGENTUM_GAMEGUI_H
