//
// Created by marcos on 6/15/20.
//

#ifndef ARGENTUM_MAPFILEREADER_H
#define ARGENTUM_MAPFILEREADER_H

#include <fstream>
#include "jsoncpp/json/json.h"
#include <unordered_map>

class MapFileReader {
private:
    Json::Reader reader;
    Json::Value obj;
    std::ifstream file;
    std::unordered_map<int, std::string> mapElements;
    int width, height;

public:
    explicit MapFileReader(const std::string& path);
    std::string getTile(int x, int y);
    std::string getStructure(int row, int column);
    ~MapFileReader();

private:
    void _readMapSize();
    void _readIDs();
};


#endif //ARGENTUM_MAPFILEREADER_H
