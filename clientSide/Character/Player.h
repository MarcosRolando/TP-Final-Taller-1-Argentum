//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H

#include "Entity.h"
#include "../Texture/PlayerTexture.h"
#include "../Texture/NPCTexture.h"

/*Esta clase representa a los players en el mapa, incluido el propio*/

class Player : public Entity {
private:
    PlayerTexture pTexture;
    NPCTexture ghostTexture;
    bool isAlive{true};

public:
    Player(TextureRepository& repo, SDL_Rect& camera, float x, float y,
                                                    PlayerEquipment& images,
                                                    bool _isAlive = true);

    /* Renderiza al jugador con su equipamiento (o como fantasma si esta muerto) */
    void render() override;

    /* Añade la textura del item que se quiere equipar al jugador */
    void equip(GameType::EquipmentPlace place, TextureID equipment);

    /* Setea isAlive en false asi luego lo renderizo como fantasma */
    void kill();

    /* Setea isAlive en true asi luego lo renderizo normalmente */
    void revive();

    /*Aumenta el nivel que se muestra del player*/
    void updateLevel(int level);
};


#endif //ARGENTUM_PLAYER_H
