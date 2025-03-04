#include "consoleDisplay.h"
#include "game.h"
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

// Méthode pour initialiser le jeu de test
void ConsoleDisplay::initGameTest() {
    jeu = Game();
}

// Méthode pour tester les fonctionnalités du jeu
void ConsoleDisplay::testFonctionnalites() {
    //level.displayGrid();
    // tests randoms
    std::cout << "déplacement du joueur" << std::endl;
    alph.Move({9, 9}, level.grid);
    //updateGrid();
    std::cout << "lancement de sort" << std::endl;
    //alph.SpellThrow(monstre[0].getEntity());
    //updateGrid();
}

// Méthode pour afficher la grille du jeu dans la console
void ConsoleDisplay::displayGrid() {
    for (int i = 0; i < jeu.level.grid.size(); ++i) {
        for (int j = 0; j < jeu.level.grid[i].size(); ++j) {
            char cell = jeu.level.grid[i][j];
            if (cell == 0) {
                std::cout << " " << " ";
            } else {
                std::cout << cell << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Méthode pour mettre à jour l'affichage du jeu dans la console
void ConsoleDisplay::update() {

    initGameTest(); // Initialise le jeu de test
    bool stop = false; // Variable pour contrôler l'arrêt du jeu
    while(!stop){

        
        
        //Mise à jour de l'état du jeu;
        jeu.updateGrid(); // Appelle la méthode updateGrid de l'objet jeu pour mettre à jour la grille du niveau
        
        // Affichage de la grille mise à jour dans la console
        displayGrid(); // Appelle la méthode displayGrid pour afficher la grille dans la console

        //endGame(stop); // Méthode pour vérifier si le jeu est terminé et mettre à jour la variable stop

       
    }
}