#ifndef _PLAYER_H
#define _PLAYER_H

#include "spell.h"
#include "attribute.h"
#include "entity.h"
#include <vector>
#include "monster.h"

class Player : public Entity{  // la classe Player hérite de la classe Entity
private:

    float xpPlayer;
    float xpLvlPlayer;
    

public:
    Player() : Entity(0, {}, 0, 0, 0, 0, 0, 0, 0, 0) {
        xpPlayer = 0.0f;
        xpLvlPlayer = 0.0f;
    }
    Player(int lvl, float xp, std::vector<int> pos, int f, int w, int e, int wi, int h, int in, unsigned char action, unsigned char move);
    float setXpLvlPlayer();
    void MonterLvl(const Monster& monstre, bool& monterLvl, int& point);
    void SpellThrow(Entity &cible, unsigned char spellChoice);

    float getXpPlayer() const { return xpPlayer; } 
    float getXpLvlPlayer() const { return xpLvlPlayer; } 
};

#endif //_PLAYER_H