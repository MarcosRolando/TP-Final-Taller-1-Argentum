//
// Created by marcos on 6/24/20.
//

#ifndef ARGENTUM_SERVERPROTOCOL_H
#define ARGENTUM_SERVERPROTOCOL_H


#include "../Map/Map.h"
#include <msgpack.hpp>

class PlayerProxy;

class ServerProtocol {
private:
    std::vector<char> mapBuffer;
    std::stringstream generalData;
    std::vector<char> generalDataBuffer;
    std::stringstream currentStateData;//Guarda el estado actual del juego para que despues los
                                       //clientes puedan ser actualizados solo recibiendo los cambios realidados
    std::vector<char> currentStateBuffer;
    const Map &map;

private:
    static void _loadBytes(std::vector<char>& buffer, void* data, unsigned int size);

public:
    explicit ServerProtocol(const Map &map);
    const std::vector<char>& getMapInfo() const;

    const std::vector<char>& buildCurrentState(const std::list<Player*>& players,
                                        const std::list<Monster*>& monsters);

    //Agrega la informacion del stringstream al buffer que contiene la informacion
    //general que se mandara a todos los clientes
    void addToGeneralData(std::stringstream& data);

    //Arma el mensaje a mandar con la informacion general, resetea el stringstream
    //que guarda la informacion general
    void buildGeneralDataBuffer();

    const std::vector<char>& getGeneralData();

    static std::vector<char> getPlayerData(const PlayerProxy& player);

    void storeEntityInitialData(const Entity* entity);//todo creo que esto no hace falta para nada

    //todo HACER FUNCION QUE CONSIGA LA DATA INICIAL DEL PLAYER

};


#endif //ARGENTUM_SERVERPROTOCOL_H
