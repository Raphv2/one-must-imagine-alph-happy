#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>

/**
 * @brief Groupement d'obstacle
 * @param width Largeur
 * @param height Hauteur
*/

class Block {
private:
    int width;
    int height;

public:

    /**
     * @brief Constructeur par valeur
     * @param w Largeur 
     * @param h Hauteur
    */
    Block(int w, int h);

    /**
     * @brief Getter 
     * @return Retourne la largeur
    */
    int getWidth() const;
    

    /**
     * @brief Getter 
     * @return Retourne la hauteur
    */
    int getHeight() const;
};

class Obstacle {
private:
    friend class Level;
    std::vector<Block> blocks;

public:
    Obstacle();
    void addBlock(int width, int height);
};

#endif // OBSTACLE_H