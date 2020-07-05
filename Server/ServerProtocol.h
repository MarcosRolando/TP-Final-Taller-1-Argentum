//
// Created by marcos on 6/24/20.
//

#ifndef ARGENTUM_SERVERPROTOCOL_H
#define ARGENTUM_SERVERPROTOCOL_H


#include <msgpack.hpp>

class Player;
class Monster;
class Entity;
class PlayerProxy;
class Game;

class ServerProtocol {
private:
    std::vector<char> mapBuffer;
    std::stringstream generalData;
    std::vector<char> generalDataBuffer;
    std::stringstream currentStateData;//Guarda el estado actual del juego para que despues los
                                       //clientes puedan ser actualizados solo recibiendo los cambios realidados
    std::vector<char> currentStateBuffer;
    const Game& game;

private:
    static void _loadBytes(std::vector<char>& buffer, void* data, unsigned int size);

public:
    explicit ServerProtocol(const Game& game);
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

    static std::vector<char> getPlayerData(PlayerProxy& player);
};


#endif //ARGENTUM_SERVERPROTOCOL_H
