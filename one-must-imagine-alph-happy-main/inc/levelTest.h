#ifndef LEVELTEST_H
#define LEVELTEST_H

#include <vector>
#include "obstacle.h"


/**
 * @brief Class décrivant la carte de jeu d'un combat
 * @param grid Tableau 2D contenant la position des obstacles, du joueur et des monstres
 * @param obstacles Tableau d'obstacles
*/

class Level {
private:
    friend class Game;
    friend class ConsoleDisplay;
    friend class Scene;
    std::vector<std::vector<char>> grid;
    std::vector<Obstacle> obstacles;
    int width;
    int height;

public:

    /**
     * @brief Constructeur par défault, initialise un carte aléatoire
    */
    Level();

    /**
     * @brief Mise à jour de la grille de jeu
     * @param pos Position à modifier
     * @param value Valeur à insérer
    */
    void updateGrid(std::vector<int> pos, char value);

    /**
     * @brief Affichage de la grille ??? A MODIFIER / SUPPRIMER
    */
    void displayGrid();

    /**
     * @brief Place un obstacle donné à une position donnée
     * @param obstacle Un obstacle
     * @param startX Position de départ en x
     * @param startY Position de départ en y  
    */
    void placeObstacle(const Obstacle& obstacle, int startX, int startY);

    /**
     * @brief Place de manière aléatoire un nombre d'obstacle passé en paramètre
     * @param obstacle Tableau d'obstacle passé en donnée/résultat
     * @param bigBlock Nombre d'obstacles de forme bigBlock
     * @param mediumBlock Nombre d'obstacles de forme mediumBlock
     * @param smallBlock Nombre d'obstacles de forme smallBlock
     * @param gridSizeX Taille de la grille en x
     * @param gridSizeY Taille de la grille en y
    */
    void RamdomObstacle(std::vector<Obstacle>& obstacle, int bigBlock, int mediumBlock, int smallBlock, int gridSizeX, int gridSizeY);
};

#endif // LEVELTEST_H
