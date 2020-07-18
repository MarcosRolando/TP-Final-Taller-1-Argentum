//
// Created by agustin on 8/6/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H


#include "../Items/Inventory.h"
#include "Entity.h"
#include "PlayerStats.h"
#include "Minichat.h"
#include "../Items/ItemData.h"
#include "MovementBackup.h"

class Game;
class EntityTests;
class MapTests;

class Player: public Entity {
private:
    GameType::Race race;
    GameType::Class pClass;
    Inventory inventory;
    PlayerStats stats;
    int32_t gold;
    Minichat chat;
    Game& game;
    MovementBackup movementBackup{};

    friend EntityTests;
    friend MapTests;

public:
    Player(Game& _game, Coordinate _initialPosition, const PlayerData& data);

    /*Indica si el jugador es target de un monster, un jugador es un target si esta vivo, si
    esta muerto no lo es*/
    bool isMonsterTarget() override;

    /*Ataca el lugar especificado en target*/
    int32_t attack(Coordinate target) override;

    /*Si hay lugar en el inventario del player entonces se apropia del item y
    retorna true, sino no se apropia de el y retorna false*/
    bool storeItem(std::shared_ptr<Item>& item);

    /*Retorna el item que almacene el inventario al pedirle el item con nombre
    itemName*/
    std::shared_ptr<Item> removeItem(const std::string& itemName);

    /*Intenta reducir en amount la cantidad de oro que guarda, si esta es menor
    que amount entonces no la reduce y retorna false, sino la reduce y retorna
    true*/
    bool spendGold(int amount);

    /*Incrementa el oro del Player en cantidad amount*/
    void receiveGold(unsigned int amount);

    /*Usa el item en la posicion indicada, si no hay un item en la posicion no
    hace nada*/
    UseReturnData useItem(int itemPosition);

    /*Ataca al player, retorna el danio ocasionado y el xp ganado*/
    AttackResult attacked(int damage, unsigned int attackerLevel, bool isAPlayer) override;

    /*Restaura hasta amount cantidad de vida, sin pasarse de la cantidad maxima*/
    void restoreLife(unsigned int amount);

    /*Restaura hasta amount cantidad de mana, sin pasarse de la cantidad maxima*/
    void restoreMana(unsigned int amount);

    /*Actualiza al player acorde a su estado actual (moviendo, meditando, etc)*/
    void update(double timeStep);

    /*Hace que el player comience a meditar (el Warrior no puede meditar)*/
    void meditate();

    /*Desequipa la ropa de equipment place*/
    bool unequip(GameType::EquipmentPlace clothing);

    /*Compra el item de nombre itemName del npc en la posicion npcPosition, si no hay
    uno no hace nada*/
    void buyFrom(const std::string& itemName, Coordinate npcPosition);

    /*Vende el item de nombre itemName al npc en la posicion npcPosition, si no hay
    uno no hace nada*/
    void sellTo(const std::string& itemName, Coordinate npcPosition);

    /*Pide recuperar un item de una posicion, en el caso que haya un banker
     * se retornara el item pedido (si existiera), si no hay un banker no pasa
     * nada*/
    void withdrawFrom(const std::string& itemName, Coordinate npcPosition);

    /*Pide que le listen los items a un NPC ubicado en npcPosition, si no hay
     * un npc valido no pasa nada*/
    void listFrom(Coordinate npcPosition);

    /*Intenta depositar un item en el banker ubicado en npcPosition, si no hay
    * un npc valido no pasa nada*/
    void depositTo(const std::string& itemName, Coordinate npcPosition);

    /*Desequipa el arma*/
    bool unequip();

    /*Retorna una instancia de un ItemData que guarda el tipo e id de item y la
    posicion en la que el item fue dejado, si no se encuentra un item en la posicion
    recibida entonces se almacena -1 en el id del item*/
    const Item* dropItem(unsigned int itemPosition);

    /*Carga los datos generales del player de acuerdo al protocolo, se utiliza
     * para la info que se le envia a un cliente recien conectado*/
    void operator>>(std::stringstream& buffer) const override;

    /*Almacena los datos personales del player acorde al protocolo, estos
     * datos solo son enviados al cliente que controla a ese player
     * (seria la UI externa al mapa)*/
    void storeAllRelevantData(std::stringstream& buffer) const;

    /*Limpia el minichat del player, se llama despues de haber enviado el update
     * al cliente que controla a ese player. Es para no mandar los mensajes repetidos*/
    void clearMinichat();

    /*Agrega un mensaje al minichat del player*/
    void addMessage(const std::string& message);

    /*Le confirma a entity el request de movimiento para comenzar la interpolacion*/
    void move(Coordinate newPosition) override;

    /*Setea el mana y la vida del player al maximo*/
    void restoreStats(bool isBeingRevived);

    /*Retorna true si el player esta muerto, false en caso contrario*/
    bool isDead();

    /*Resetea la interpolacion del player*/
    void resetMovement();

    /*Retorna true si el player tiene dicho item, false en caso contrario*/
    bool hasItem(const std::string& itemName);

    /*Agrega al minichat del player en nombre de los items que tiene en el
     * inventario para que el cliente sepa como se llaman*/
    void getInventoryNames();

    /*Setea la direccion de movimiento del player en direction*/
    void startMovement(GameType::Direction direction);

    /*Deja de mover al player*/
    void stopMovement();

    /*Retorna su data actual (las cosas guardadas, stats, etc)*/
    PlayerData getData() const;

private:
    void _dropItems();
    void _storeAttackedResultMessage(std::string& resultMessage, std::pair<int, bool> attackResult,
                                     unsigned int experience);
    AttackResult _receiveDamage(int damage, unsigned int attackerLevel, bool isAPlayer);
};


#endif //ARGENTUM_PLAYER_H
