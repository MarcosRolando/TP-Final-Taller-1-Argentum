//
// Created by agustin on 5/7/20.
//

#include "NotifyDeath.h"

#include "../../Entities/Player.h"
#include "../../Config/GameEnums.h"
#include "../../Server/ServerProtocol.h"
#include <msgpack.hpp>
#include "../../Server/ServerProtocol.h"

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::EquipmentPlace)

NotifyDeath::NotifyDeath(const Player &player): player(player) {

}

void NotifyDeath::operator()(ServerProtocol &protocol) {
    std::stringstream data;
    msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::PLAYER_DEATH);
    msgpack::pack(data, messageTypeData);
    msgpack::type::tuple<std::string> nicknameData(player.getNickname());
    msgpack::pack(data, nicknameData);
    _appendUnequipMessages(data);
    protocol.addToGeneralData(data);
}

////////////////////////////////PRIVATE//////////////////////////

void NotifyDeath::_appendUnequipMessages(std::stringstream& data) {
    std::vector<GameType::EquipmentPlace> equipment = {GameType::EQUIPMENT_PLACE_WEAPON,
          GameType::EQUIPMENT_PLACE_SHIELD, GameType::EQUIPMENT_PLACE_HEAD,
          GameType::EQUIPMENT_PLACE_CHEST};

    for (const auto & place: equipment) {
        msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::UNEQUIP);
        msgpack::pack(data, messageTypeData);
        msgpack::type::tuple<std::string, GameType::EquipmentPlace>
                unequipmentData(player.getNickname(), place);
        msgpack::pack(data, unequipmentData);
    }
    msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::EQUIPPED);
    msgpack::pack(data, messageTypeData);
    msgpack::type::tuple<std::string, GameType::EquipmentPlace, int32_t>
            equippedData(player.getNickname(), GameType::EQUIPMENT_PLACE_CHEST,
                    GameType::COMMON_CLOTHING);
    msgpack::pack(data, equippedData);
}
