//
// Created by agustin on 25/6/20.
//

#include "CitizenFactory.h"
#include "Trader.h"
#include "Priest.h"
#include "Banker.h"

////////////////////////////PRIVATE////////////////////////////////

void CitizenFactory::_storeTrader(std::shared_ptr<Entity>& citizen, Coordinate initialPosition) {
    citizen.reset(new Trader(initialPosition));
}


void CitizenFactory::_storePriest(std::shared_ptr<Entity>& citizen, Coordinate initialPosition) {
    citizen.reset(new Priest(initialPosition));
}

void CitizenFactory::_storeBanker(std::shared_ptr<Entity> &citizen, Coordinate initialPosition) {
    citizen.reset(new Banker(initialPosition));
}

////////////////////////////PUBLIC////////////////////////////////

CitizenFactory::CitizenFactory() {
    citizensCreators[GameType::Entity::TRADER] = _storeTrader;
    citizensCreators[GameType::Entity::PRIEST] = _storePriest;
    citizensCreators[GameType::Entity::BANKER] = _storeBanker;
}

void CitizenFactory::storeCitizen(std::shared_ptr<Entity> &citizen, GameType::Entity _type,
                                  Coordinate initialPosition) {
    citizensCreators.at(_type)(citizen, initialPosition);
}
