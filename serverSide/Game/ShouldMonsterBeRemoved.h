//
// Created by agustin on 21/6/20.
//

#ifndef ARGENTUM_SHOULDMONSTERBEREMOVED_H
#define ARGENTUM_SHOULDMONSTERBEREMOVED_H

#include <list>
#include <memory>
#include "../Map/Coordinate.h"

class Monster;

//Functor que indica cuando un monstruo debe ser eliminado de la lista, se debe pasar
//a remove_if para la ista de monsters
//Almacena en la lista recibida las coordenadas de los monsters que se eliminaron para
//sacarlos despues del mapa
class ShouldMonsterBeRemoved {
private:
    std::list<std::pair<Coordinate, const std::string*>>& monstersToRemove;
public:
    explicit ShouldMonsterBeRemoved(std::list<std::pair<Coordinate, const std::string*>>& monstersToRemove);

    //Retorna true si el monstruo esta muerto y guarda su coordenada en la lista
    //almacenada
    bool operator()(const Monster* monster);
};






#endif //ARGENTUM_SHOULDMONSTERBEREMOVED_H
