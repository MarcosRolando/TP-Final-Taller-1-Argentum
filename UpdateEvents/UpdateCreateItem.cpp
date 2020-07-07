//
// Created by marcos on 7/5/20.
//

#include "UpdateCreateItem.h"
#include "../Client/GameGUI.h"
#include "../Client/ProtocolEnumTranslator.h"

UpdateCreateItem::UpdateCreateItem(GameType::ItemType _type, int32_t _item,
                                    Coordinate _position) {
    ProtocolEnumTranslator translator;
    position = _position;
    switch (_type) {
        case GameType::ITEM_TYPE_GOLD:
            item = Gold;
            break;
        case GameType::ITEM_TYPE_WEAPON:
            item = translator.getWeaponDropTexture(static_cast<GameType::Weapon>(_item));
            break;
        case GameType::ITEM_TYPE_CLOTHING:
            item = translator.getClothingDropTexture(static_cast<GameType::Clothing>(_item));
            break;
        case GameType::ITEM_TYPE_POTION:
            item = translator.getPotionTexture(static_cast<GameType::Potion>(_item));
            break;
        case GameType::ITEM_TYPE_NONE:
            throw TPException("Intentaron crear un item que no existia");
            break;
    }
}

void UpdateCreateItem::operator()(GameGUI &game) {
    game.getMap().createItem(position, item);
}
