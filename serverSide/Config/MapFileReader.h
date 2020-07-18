//
// Created by marcos on 6/15/20.
//

#ifndef ARGENTUM_MAPFILEREADER_H
#define ARGENTUM_MAPFILEREADER_H

#include <fstream>
#include "json.hpp"
#include <unordered_map>

struct TileInfo {
    std::string tileType;
    std::string structureType;
    std::string entityType;
    bool isOccupable;
    bool isFromCity;
};

struct MapSize {
    unsigned int width;
    unsigned int height;
};

class MapFileReader {
private:
    nlohmann::json obj;
    std::unordered_map<int, std::string> mapElements;
    MapSize mapDimensions{};

public:
    explicit MapFileReader(const std::string& path);

    /*Retorna los datos del tile (si es ocupable, pertence a una ciudad, tiene un NPC/estructura*/
    TileInfo getTileInfo(unsigned int x, unsigned int y);

    /*Retorna las dimensiones MxN del mapa*/
    MapSize getMapDimensions() const;

private:
    void _readMapSize();
    void _readIDs();
};


#endif //ARGENTUM_MAPFILEREADER_H
