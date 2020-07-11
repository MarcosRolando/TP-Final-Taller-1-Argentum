//
// Created by agustin on 14/6/20.
//

#ifndef ARGENTUM_PLAYERSTATS_H
#define ARGENTUM_PLAYERSTATS_H

#include <sstream>
#include <cstdint>
#include "../Config/GameEnums.h"
#include "../Server/PlayerData.hpp"
#include "../Config/ConfigFileReader.h"

class EntityTests;
class MapTests;
class Minichat;

class PlayerStats {
private:
    bool isMeditating{};
    double timeElapsed{};

    int32_t constitution{};
    int32_t  intelligence{};
    int32_t  agility{};
    int32_t  strength{};

    int32_t  classLifeMultiplier{};
    int32_t  raceLifeMultiplier{};
    int32_t  classManaMultiplier{};
    int32_t  raceManaMultiplier{};
    int32_t  recoveryRate{};
    int32_t  meditationRate{};

    int32_t  experience{};
    int32_t  nextLevelExperience{};
    int32_t  level{};
    int32_t  currentMana{};
    int32_t  currentLife{};
    int32_t  maxMana{};
    int32_t  maxLife{};

    friend EntityTests;
    friend MapTests;

public:
    explicit PlayerStats(const PlayerData& data);

    //Retorna el danio base que logro hacer el arma del player para el ataque
    int getTotalDamage(int weaponDamage) const;

    //Retorna el level actual del player
    unsigned int getLevel() const;

    //Aumenta el xp del player
    void increaseExperience(unsigned int _experience);

    //Modifica la vida del player acorde al danio/curacion ocasionados
    int modifyLife(int damage, unsigned int attackerLevel, unsigned int defense,
                   bool isAPlayer, std::string& attackedMessage);

    //Retorna la maxima vida que puede tener el player dado su nivel actual
    int getMaxLife() const;

    //Retorna la vida actual del player
    int getCurrentLife() const;

    //Restaura hasta amount cantidad de vida, sin pasarse de la cantidad maxima
    void restoreLife(unsigned int amount);

    //Restaura hasta amount cantidad de mana, sin pasarse de la cantidad maxima
    void restoreMana(unsigned int amount);

    //Retorna si el player esta o no muerto
    bool isDead() const;

    //Actualiza el estado de la vida y el mana del player
    void update(double timeStep);

    //Setea el player a modo meditacion
    void startMeditating(Minichat& minichat);

    //Hace que el player deje de estar en modo meditacion
    void stopMeditating(Minichat& minichat);

    int32_t& getCurrentMana();

    void restore();

    //Guarda experiencia, experiencia para proximo nivel, nivel, mana actual, mana maximo,
    //vida, vida maxima y si esta vivo (true) o muerto (false)
    void storeAllRelevantData(std::stringstream& buffer) const;

    //Guarda true si esta vivo, sino guarda false
    void storeLifeStatus(std::stringstream& buffer) const;


private:
    void _increaseStats();
    void _loadInitialStats(Config::Modifiers& classM, Config::Modifiers& raceM,
                                        const PlayerData& data);
    void _loadGenericStats(Config::Modifiers& classM, Config::Modifiers& raceM,
                                        const PlayerData& data);
};


#endif //ARGENTUM_PLAYERSTATS_H
