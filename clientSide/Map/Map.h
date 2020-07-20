//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H

#include "Tile.h"
#include <vector>
#include "../Texture/TextureRepository.h"
#include "Structure.h"
#include "../Client/ProtocolEnumTranslator.h"
#include "../Texture/PlayerEquipment.h"
#include <list>
#include "../Client/EntityData.h"
#include "../Miscellaneous/Spell.h"
#include "../Client/CitizenData.h"
#include "../Sound/SoundPlayer.h"
#include "../Miscellaneous/Arrow.h"

/*Esta clase representa al mapa del juego y tiene el ownership de las entidades,
 * flechas y hechizos en juego*/

class Map {
private:
    TextureRepository& textureRepo;
    SoundPlayer& soundPlayer;
    std::vector<Tile> tiles;
    SDL_Rect& camera;
    std::unordered_map<std::string, std::pair<std::shared_ptr<Entity>, Coordinate>> entities;
    std::list<std::tuple<std::shared_ptr<Entity>*, Coordinate, std::string>> entitiesToUpdateTilePosition;
    /*Esto es para no pisar entities entre si cuando terminan de moverse*/

    std::list<std::shared_ptr<Spell>> spells;
    std::list<std::unique_ptr<Arrow>> arrows;
    std::string playerNickname;

public:
    Map(TextureRepository& repo, SDL_Rect& camera, SoundPlayer& soundPlayer);

    /*Setea el tamanio del vector unidimensional tiles*/
    void setSize(int rows, int columns);

    /*Carga la data inicial del tile position, es decir, su tipo de piso,
     * estructura (si tuviera) y citizen (si tuviera). Es lo primero que recibo
     * cuando me conecto al server, para cada tile*/
    void loadTileData(Coordinate position, FloorTypeTexture floor, TextureID structure,
                      CitizenData& citizen);

    /*Crea el item con la textura pedida en el tile de coordenada position*/
    void createItem(Coordinate position, TextureID itemTexture);

    /*Crea un npc en el mapa en base a la data provista (textura, posicion, etc)*/
    void addNPC(EntityData& data);

    /*Crea un player en el mapa en base a la data provista (textura, posicion, etc)*/
    void addPlayer(MapPlayerData& playerData);

    /*Desplaza a la entity en la direccion recibida la distanceTravelled indicada,
     * , si termino de moverse (reachedDestination = true) le resetea la animacion.
     * Si es el entity estaba quieto entonces lo encola a la
     * lista de entitesToUpdateTilePosition para actualizarle su posicion*/
    void moveEntity(std::string& nickname, GameType::Direction direction,
            unsigned int distanceTravelled, bool reachedDestination);

    /*Centra la camara en la entidad cuyo nombre matchee con nickname
     * (se utiliza para el propio player)*/
    void setCameraOn(std::string& nickname);

    /*Borra del mapa a la entity*/
    void removeEntity(std::string& nickname);

    /*Equipa en el EquipmentPlace indicado el equipment recibido, se usa para
     * cambiar lo que tienen equipados los players)*/
    void equipOnPlayer(std::string& nickname, GameType::EquipmentPlace place,
                        TextureID equipment);

    /*Setea la texture del player en el fantasma*/
    void killPlayer(std::string& nickname);

    /*Setea la texture del player en la que tiene cuando esta vivo, es decir,
     * si tiene la del fantasma se la quita*/
    void revivePlayer(std::string &nickname);

    /*Agrego un spell en la posicion indicada. Si hubiera un player en dicha
     * posicion se lo agrega a el, sino lo agrega al tile*/
    void addSpell(Coordinate position, TextureID spellTexture);

    /*Agrega un arrow a la lista de arrows, seteando su posicion inicial en
     * la del arquero, dicha arrow se movera al target a medida que pase el tiempo*/
    void addArrow(std::string& archerNickname, Coordinate target, TextureID arrowTexture);

    /*Actualiza las animaciones del juego en base al timeStep y mueve a los entities
     * a sus nuevos tiles correspondientes*/
    void update(double timeStep = 0);

    /*Elimina el item en la posicion indicada*/
    void destroyItem(Coordinate itemPosition);

    /*Teletransporta un entity de una posicion a otra. Se usa para cuando
     * en el juego un player revive en una ciudad*/
    void teleportEntity(const std::string& nickname, Coordinate newPosition,
                        bool isMyPlayer);

    /*Setea el nickname del player propio, util para poder referenciarlo y saber
     * que sonidos realizar (lo buscamos en el map y conseguimos su ubicacion
     * en el mapa)*/
    void setPlayerNickname(const std::string& nickname);

    /*Verifica si el sonido a realizar esta dentro del rango de sonido del player
     * propio*/
    void verifyQueueSound(Coordinate tile, SoundID sound, int maxDistance);

    /*Cambia la direccion de renderizado del entity, se utiliza en el evento de un ataque
     * para que mire a su target*/
    void changeEntityLookDirection(std::string& nickname, GameType::Direction direction);

    /*Actualiza el nivel que se muestra del player*/
    void updatePlayerLevel(const std::string& _playerNickname, int level);

    /*Renderiza el mapa, esto incluye entities, estructuras, spells, etc*/
    void render();

private:
    static Coordinate _calculateNewTile(Coordinate position, GameType::Direction direction);
    void _updateSpells(double timeStep);
    void _updateArrows(double timeStep);
    void _moveEntitiesToNewTile();
    void _addEntity(EntityData& data, std::shared_ptr<Entity>& entity);
    void _renderGround();
    void _renderStructures();
    void _renderNPCS();
    void _renderArrows();
};


#endif //ARGENTUM_MAP_H
