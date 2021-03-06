//
// Created by agustin on 14/6/20.
//

#ifndef ARGENTUM_PLAYERSTATS_H
#define ARGENTUM_PLAYERSTATS_H

#include <sstream>
#include <cstdint>
#include "../../libs/GameEnums.h"
#include "../Server/PlayerData.hpp"
#include "../Config/ConfigFileReader.h"
#include "../Config/Configuration.h"

class EntityTests;
class MapTests;
class Minichat;

class PlayerStats {
private:
    bool isMeditating{};
    double timeElapsedLife{};
    double timeElapsedMana{};

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

    const double TIME_FOR_RECOVERY{Configuration::getInstance().configPlayerRecoveryTime()*1000};

    friend EntityTests;
    friend MapTests;

public:
    //Construye el PlayerStats utilizando los datos almacenados en la instancia de PlayerData
    //Esta pensado para cargar los stats que tuvo un jugador antes de desconectarse
    explicit PlayerStats(const PlayerData& data);

    //Retorna el danio base que logro hacer el arma del player para el ataque
    int getTotalDamage(int weaponDamage) const;

    //Retorna el level actual del player
    unsigned int getLevel() const;

    //Aumenta la xp del player, retorna true si subio de nivel, false en otro caso
    //Un player nunca puede subir de a mas de un nivel ya que la experiencia de
    //sobra es descartada
    bool increaseExperience(unsigned int _experience);

    //Modifica la vida del player acorde al danio/curacion ocasionados
    //Retorna el pair(danio total recibido, pudo esquivar)
    //Concatena en attackedMessage prefijos para el mensaje de ataque segun el
    //resultado
    std::pair<int, bool> modifyLife(int damage, unsigned int attackerLevel, unsigned int defense,
                   bool isAPlayer, std::string& attackedMessage);

    //Retorna la maxima vida que puede tener el player dados sus stats actuales
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

    //Setea el mana y la vida actual en sus valores maximos
    void restore();

    //Guarda experiencia, experiencia para proximo nivel, nivel, mana actual, mana maximo,
    //vida, vida maxima y si esta vivo (true) o muerto (false) en buffer
    void storeAllRelevantData(std::stringstream& buffer) const;

    //Guarda true si esta vivo, sino guarda false en buffer
    void storeLifeStatus(std::stringstream& buffer) const;

    //Almacena las stats del player en pData, se usa para el backup del archivo
    void getData(PlayerData& pData) const;

    //Intenta consumir amount cantidad de mana, retorna true si lo pudo hacer,
    //sino retorna false
    bool consumeMana(unsigned int amount);

private:
    void _increaseStats();
    void _loadInitialStats(Config::Modifiers& classM, Config::Modifiers& raceM,
                                        const PlayerData& data);
    void _loadGenericStats(Config::Modifiers& classM, Config::Modifiers& raceM,
                                        const PlayerData& data);
};


#endif //ARGENTUM_PLAYERSTATS_H
