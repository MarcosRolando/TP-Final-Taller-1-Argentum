//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ENTITY_H
#define ARGENTUM_ENTITY_H


#include "../Map/Coordinate.h"
#include <list>
#include <chrono>
#include "../../libs/GameEnums.h"

struct ProductData;
struct AttackResult;
class Game;

struct Movement {
    bool isMoving{false};
    unsigned int movedDistance{0};

    /*Esta direccion solo tiene sentido si se setea que se esta moviendo el entity*/
    GameType::Direction direction{GameType::DIRECTION_STILL};
};

class Player;

class Entity {
private:
    static unsigned int availableId;
    std::string nickname;

protected:
    Coordinate currentPosition{};
    GameType::Entity type;
    Movement movement{};
    unsigned int speed{};

private:
    Coordinate _calculatePreviousPosition() const;

protected:
    GameType::Direction _getMoveDirection(Coordinate destination);

public:
    Entity(GameType::Entity _type, Coordinate initialPosition, const std::string& _nicknamePrefix,
           bool isPrefixUnique = false);

    /*Implementa el comportamiento realizado al atacar,
    debe ser modificado en las clases hijas de ser necesario*/
    virtual int32_t attack(Coordinate target);

    /*Implementa el comportamiento realizado al ser atacado, por default
    retorna struct nulo, debe ser modificado en las clases hijas de ser necesario*/
    virtual AttackResult attacked(int damage, unsigned int level, bool isAPlayer);

    /*Implementa el comportamiento realizado al pedirle una lista de los items
    que tiene en venta, por default no hace nada, debe ser reimplementada
    si la clase hija tiene objetos en venta para listar*/
    virtual void list(Player &player);

    /*Implementa el comportamiento realizado al pedirle uno de los items
    que tiene guardados, por default no hace nada, debe ser reimplementada
    si la clase hija puede almacenar y devolver items*/
    virtual void withdraw(Player& player, const std::string& itemName);

    /*Implementa el comportamiento realizado al pedirle que guarde el item que se
    encuentra en la posicion pasada, por default no hace nada, debe ser reimplementada
    si la clase hija puede almacenar y devolver items*/
    virtual void deposit(Player& player, const std::string& itemName);

    /*Implementa el comportamiento realizado al intentar comprar un item
    con el nombre pasado, por default no hace nada, debe ser reimplementada
    si la clase hija puede comprar y vender items*/
    virtual void buy(Player& player, const std::string& itemName);

    /*Implementa el comportamiento realizado al intentar vender un item que se
    encuentra en la posicion pasada, por default no hace nada, debe ser reimplementada
    si la clase hija puede comprar y vender items*/
    virtual void sell(Player& player, const std::string& itemName);

    /*Indica si el Entity va a ser atacado por un monstruo, por default retorna
    false, las clases que hereden deben reimplementarla si son consideradas
    targets*/
    virtual bool isMonsterTarget();

    /*Le asigna al jugador la posicion recibida*/
    void setPosition(Coordinate coordinate);

    /*Retorna la posicion en la que quiere estar el jugadoras*/
    Coordinate getPosition() const;

    /*Le confirma a entity el request de movimiento para comenzar la interpolacion*/
    virtual void move(Coordinate newPosition);

    /*Por default no hace nada, las clases hijas deben reimplementarlo de ser
     * necesario (por ejemplo el Priest)*/
    virtual void requestHeal(Player& player);

    /*Actualiza el estado de la entity, por ejemplo si se esta moviendo le
    actualiza la interpolacion*/
    void update(double timeStep, Game& game);

    /*Retorna si el entity esta o no en movimiento (lo uso en monster)*/
    bool isMoving() const;

    /*Retorna el tipo de entity (tipo de monstruo, npc o si es un player)*/
    GameType::Entity getType() const;

    /*Carga los datos generales del entity de acuerdo al protocolo, se utiliza
     * para la info que se le envia a un cliente recien conectado*/
    virtual void operator>>(std::stringstream& buffer) const;

    virtual ~Entity() = default;

    /*Retorna el nickname del entity (los monsters/npc tiene asignado uno tambien*/
    virtual const std::string& getNickname() const;

    /*Actualiza la interpolacion de la entity cuando se esta moviendo
     * de un tile al otro*/
    int32_t executeDisplacement(int32_t displacement, bool& hasFinished);

    /*Retorna la coordenada del tile al que se esta desplazando la entity*/
    virtual Coordinate getFinalCoordinate(GameType::Direction direction);

    virtual int32_t getLevel() const;
};


#endif //ARGENTUM_ENTITY_H
