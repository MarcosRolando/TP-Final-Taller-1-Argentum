//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ENTITY_H
#define ARGENTUM_ENTITY_H


#include "../Map/Coordinate.h"
#include <list>
#include <chrono>
#include "../Config/GameEnums.h"

struct ProductData;
struct AttackResult;
class Game;

struct Movement {
    bool isMoving{};
    unsigned int movedDistance{};

    //Esta direccion solo tiene sentido si se setea que se esta moviendo el entity
    GameType::Direction direction{};
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
    unsigned int speed;

private:
    Coordinate _calculatePreviousPosition() const;

 public:
    Entity(GameType::Entity _type, Coordinate initialPosition, std::string&& _nicknamePrefix,
           bool isPrefixUnique = false);

    //Implementa el comportamiento realizado al atacar,
    //debe ser modificado en las clases hijas de ser necesario
    virtual void attack(Coordinate target);

    //Implementa el comportamiento realizado al ser atacado, por default
    //retorna 0, debe ser modificado en las clases hijas de ser necesario
    virtual AttackResult attacked(int damage, unsigned int level, bool isAPlayer);

    //Implementa el comportamiento realizado al pedirle una lista de los items
    //que tiene en venta, por default no hace nada, debe ser reimplementada
    //si la clase hija tiene objetos en venta para listar
    //virtual unsigned int list(const Player &player, std::list<ProductData>& products);
    virtual void list(const Player &player, std::stringstream& data);

    //Implementa el comportamiento realizado al pedirle uno de los items
    //que tiene guardados, por default no hace nada, debe ser reimplementada
    //si la clase hija puede almacenar y devolver items
    virtual void withdraw(Player& player, const std::string& itemName);

    //Implementa el comportamiento realizado al pedirle que guarde el item que se
    //encuentra en la posicion pasada, por default no hace nada, debe ser reimplementada
    //si la clase hija puede almacenar y devolver items
    virtual void deposit(Player& player, const std::string& itemName);

    //Implementa el comportamiento realizado al intentar comprar un item
    //con el nombre pasado, por default no hace nada, debe ser reimplementada
    //si la clase hija puede comprar y vender items
    virtual void buy(Player& player, const std::string& itemName);

    //Implementa el comportamiento realizado al intentar vender un item que se
    //encuentra en la posicion pasada, por default no hace nada, debe ser reimplementada
    //si la clase hija puede comprar y vender items
    virtual void sell(Player& player, const std::string& itemName);

    //Indica si el Entity va a ser atacado por un monstruo, por default retorna
    //false, las clases que hereden deben reimplementarla si son consideradas
    //targets
    virtual bool isMonsterTarget();

    //Encola la accion de movimiento si el entity esta quieto,
    // la cual puede ser rechazada o aceptada
    //void requestMove(Game& game, GameType::Direction moveDirection);

    //Le asigna al jugador la posicion recibida
    void setPosition(Coordinate coordinate);

    //Retorna la posicion en la que quiere estar el jugadoras
    Coordinate getPosition() const;

    //Le confirma a entity el request de movimiento para comenzar la interpolacion
    void move(Coordinate newPosition);

    //Actualiza el estado de la entity, por ejemplo si se esta moviendo le
    //actualiza la interpolacion
    void update(double timeStep, Game& game);

    //Retorna si el entity esta o no en movimiento (lo uso en monster)
    bool isMoving() const;

    GameType::Entity getType() const;

    virtual void operator>>(std::stringstream& buffer) const;

    virtual ~Entity() = default;

    bool isCitizen();

    virtual const std::string& getNickname() const;

    int32_t executeDisplacement(int32_t displacement, bool& hasFinished);

    virtual Coordinate getFinalCoordinate(GameType::Direction direction);
};


#endif //ARGENTUM_ENTITY_H
