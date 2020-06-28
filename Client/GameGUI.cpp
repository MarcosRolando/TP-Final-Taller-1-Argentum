//
// Created by marcos on 6/25/20.
//

#include "GameGUI.h"

void GameGUI::setMapSize(int rows, int columns) {
    map.setSize(rows, columns);
}

GameGUI::GameGUI() : repo(screen.getRenderer()), map(repo, camera),
                    minichat(screen.getRenderer()), infoGUI(screen.getRenderer())
                    ,inventoryGUI(repo, screen.getRenderer(), infoGUI),
                    background(repo.getTexture(Background)) {
}

void GameGUI::loadTileData(Coordinate position, FloorTypeTexture floor,
                                TextureID structure, TextureID entity) {
    map.loadTileData(position, floor, structure, entity);
}

void GameGUI::render() {
    screen.clear();
    screen.setViewport(ScreenViewport);
    background.render(0, 0);

    //Mapa
    screen.setViewport(MapViewport);
    map.renderGround();
    map.renderNPCS(0);
    map.renderStructures();

    //Inventario
    screen.setViewport(InventoryViewport);
    inventoryGUI.render(selector.getInventorySlot());

    //PlayerInfo
    screen.setViewport(PlayerInfoViewport);
    infoGUI.render();

    //Minichat
    screen.setViewport(MinichatViewport);
    minichat.render();
    screen.show();
}

Window& GameGUI::getWindow() {
    return screen;
}

Minichat &GameGUI::getMinichat() {
    return minichat;
}

Selector &GameGUI::getSelector() {
    return selector;
}

PlayerInfoGUI &GameGUI::getPlayerInfo() {
    return infoGUI;
}

void GameGUI::addNPC(TextureID type, std::string&& nickname, Coordinate position) {
    map.addNPC(type, std::move(nickname), position);
}

void GameGUI::loadTileItem(Coordinate position, TextureID itemTexture) {
    map.loadTileItem(position, itemTexture);
}

void GameGUI::addPlayer(PlayerEquipment equipment, std::string &&nickname,
                        Coordinate position) {
    map.addPlayer(equipment, std::move(nickname), position);
}

PlayerInventoryGUI &GameGUI::getPlayerInventory() {
    return inventoryGUI;
}

