//
// Created by marcos on 6/25/20.
//

#include "GameGUI.h"

void GameGUI::setMapSize(int rows, int columns) {
    map.setSize(rows, columns);
}

GameGUI::GameGUI() : repo(screen.getRenderer()), map(repo, camera),
                    minichat(screen.getRenderer()) {}

void GameGUI::loadTileData(int i, int j, FloorTypeTexture floor, TextureID structure,
                                                            TextureID entity) {
    map.loadTileData(i , j , floor, structure, entity);
}

void GameGUI::render() {
    screen.clear();
    screen.setViewport(MapViewport);
    map.renderGround();
    screen.show();
}
