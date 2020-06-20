//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H


#include "Map/Map.h"
#include <queue>

class Game {
private:
    Map map;
    std::queue<std::string> eventQueue;
public:
    AttackResult attackPosition(int damage, unsigned int level,
                            Coordinate coordinate);
    //Llama a Map para que guarde los items recibidos en el tile que corresponde
    //a la coordenada recibida
    void dropItems(std::list<std::shared_ptr<Item>>&& items, Coordinate position);

    //Llama a Map para que guarde el item recibido en el tile que corresponde
    //a la coordenada recibida
    void dropItems(std::shared_ptr<Item>&& item, Coordinate position);

    //Le indica a game que se quiere mover un entity de initial a final position,
    //initialPosition debe contener un entity, sino el comportamiento es indefinido,
    //si finalPosition no es ocupable entoncesno hace nada
    void requestMove(Coordinate initialPosition, Coordinate finalPosition);
};


#endif //ARGENTUM_GAME_H
