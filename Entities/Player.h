//
// Created by agustin on 8/6/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H


#include "../Items/Inventory.h"
#include "Entity.h"
#include "PlayerStats.h"

class Game;
class EntityTests;
class MapTests;

class Player: public Entity {
private:
    GameType::Race race;
    Inventory inventory;
    PlayerStats stats;
    int32_t gold;
    Game& game;

    friend EntityTests;
    friend MapTests;

public:
    //El nivel minimo debe ser 1, sino tendra vida 0
    Player(Game& _game, GameType::Race _race, GameType::Class _class, unsigned int _level,
           unsigned int _experience, Coordinate _initialPosition, std::string&& nickname);

    //Indica si el jugador es target de un monster, un jugador es un target si esta vivo, si
    //esta muerto no lo es
    bool isMonsterTarget() override;

    //Ataca el lugar especificado en target
    void attack(Coordinate target) override;

    //Si hay lugar en el inventario del player entonces se apropia del item y
    //retorna true, sino no se apropia de el y retorna false
    bool storeItem(std::shared_ptr<Item>&& item);

    //Retorna el item que almacene el inventario al pedirle el item con nombre
    //itemName
    std::shared_ptr<Item> removeItem(const std::string& itemName);

    //Intenta reducir en amount la cantidad de oro que guarda, si esta es menor
    //que amount entonces no la reduce y retorna false, sino la reduce y retorna
    //true
    bool spendGold(int amount);

    //Incrementa el oro del Player en cantidad amount
    void receiveGold(unsigned int amount);

    //Usa el item en la posicion indicada, si no hay un item en la posicion no
    //hace nada
    void useItem(int itemPosition);

    //Ataca al player, retorna el danio ocasionado y el xp ganado
    AttackResult attacked(int damage, unsigned int attackerLevel, bool isAPlayer) override;

    //Retorna el nombre del player
    const std::string& getNickname() const;

    //Restaura hasta amount cantidad de vida, sin pasarse de la cantidad maxima
    void restoreLife(unsigned int amount);

    //Restaura hasta amount cantidad de mana, sin pasarse de la cantidad maxima
    void restoreMana(unsigned int amount);

    //Actualiza al player acorde a su estado actual (moviendo, meditando, etc)
    void update(double timeStep) override;

    //Hace que el player comience a meditar
    void meditate();

    //Notifica al juego la intencion de moverse del player
    void requestMove(Direction direction);

    //Desequipa la ropa de equipment place
    void unequip(EquipmentPlace clothing);

    //Compra el item de nombre itemName del npc en la posicion npcPosition, si no hay
    //uno no hace nada
    void buyFrom(const std::string& itemName, Coordinate npcPosition);

    //Vende el item de nombre itemName al npc en la posicion npcPosition, si no hay
    //uno no hace nada
    void sellTo(const std::string& itemName, Coordinate npcPosition);

    void withdrawFrom(const std::string& itemName, Coordinate npcPosition);

    void listFrom(Coordinate npcPosition);

    void depositTo(const std::string& itemName, Coordinate npcPosition);

    //Desequipa el arma
    void unequip();

    void dropItem(unsigned int itemPosition);

    void operator>>(std::stringstream& buffer) override;

    void storeAllRelevantData(std::stringstream& buffer);

private:
    void _dropItems();
};


#endif //ARGENTUM_PLAYER_H
