//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H

#include "PlayerTexture.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player {
private:
    PlayerTexture pTexture;
    int xSpeed;
    int ySpeed;
    int xPosition;
    int yPosition;

public:
    Player(SDL_Renderer& renderer, int x, int y, std::string& helmetImage, std::string& headImage,
           std::string& bodyImage, std::string& weaponImage);

    Player(SDL_Renderer& renderer, int x, int y, std::string&& helmetImage, std::string&& headImage,
           std::string&& bodyImage, std::string&& weaponImage) : Player(renderer, x, y,
                   helmetImage, headImage, bodyImage, weaponImage){}

    void move(Direction direction);

    void handleEvent(SDL_Event& e);
};


#endif //ARGENTUM_PLAYER_H
