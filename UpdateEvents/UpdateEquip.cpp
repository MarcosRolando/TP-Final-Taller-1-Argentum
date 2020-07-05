//
// Created by marcos on 7/5/20.
//

#include "UpdateEquip.h"
#include "../Client/ProtocolEnumTranslator.h"
#include "../Client/GameGUI.h"

UpdateEquip::UpdateEquip(std::string &&_nickname,
                         GameType::EquipmentPlace _place, int32_t _equipment) {

    ProtocolEnumTranslator translator;
    nickname = std::move(_nickname);
    place = _place;
    switch (place) {
        case GameType::EQUIPMENT_PLACE_WEAPON:
            equipment = translator.getWeaponTexture(static_cast<GameType::Weapon>(_equipment));
            break;

        default:
            equipment = translator.getClothingTexture(static_cast<GameType::Clothing>(_equipment));
    }
}

void UpdateEquip::operator()(GameGUI &game) {
    game.getMap().equipOnPlayer(nickname, place, equipment);
}
