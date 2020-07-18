//
// Created by marcos on 6/15/20.
//

#include "MapFileReader.h"
#include "../../libs/TPException.h"
#include <memory>

using json = nlohmann::json;

MapFileReader::MapFileReader(const std::string& path) {
    mapDimensions.width = 0;
    mapDimensions.height = 0;
    std::ifstream file(path);
    if (!file.is_open()) {
        throw TPException("Could not open Map File, check whether"
                          " it exists or not!");
    }
    try {
        file >> obj;
    } catch (...) {
        throw TPException("Map file parsing failed!");
    }
    _readMapSize();
    _readIDs();
}

void MapFileReader::_readMapSize() {
    mapDimensions.width = obj["width"].get<int>();
    mapDimensions.height = obj["height"].get<int>();
}

void MapFileReader::_readIDs() {
    json& tilesets = obj["tilesets"];
    mapElements.emplace(0, "Nothing");
    for (auto & tileset : tilesets) {
        std::string name = tileset["name"].get<std::string>();
        int id = tileset["firstgid"].get<int>();
        int tilecount = tileset["tilecount"].get<int>();
        if (tilecount > 1) {
            for (int i = 0; i < tilecount; ++i) {
                mapElements.emplace(id + i, name + std::to_string(i));
            }
        } else {
            mapElements.emplace(id, name);
        }
    }
}

TileInfo MapFileReader::getTileInfo(unsigned int row, unsigned int column) {
    json& layers = obj["layers"];
    json& tileData = layers[0]["data"];
    TileInfo tile;
    tile.tileType = mapElements.at(tileData[row*mapDimensions.width + column].get<int>());
    json& sData = layers[1]["data"];
    tile.structureType = mapElements.at(sData[row*mapDimensions.width + column].get<int>());
    json& eData = layers[2]["data"];
    tile.entityType = mapElements.at(eData[row*mapDimensions.width + column].get<int>());
    json& oData = layers[3]["data"]; /*isOccupable*/
    tile.isOccupable = (oData[row*mapDimensions.width + column].get<int>() == 0);
    json& cData = layers[4]["data"]; /*isFromCity*/
    tile.isFromCity = (cData[row*mapDimensions.width + column].get<int>() != 0);
    return tile;
}

MapSize MapFileReader::getMapDimensions() const {
    return mapDimensions;
}
