//
// Created by marcos on 6/25/20.
//

#ifndef ARGENTUM_GAMEGUI_H
#define ARGENTUM_GAMEGUI_H

#include "../Screen/Window.h"
#include "../Texture/TextureRepository.h"
#include "GameConstants.h"
#include "../Map/Map.h"
#include "../Graphics/Minichat/Minichat.h"
#include "../Graphics/Selector.h"
#include "../Graphics/GUI/PlayerInventoryGUI.h"
#include "../Graphics/GUI/PlayerInfoGUI.h"
#include "../Texture/PlayerEquipment.h"
#include "../Sound/SoundPlayer.h"
#include "EntityData.h"
#include "CitizenData.h"

class GameGUI {
private:
    Window screen;
    SDL_Rect camera{0, 0, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT};
    TextureRepository repo;
    SoundPlayer soundPlayer;
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
    void setCameraOn(std::string& playerNickname);
    void render(float timeStep);
    Window& getWindow();
    Minichat& getMinichat();
    Selector& getSelector();
    PlayerInfoGUI& getPlayerInfo();
    PlayerInventoryGUI& getPlayerInventory();
    Map& getMap();
    SoundPlayer& getSoundPlayer();

    TextureRepository &getTextureRepo();
};


#endif //ARGENTUM_GAMEGUI_H
