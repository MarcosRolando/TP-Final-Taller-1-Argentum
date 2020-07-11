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

void GameGUI::render(float timeStep) {
    //Font UIFont("../SDL/Text/medieval.ttf", 25);
    //Text clickPos(UIFont, screen.getRenderer());

    map.update(timeStep);
    screen.clear();
    screen.setViewport(ScreenViewport);
    background.render(0, 0);

    //Mapa
    screen.setViewport(MapViewport);
    map.renderGround();
    map.renderNPCS();
    map.renderStructures();
    //Outline del tile seleccionado. Ver si lo ponemos en Map
   // Coordinate tileToRender = selector.getSelectedTileToRender({getPlayerInfo().getYPos(),getPlayerInfo().getXPos()});
    //SDL_Rect fillRect = {tileToRender.j, tileToRender.i, 128, 128};
    //SDL_SetRenderDrawColor(&screen.getRenderer(), 0xFF,
                           //0x00, 0x00, 0xFF);
    //SDL_RenderDrawRect( &screen.getRenderer(), &fillRect );//Debugging*/

    //Inventario
    screen.setViewport(InventoryViewport);
    inventoryGUI.render(selector.getInventorySlot());
    //clickPos.updateText("ClickX: " + std::to_string(selector.getSelectedTile().j) +
                        //"   ClickY: " + std::to_string(selector.getSelectedTile().i));
    //clickPos.render(150,100, {0xFF,0xFF,0xFF});//Debugging del click

    //PlayerInfo
    screen.setViewport(PlayerInfoViewport);
    infoGUI.render();

    //Minichat
    screen.setViewport(MinichatViewport);
    minichat.render();//todo race condition
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

void GameGUI::setCameraOn(Coordinate position) {
    map.setCameraOn(position);
}



