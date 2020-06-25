//
// Created by marcos on 6/15/20.
//

#ifndef ARGENTUM_MAPFILEREADER_H
#define ARGENTUM_MAPFILEREADER_H

#include <fstream>
#include "jsoncpp/json/json.h"
#include <unordered_map>

struct TileInfo {
    std::string tileType;
    std::string structureType;
    std::string entityType;
};

struct MapSize {
    unsigned int width;
    unsigned int height;
};

class MapFileReader {
private:
    Json::Reader reader;
    Json::Value obj;
    std::ifstream file;
    std::unordered_map<int, std::string> mapElements;
    MapSize mapDimensions{};

public:
    explicit MapFileReader(const std::string& path);
    TileInfo getTileInfo(int x, int y);
    MapSize getMapDimensions() const;
    ~MapFileReader();

private:
    void _readMapSize();
    void _readIDs();
};


#endif //ARGENTUM_MAPFILEREADER_H
