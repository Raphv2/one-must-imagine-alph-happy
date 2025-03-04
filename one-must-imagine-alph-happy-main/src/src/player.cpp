#include "player.h"
#include <cmath>
#include <iostream>
#include "entity.h"
#include "spell.h"
#include "monster.h"

// Constructeur de la classe Player
Player::Player(int lvl, float xp, std::vector<int> pos, int f, int w, int e, int wi, int h, int in, unsigned char action, unsigned char move) : Entity(lvl, pos, f, w, e, wi, h, in, action, move){
    
    xpPlayer = xp;
    xpLvlPlayer = 100;
   
}

// Méthode pour définir l'XP nécessaire pour atteindre le prochain niveau du joueur
float Player::setXpLvlPlayer(){
    int lvlPlayer = getLvl();

    xpLvlPlayer +=  100 * lvlPlayer;
    return xpLvlPlayer;
}

// Méthode pour faire monter de niveau le joueur
void Player::MonterLvl(const Monster& monstre, bool& monterLvl, int&point) {
    // Ajout de l'XP du monstre mort au joueur
    if (monstre.Death()) {
        xpPlayer += monstre.getXPMonster();
    }

    // Vérification si le joueur doit monter de niveau
    while(xpPlayer >= xpLvlPlayer) {
        lvlEntity++;
        statActuelles.StatUp(2.);
        attEntity.StatUp(2.);
        monterLvl = true;
        // Réduction de l'XP du joueur par le seuil requis pour le niveau actuel
        xpPlayer -= xpLvlPlayer;
        
        // Augmentation du niveau du joueur
        lvlEntity++;
        
        point++;
        // Calcul du nouveau seuil XP pour le prochain niveau
        xpLvlPlayer = setXpLvlPlayer();
    }
}


// Méthode pour lancer un sort sur une entité cible si celle-ci est à portée
void Player::SpellThrow(Entity& cible, unsigned char spellChoice) {
    // Sélectionne le sort à l'aide du choix de l'utilisateur
    Spell spell = spell.SelectSpell(FIREWORK);
    // Vérifie si la distance entre le joueur et la cible est inférieure à la portée du sort
    if (spell.getSpellStat(RANGE) > manhattan_distance(posEntity, cible.getPosEntity())) {
        // Active le sort sur la cible
        SpellActive(spell, cible);
        // Affiche un message indiquant que le sort a été lancé par le joueur
        std::cout << "Sort lancé par le joueur !!" << std::endl;
        // Réduit les points d'action du joueur en fonction du coût en points d'action du sort
        statActuelles.addStat(ACTION_POINT, -spell.getSpellStat(ACTION_POINT_COST));
    } else {
        // Si la cible est hors de portée, la fonction se termine sans effectuer d'action
        return;
    }
}

