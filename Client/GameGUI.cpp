//
// Created by marcos on 6/25/20.
//

#include "GameGUI.h"

void GameGUI::setMapSize(int rows, int columns) {
    map.setSize(rows, columns);
}

GameGUI::GameGUI() : repo(screen.getRenderer()), map(repo, camera),
                    minichat(screen.getRenderer()), infoGUI(screen.getRenderer())
                    ,inventoryGUI(repo, screen.getRenderer()),
                    background(repo.getTexture(Background)){
}

void GameGUI::loadTileData(int i, int j, FloorTypeTexture floor, TextureID structure,
                                                            TextureID entity) {
    map.loadTileData(i , j , floor, structure, entity);
}

void GameGUI::render() {
    //Texture& background = repo.getTexture(Background);
    screen.clear();
    screen.setViewport(ScreenViewport);
    background.render(0, 0);
    //Mapa
    screen.setViewport(MapViewport);
    map.renderGround();
    map.renderStructures();

    //Inventario
    screen.setViewport(InventoryViewport);
    inventoryGUI.render(selector.getInventorySlot());
    //PlayerInfo
    screen.setViewport(PlayerInfoViewport);
    infoGUI.updateHealth(20000, 20000);
    infoGUI.updateMana(9800, 10000);
    infoGUI.updateXP(150000, 800000);
    //Minichat
    screen.setViewport(MinichatViewport);
    minichat.render();
    screen.show();
}
