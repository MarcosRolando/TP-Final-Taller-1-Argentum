//
// Created by marcos on 7/8/20.
//

#ifndef ARGENTUM_PLAYERINDEXFILE_H
#define ARGENTUM_PLAYERINDEXFILE_H

#include <fstream>
#include <unordered_map>
#include "PlayerFilePosition.h"

/*Esta clase maneja el archivo de indice de jugadores, el cual contiene
 * el nombre del jugador, el offset donde arranca su informacion y la cantidad de
 * bytes que su informacion ocupa (para saber cuanto leer con msgpack)*/
class PlayerIndexFile {
private:
    std::fstream indexFile;
    std::unordered_map<std::string, PlayerFilePosition> players;

public:
    explicit PlayerIndexFile(const std::string& filePath);
    explicit PlayerIndexFile(const std::string&& filePath) : PlayerIndexFile(filePath) {}
    void storeNewPlayer(std::string& playerNickname, PlayerFilePosition offData);
    void storeNewPlayer(std::string&& playerNickname, PlayerFilePosition offData);

private:
    void _loadFileDataToMap();
};


#endif //ARGENTUM_PLAYERINDEXFILE_H
