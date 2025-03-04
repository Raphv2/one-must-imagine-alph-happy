#ifndef _MONSTER_H
#define _MONSTER_H

#include "spell.h"
#include "attribute.h"
#include "entity.h"

#include <vector>

enum listMonster {
    DEFAULTMONSTER = 0,
    BELZEBUTH = 1,
    OGREST = 2
};

/**
 * @brief Class décrivant un monstre, entité non jouable. Utilise l'hérité avec la class Entity
 * @param xpMonster Quantité de point d'expérience donnée au joueur à sa mort
*/

class Monster: public Entity {
private:
    float xpMonster;
    std::string nom;
public:

    /**
     * @brief Constructeur par défault
    */
    Monster() : Entity(0, {}, 0, 0, 0, 0, 0, 0, 0, 0) {
        xpMonster = 0;
        nom = "no name";
    }

    float getXPMonster() const;

    /**
     * @brief Constructeur par valeur (simple)
     * @param xp La nouvelle valeur de xpMonster
    */
    Monster(float xp, std::string name) : Entity(0, {}, 0, 0, 0, 0, 0, 0, 0, 0) {
        xpMonster = xp;
        nom = name;
    }

    /**
     * @brief Constructeur par valeur (détaillé)
     * @param lvl Valeur utilisée dans le constructeur par valeur de la class Entity
     * @param xp Nouvelle valeur de xpMonster
     * @param pos Valeur utilisée dans le constructeur par valeur de la class Entity
     * @param f Valeur utilisée dans le constructeur par valeur de la class Entity
     * @param w Valeur utilisée dans le constructeur par valeur de la class Entity
     * @param e Valeur utilisée dans le constructeur par valeur de la class Entity
     * @param wi Valeur utilisée dans le constructeur par valeur de la class Entity
     * @param h Valeur utilisée dans le constructeur par valeur de la class Entity
     * @param in Valeur utilisée dans le constructeur par valeur de la class Entity
     * @param action Valeur utilisée dans le constructeur par valeur de la class Entity
     * @param move Valeur utilisée dans le constructeur par valeur de la class Entity
    */
    Monster(std::string name, int lvl, float xp, std::vector<int> pos, int f, int w, int e, int wi, int h, int in, unsigned char action, unsigned char move);

    /**
     * @brief Tente de lancer un sort sur le joueur si cela est possible
     * @param cible Entité visée, modifiée si le sort est effectivement lancé
     * @param endRound Booléen indiquant si le sort est lancé ou non ??? A MODIFIER
    */
    void SpellThrow(Entity& cible, bool &endRound);

    /**
     * ??? PAS IMPLEMENTER
    */
    void DeathMonster();

    std::string getName() const { return nom; }


};

Monster SelectMonster(int codeMonster);

#endif //_MONSTER_H