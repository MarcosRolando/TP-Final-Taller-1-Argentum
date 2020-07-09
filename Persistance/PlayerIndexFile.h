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
    std::unordered_map<std::string, int32_t> indexPlayersPosition; /*Guardo la posicion en el indice del largo en bytes*/
                                                                    /*de la info del player para poder acceder rapido cada vez que cambie*/

public:
    explicit PlayerIndexFile(const std::string& filePath);
    void storePlayer(const std::string& playerNickname, PlayerFilePosition filePosition);
    PlayerFilePosition getPlayerPosition(const std::string& nickname);

private:
    void _loadFileData();
    void _storeNewPlayer(const std::string& nickname);
};


#endif //ARGENTUM_PLAYERINDEXFILE_H
