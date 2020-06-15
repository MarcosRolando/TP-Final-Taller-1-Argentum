//
// Created by marcos on 6/15/20.
//

#include "MapFileReader.h"

MapFileReader::MapFileReader(const std::string& path) {
    file.open(path);
    reader.parse(file, obj);
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
        mapElements.emplace(id, name);
    }
}

std::string MapFileReader::getTile(int row, int column) {
    Json::Value& layers = obj["layers"];
    Json::Value& data = layers[0]["data"];
    int type = data[row*width + column].asInt();
    return mapElements.at(type);
}

std::string MapFileReader::getStructure(int row, int column) {
    Json::Value& layers = obj["layers"];
    Json::Value& data = layers[1]["data"];
    int type = data[row*width + column].asInt();
    return mapElements.at(type);
}
