#include "obstacle.h"
#include <iostream>

// Définition du constructeur de la classe Block
Block::Block(int w, int h) : width(w), height(h) {}

// Méthode pour obtenir la largeur du bloc
int Block::getWidth() const { return width; }

// Méthode pour obtenir la hauteur du bloc
int Block::getHeight() const { return height; }

// Constructeur par défaut de la classe Obstacle
Obstacle::Obstacle() {}

// Méthode pour ajouter un bloc à l'obstacle
void Obstacle::addBlock(int width, int height) {
    Block block(width, height);
    blocks.push_back(block);
}
