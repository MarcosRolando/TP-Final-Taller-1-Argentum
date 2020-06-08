//
// Created by ivan on 8/6/20.
//

#ifndef ARGENTUM_FILEREADER_H
#define ARGENTUM_FILEREADER_H

#include <fstream>

#include "jsoncpp/json/json.h"


class FileReader {
private:
    Json::Reader reader;
    Json::Value obj;
    std::ifstream file;

public:
    FileReader();
    ~FileReader();

    Json::Value getNewbieLevel();
};


#endif //ARGENTUM_FILEREADER_H
