//
// Created by marcos on 7/7/20.
//

#ifndef ARGENTUM_UPDATEATTACK_H
#define ARGENTUM_UPDATEATTACK_H

#include "UpdateEvent.h"
#include "../Map/Coordinate.h"
#include "../../libs/GameEnums.h"
#include <string>

class UpdateAttack : public UpdateEvent {
private:
    Coordinate position{};
    GameType::Weapon weapon;
    GameType::Direction attackDir;
    std::string nickname;

public:
    UpdateAttack(std::string& _nickname, Coordinate _position, int32_t _weapon,
                                            GameType::Direction _attackDir);
    void operator()(GameGUI& game) override;

private:
    bool _shouldPlaySound(); //Para no spammear siempre sonidos de ataque de los monstruos
};


#endif //ARGENTUM_UPDATEATTACK_H
