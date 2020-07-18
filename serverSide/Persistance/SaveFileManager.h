//
// Created by marcos on 9/7/20.
//

#ifndef ARGENTUM_SAVEFILEMANAGER_H
#define ARGENTUM_SAVEFILEMANAGER_H

#include "PlayerIndexFile.h"
#include "PlayerSaveFile.h"
#include <mutex>

/*Esta clase se encarga de administrar la persistencia del servidor. Maneja los
 * 2 archivos (indice y save file)*/

class SaveFileManager {
private:
    PlayerIndexFile indexFile;
    PlayerSaveFile saveFile;
    std::mutex m;

public:
    SaveFileManager(const std::string& indexPath, const std::string& savePath) :
                    indexFile(indexPath), saveFile(savePath) {}

    /*Retorna la data almacenada del player. Si el player no existe tira exception*/
    PlayerData getPlayerData(const std::string& playerNickname);

    /*Almacena la data del player recibida en el correspondiente en el archivo.
     * Si el player no existia en el archivo tira exception*/
    void storeOldPlayer(const PlayerData& data);

    /*Almacena la data del player recibida, agregando la entrada correspondiente
     * en ambos archivos. Si el player ya existia tira exception*/
    void storeNewPlayer(const PlayerData& data);
};


#endif //ARGENTUM_SAVEFILEMANAGER_H
