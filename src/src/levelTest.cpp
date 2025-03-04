#include "levelTest.h"
#include <iostream>
#include <cstdlib> 
#include <ctime> 

// Constructeur par défaut de la classe Level
Level::Level() {
    srand(time(nullptr));

    // Génère une taille aléatoire pour la grille
    int gridSizeX = rand() % 20 + 10; 
    int gridSizeY = rand() % 10 + 10; 
    width = gridSizeX;
    height = gridSizeY;
    int bigBlock = rand() % 2 + 2;
    int mediumBlock = rand() % 2 +2;
    int smallBlock = rand() % 5 + 5;

    int size = bigBlock + mediumBlock + smallBlock;

    // Redimensionne la grille et crée un vecteur d'obstacles
    grid.resize(gridSizeX, std::vector<char>(gridSizeY, 0));
    std::vector<Obstacle> obstacle(size);

    // Génère et place des obstacles aléatoires dans la grille
    RamdomObstacle(obstacle, bigBlock, mediumBlock, smallBlock,  gridSizeX, gridSizeY);
}

// Met à jour la grille avec une nouvelle valeur à une position donnée
void Level::updateGrid(std::vector<int> pos, char value) {
    if (value != value) {
        grid[pos[0]][pos[1]] = value;
    } else {
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (i == pos[0] && j == pos[1]) {
                    grid[i][j] = value;
                } else if (grid[i][j] == value) {
                    grid[i][j] = 0;
                }
            }
        }
    }
}

// Affiche la grille
void Level::displayGrid() {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            char cell = grid[i][j];
            if (cell == 0) {
                std::cout << " " << " ";
            } else {
                std::cout << cell << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Place un obstacle dans la grille à une position donnée
void Level::placeObstacle(const Obstacle& obstacle ,int startX, int startY) {

    int endX = startX + obstacle.blocks[0].getWidth() - 1;
    int endY = startY + obstacle.blocks[0].getHeight() - 1;

    if (endX >= 0 && endX < grid.size() && endY >= 0 && endY < grid[0].size()) {
        // Parcourt chaque bloc de l'obstacle et le place dans la grille
        for (const auto& block : obstacle.blocks) {
            for (int i = 0; i < block.getWidth(); ++i) {
                for (int j = 0; j < block.getHeight(); ++j) {
                    grid[startX + i][startY + j] = '1'; 
                }
            }
        }
    } else {
        std::cerr << "Impossible de placer l'obstacle en dehors de la grille." << std::endl;
    }
}

// Génère et place des obstacles aléatoires dans la grille
void Level::RamdomObstacle(std::vector<Obstacle>& obstacles, int bigBlock, int mediumBlock, int smallBlock, int gridSizeX, int gridSizeY) {
    // Génère et place des obstacles de grande taille
    for (int i = 0; i < bigBlock; ++i) {
        Obstacle bigObstacle;
        bigObstacle.addBlock(3, 3); 
        placeObstacle(bigObstacle, rand() % (gridSizeX - 2), rand() % (gridSizeY - 2));
        obstacles.push_back(bigObstacle);
    }

    // Génère et place des obstacles de taille moyenne
    for (int i = 0; i < mediumBlock; ++i) {
        Obstacle mediumObstacle;
        mediumObstacle.addBlock(2, 2); 
        placeObstacle(mediumObstacle, rand() % (gridSizeX - 2), rand() % (gridSizeY - 2));
        obstacles.push_back(mediumObstacle);
    }


    // Génère et place des obstacles de petite taille
    for (int i = 0; i < smallBlock; ++i) {
        Obstacle smallObstacle;
        smallObstacle.addBlock(1, 1); 
        placeObstacle(smallObstacle, rand() % (gridSizeX - 2), rand() % (gridSizeY - 2));
        obstacles.push_back(smallObstacle);
    }
}
