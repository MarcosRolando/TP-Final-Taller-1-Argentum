//
// Created by marcos on 6/15/20.
//

#include "MapFileReader.h"
#include "TPException.h"

MapFileReader::MapFileReader(const std::string& path) {
    width = 0;
    height = 0;
    file.open(path);
    try {
        reader.parse(file, obj);
    } catch (...) {
        file.close();
        throw TPException("Fallo el parseo del Mapa!");
    }
    _readMapSize();
    _readIDs();
}

void MapFileReader::_readMapSize() {
    width = obj["width"].asInt();
    height = obj["height"].asInt();
}

void MapFileReader::_readIDs() {
    Json::Value& tilesets = obj["tilesets"];
    mapElements.emplace(0, "Nothing");
    for (auto & tileset : tilesets) {
        std::string name = tileset["name"].asString();
        int id = tileset["firstgid"].asInt();
        int tilecount = tileset["tilecount"].asInt();
        if (tilecount > 1) {
            for (int i = 0; i < tilecount; ++i) {
                mapElements.emplace(id + i, name + std::to_string(i));
            }
        } else {
            mapElements.emplace(id, name);
        }
    }
}

TileInfo MapFileReader::getTileInfo(int row, int column) {
    Json::Value& layers = obj["layers"];
    Json::Value& tileData = layers[0]["data"];
    TileInfo tile;
    tile.tileType = mapElements.at(tileData[row*width + column].asInt());
    Json::Value& sData = layers[1]["data"];
    tile.structureType = mapElements.at(sData[row*width + column].asInt());
    Json::Value& eData = layers[2]["data"];
    tile.entityType = mapElements.at(eData[row*width + column].asInt());
    return tile;
}

MapFileReader::~MapFileReader() {
    file.close();
}
