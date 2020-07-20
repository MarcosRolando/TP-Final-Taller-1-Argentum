//
// Created by marcos on 6/9/20.
//

#ifndef ARGENTUM_ENTITY_H
#define ARGENTUM_ENTITY_H

#include "../Texture/EntityTexture.h"
#include "../../libs/GameEnums.h"
#include <list>
#include <memory>
#include "../Miscellaneous/Spell.h"

/*Esta clase encapsula el comportamiento general de las entites (personajes
 * del juego, sean npcs o players)*/

class Entity {
private:
    SDL_Rect& camera;
    int currentFrame;
    GameType::Direction moveDirection, lastDirection;
    float xPosition, width;
    float yPosition, height;
    float totalDistanceMoved{0};

protected:
    bool cameraFollows{false};
    std::weak_ptr<Spell> spell;

public:
    Entity(SDL_Rect& camera, float x, float y);

    /*Desplaza al entity en la direccion indicada la distanceTravelled indicada.
     * Si reachedDestination es true, resetea el contador y el frame de la animacion.
     * Este sera true cuando el entity haya terminado de desplazarse la distancia
     * entre un tile y otro (el server me avisa)*/
    GameType::Direction move(GameType::Direction direction, unsigned int distanceTravelled, bool reachedDestination);

    /*Renderiza al la textura de entity recibida*/
    void render(EntityTexture& eTexture);

    /*Metodo abstracto, deben implementarlo los hijos*/
    virtual void render() = 0;

    /*Centra la camara en el player*/
    void updateCamera();

    /*Setea que la camara siga al player, este metodo solo se debera ejecutar
     * en el player propio*/
    void activateCamera();

    /*Agrega un hechizo al entity para que lo siga*/
    void addSpell(std::shared_ptr<Spell>& _spell);

    /*Retorna el spell que guarda el entity, este metodo existe en el caso
     * donde el entity sea matado por un hechizo y el hechizo deba migrar a un tile
     * para no perder la animacion del hechizo*/
    std::weak_ptr<Spell>& getSpell();

    /*Setea la posicion interna del player (en pixeles)*/
    void setPosition(float _xPosition, float _yPosition);

    /*Setea la direccion de renderizado del entity, se utiliza para cuando
     * un entity ataca, para que mire a la direccion en la que ataco*/
    void setLookDirection(GameType::Direction direction);

    virtual void updateLevel(int level) = 0;

    virtual ~Entity() = default;

private:
    void _renderLastDirection(EntityTexture& eTexture);
    void _modifyPosition(GameType::Direction direction, float distance);
    void _updateFrame(bool reachedDestination);
};


#endif //ARGENTUM_ENTITY_H
