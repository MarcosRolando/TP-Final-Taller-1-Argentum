//
// Created by marcos on 6/25/20.
//

#include "GameGUI.h"

void GameGUI::setMapSize(int rows, int columns) {
    map.setSize(rows, columns);
}

GameGUI::GameGUI() : repo(screen.getRenderer()), map(repo, camera, soundPlayer),
                    minichat(screen.getRenderer()), infoGUI(screen.getRenderer())
                    ,inventoryGUI(repo, screen.getRenderer(), infoGUI),
                    background(repo.getTexture(Background)) {
}

void GameGUI::loadTileData(Coordinate position, FloorTypeTexture floor,
                                TextureID structure, CitizenData& citizen) {
    map.loadTileData(position, floor, structure, citizen);
}

void GameGUI::update(double timeStep) {
    map.update(timeStep);
}

void GameGUI::render() {
    screen.clear();
    screen.setViewport(ScreenViewport);
    background.render(0, 0);

    //Mapa
    screen.setViewport(MapViewport);
    map.renderGround();
    map.renderNPCS();
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

void GameGUI::addNPC(EntityData& entityData) {
    map.addNPC(entityData);
}

void GameGUI::createItem(Coordinate position, TextureID itemTexture) {
    map.createItem(position, itemTexture);
}

void GameGUI::addPlayer(MapPlayerData& playerData) {
    map.addPlayer(playerData);
}

PlayerInventoryGUI &GameGUI::getPlayerInventory() {
    return inventoryGUI;
}

Map &GameGUI::getMap() {
    return map;
}

SoundPlayer &GameGUI::getSoundPlayer() {
    return soundPlayer;
}

TextureRepository& GameGUI::getTextureRepo() {
    return repo;
}

void GameGUI::setCameraOn(std::string& playerNickname) {
    map.setCameraOn(playerNickname);
}



