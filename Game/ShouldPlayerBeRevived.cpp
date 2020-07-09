//
// Created by agustin on 8/7/20.
//

#include "ShouldPlayerBeRevived.h"

#include "ResurrectData.h"
#include "../Config/GameEnums.h"
#include "../Entities/Player.h"
#include "../Map/Map.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::EventID)

ShouldPlayerBeRevived::ShouldPlayerBeRevived(Map& map, std::stringstream &data, double _timeStep)
                                    : map(map), data(data) {
    timeStep = _timeStep;
}

bool ShouldPlayerBeRevived::operator()(ResurrectData &resurrectData) {
    if (!resurrectData.playerToResurrect->isDead()) {
        return true;
    }
    resurrectData.timeWaited += timeStep;
    Coordinate noFreePositionReturn = {-1, -1};
    Coordinate positionToTeleport{};
    if (resurrectData.timeWaited >= resurrectData.timeToWait) {
        positionToTeleport = map.getSpawnCoordinateArroundPosition(resurrectData.resurrectingPriest);
        if (positionToTeleport != noFreePositionReturn) {
            map.moveEntity(resurrectData.playerToResurrect->getPosition(), positionToTeleport);
            resurrectData.playerToResurrect->restoreStats();
            _storeResurrectMessage(resurrectData);
            _storeTeleportMessage(resurrectData, positionToTeleport);
            return true;
        }
    }
    return false;
}

//////////////////////////////////PRIVATE////////////////////////////////////

void ShouldPlayerBeRevived::_storeResurrectMessage(const ResurrectData& resurrectData) {
    msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::RESURRECTED);
    msgpack::pack(data, messageTypeData);
    msgpack::type::tuple<std::string> resurrectDataTuple(resurrectData.playerToResurrect->getNickname());
    msgpack::pack(data, messageTypeData);
}

void ShouldPlayerBeRevived::_storeTeleportMessage(const ResurrectData& resurrectData, Coordinate newPosition) {
    msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::TELEPORTED);
    msgpack::pack(data, messageTypeData);
    msgpack::type::tuple<std::string, int32_t, int32_t> resurrectDataTuple
                (resurrectData.playerToResurrect->getNickname(), newPosition.iPosition, newPosition.jPosition);
    msgpack::pack(data, messageTypeData);
}
