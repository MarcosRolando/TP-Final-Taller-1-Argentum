//
// Created by ivan on 8/6/20.
//

#include "FileReader.h"

FileReader::FileReader() {
    file.open("../config.json");
    reader.parse(file, obj);
}

Json::Value FileReader::getNewbieLevel(){
    int n = obj["NewbieLevel"].asInt();
    return n;
}

FileReader::~FileReader() {
    file.close();
}
