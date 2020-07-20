//
// Created by marcos on 6/24/20.
//

#ifndef ARGENTUM_SERVERPROTOCOL_H
#define ARGENTUM_SERVERPROTOCOL_H

#include "../Items/ItemData.h"
#include <msgpack.hpp>

class Player;
class Monster;
class Entity;
class PlayerProxy;
class Game;
class Item;

//Esta clase se encarga de almacenar de la forma apropiada la informacion a mandar a los
//clientes
class ServerProtocol {
private:
    std::vector<char> mapBuffer;
    std::stringstream generalData;
    std::vector<char> generalDataBuffer;
    std::vector<char> currentStateBuffer;
    const Game& game;

private:
    static void _loadBytes(std::vector<char>& buffer, void* data, unsigned int size);

public:
    explicit ServerProtocol(const Game& game);

    //Retorna el buffer que contiene la informacion del mapa que no cambia
    const std::vector<char>& getMapInfo() const;

    //Arma el buffer que almacena todos los datos necesarios para que se conecte un
    //player con la informacion inicial apropiada y retorna una referencia a el
    const std::vector<char>& buildCurrentState(
                                const std::unordered_map<std::string, Player*>& players,
                                const std::list<Monster*>& monsters,
                                const std::unordered_map<Coordinate, const Item*>& mapItems);

    //Agrega la informacion del stringstream al buffer que contiene la informacion
    //general que se mandara a todos los clientes
    void addToGeneralData(std::stringstream& data);

    //Arma el mensaje a mandar con la informacion general, resetea el stringstream
    //que guarda la informacion general
    void buildGeneralDataBuffer();

    //Retorna una referencia al buffer que contiene toda la informacion de lo pasado
    //en el ultimo update de game
    const std::vector<char>& getGeneralData();

    //Retorna un buffer que contiene la informacion del player que almacena el
    //PlayerProxy
    static std::vector<char> getPlayerData(PlayerProxy& player);
};


#endif //ARGENTUM_SERVERPROTOCOL_H
