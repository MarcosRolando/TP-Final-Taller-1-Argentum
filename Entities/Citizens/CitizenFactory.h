//
// Created by agustin on 25/6/20.
//

#ifndef ARGENTUM_CITIZENFACTORY_H
#define ARGENTUM_CITIZENFACTORY_H

#include <unordered_map>
#include <memory>
#include "../../Config/GameEnums.h"
#include "../../Map/Coordinate.h"

class Entity;

typedef void (*CitizenCreator)(std::shared_ptr<Entity>& citizen, Coordinate initialPosition);


class CitizenFactory {
private:
    std::unordered_map<GameType::Entity, CitizenCreator> citizensCreators;

private:
    static void _storeTrader(std::shared_ptr<Entity>& citizen, Coordinate initialPosition);
    static void _storePriest(std::shared_ptr<Entity>& citizen, Coordinate initialPosition);
    static void _storeBanker(std::shared_ptr<Entity>& citizen, Coordinate initialPosition);

public:
    CitizenFactory();
    void storeCitizen(std::shared_ptr<Entity>& citizen, GameType::Entity _type, Coordinate initialPosition);
};


#endif //ARGENTUM_CITIZENFACTORY_H
