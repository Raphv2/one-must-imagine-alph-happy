#ifndef _CONSOLEDISPLAY_H
#define _CONSOLEDISPLAY_H

#include "game.h"
#include "scene.h"

/**
 * @brief Cette classe sert à l'affichage console
 * @param jeu Instance de la classe Game
*/

class ConsoleDisplay : public Game{
private:
    Game jeu;
public:

    /**
     * @brief Initialise le membre jeu avec le constructeur Game()
    */
    void initGameTest();

    /**
     * @brief Test de fonctionnalités
    */
    void testFonctionnalites();

    /**
     * @brief Affichage console de la carte de jeu
    */
    void displayGrid();

    /**
     * @brief La fonction qui gère l'affichage console de notre jeu
    */
    void update();
};

#endif //_CONSOLEDISPLAY_H
