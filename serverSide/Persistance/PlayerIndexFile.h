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

    /*Almacena los datos actualizados de un player player ya estaba almacenado en el archivo*/
    void storeOldPlayer(const std::string& playerNickname, PlayerFilePosition filePosition);

    /*Almacena en el archivo los datos de un player que acaba de ser creado*/
    void storeNewPlayer(const std::string& playerNickname, PlayerFilePosition filePosition);

    /*Retorna la posicion del player en el archivo que contiene todos sus datos*/
    PlayerFilePosition getPlayerPosition(const std::string& nickname);

    /*Retorna true si el player existe en el archivo de datos, false en caso contrario*/
    bool playerExists(const std::string& nickname) const;

private:
    void _loadFileData();
};


#endif //ARGENTUM_PLAYERINDEXFILE_H
