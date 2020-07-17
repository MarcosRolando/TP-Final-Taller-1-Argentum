//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_BANKER_H
#define ARGENTUM_BANKER_H

#include <unordered_map>
#include "../Entity.h"
#include "../../Server/PlayerData.hpp"

class Storage;

class EntityTests;

class Banker;
typedef void (*ModifyGold)(Storage &playerStorage, Player &player, int goldAmount);

//Clase que se encarga de guardar todos los items que le otorgue el jugador
//El jugador puede darle oro o items nuevos para que guarde o sacar oro o items
class Banker: public Entity {
private:
    static std::unordered_map<std::string, std::pair<unsigned int, Storage>> playersStorages;

    friend EntityTests;

private:
    static int32_t _getNumberOfItemsStored(const std::unordered_map<std::string, unsigned int>&
                                                        initialItemsAmounts) ;
    static void _storeAvailableRoomMessage(Player &player, unsigned int storedItemsAmount);

    static void _modifyGoldReserves(Storage& playerStorage, Player &player,
                        const std::string& itemName, ModifyGold modifier);

    static std::string _translateItemTypeToName(std::tuple<GameType::ItemType, int32_t> item);

    static void _depositGold(Storage &playerStorage, Player &player, int goldAmount);

    static void _withdrawGold(Storage &playerStorage, Player &player, int goldAmount);

public:
    explicit Banker(Coordinate initialPosition);

    /*Almacena una lista con los datos de los items y oro almacenados*/
    void list(Player &player) override;

    /*Intenta sacar el item del banco y almacenarlo en el inventario del jugador
    Si el item no esta guardado en el banco o el judador no tiene espacio en
    su inventario entonces no hace nada
    Si se intenta sacar mas oro del guardado, entonces saca el oro disponible*/
    void withdraw(Player& player, const std::string& itemName) override;

    /*Intenta guardar el item en el banco, sacandolo del inventario del jugador
    Si el item no esta en el inventario del judador entonces no hace nada
    No se pueden guardar items equipados
    Si se intenta depositar mas oro del guardado, entonces deposita la totalidad del oro*/
    void deposit(Player& player, const std::string& itemName) override;

    /*Carga en el banker los items provenientes del player provenientes del archivo,
     * esto se hace cuando un player se conecta*/
    static void addPlayerItems(const PlayerData& playerData);

    /*Borra del banker los items almacenados por el player, esto se hace cuando un player se desconecta*/
    static void erasePlayerItems(const std::string& playerNickname);

    /*Retorna los items del player almacenados para ser guardados en el archivo de persistencia*/
    static void getPlayerItems(PlayerData& playerData);
};


#endif //ARGENTUM_BANKER_H
