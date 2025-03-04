#include "monster.h"
#include "spell.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Constructeur de la classe Monster
Monster::Monster(std::string name, int lvl, float xp, std::vector<int> pos, int f, int w, int e, int wi, int h, int in, unsigned char action, unsigned char move)
    : Entity(lvl, pos, f, w, e, wi, h, in, action, move) {
    xpMonster = xp;
    nom = name;
}

// Méthode pour obtenir l'expérience du monstre
float Monster::getXPMonster() const {
    return xpMonster;
}

// Méthode pour lancer un sort par le monstre
void Monster::SpellThrow(Entity& cible, bool& endRound) {
    Spell spell = spell.SelectSpell(1);
    if (spell.getSpellStat(RANGE) > manhattan_distance(posEntity, cible.getPosEntity())) {
        SpellActive(spell, cible);
        std::cout << "Sort lancé par le monstre !!" << std::endl;
        statActuelles.addStat(ACTION_POINT, -spell.getSpellStat(ACTION_POINT_COST));
    } else {
        endRound = true;
        return;
    }
}

// Instances prédéfinies de monstres
Monster belzebuth = Monster("belzebuth", 1,  15, {},0, 0, 0, 0, 6, 100, 5, 5);

Monster ogrest = Monster("ogrest", 1,  100, {},0, 0, 0, 0, 5, 150, 6, 5);

// Fonction pour sélectionner un monstre en fonction de son code
Monster SelectMonster(int codeMonster) {
    
    switch (codeMonster)
    {
    case BELZEBUTH:
        return belzebuth;

    case OGREST:
        return ogrest;

    default:
        return Monster();
        
    }
}


