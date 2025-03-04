#include "game.h"
#include "spell.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <chrono>
#include <thread>

// Constructeur par défaut de la classe Game
Game::Game() : level(), monstre(rand() % 4 + 2) {

    // Crée les monstres pour ce niveau
    createMonsters(monstre);

    // Initialise le joueur
    alph = Player(1, 1., InitPositionPlayer(), 0, 0, 0, 0, 200, 105, 10, 10);
    level.updateGrid(alph.getPosEntity(), 'A');

    // Initialise le tableau registreMove
    int tailleExterne = monstre.size() + 1;
    registreMove.resize(tailleExterne); // Redimensionne le vecteur externe avec la taille initiale

    // Initialisation des vecteurs internes
    for (int i = 0; i < tailleExterne; ++i) {
        registreMove[i].resize(2); // Redimensionne chaque vecteur interne avec une taille de 2
    }

    // Initialise la timeline
    initTimeLine();

    // Initialise l'indice actuel de la timeline
    idActuel = 0;
}

// Constructeur avec paramètre de la classe Game
Game::Game(int i) : level(), monstre(rand() % 4 + 2) {

    // Crée les monstres pour ce niveau
    createMonsters(monstre);

    // Initialise le joueur à une position donnée
    alph.setPosEntity(InitPositionPlayer());
    level.updateGrid(alph.getPosEntity(), 'A');

    // Initialise le tableau registreMove
    int tailleExterne = monstre.size() + 1;
    registreMove.resize(tailleExterne); // Redimensionne le vecteur externe avec la taille initiale

    // Initialisation des vecteurs internes
    for (int i = 0; i < tailleExterne; ++i) {
        registreMove[i].resize(2); // Redimensionne chaque vecteur interne avec une taille de 2
    }

    // Initialise la timeline
    initTimeLine();

    // Initialise l'indice actuel de la timeline
    idActuel = 0;
}



// Fonction pour mettre à jour la grille de jeu
void Game::updateGrid() {
    std::cout << "vie du joueur : " << alph.statActuelles.getStat(HEALTH) << std::endl;
    std::cout << "point : " << point << std::endl;
    std::cout << "vie du joueur : " << alph.getXpPlayer() << std::endl;
    std::cout << "vie du joueur : " << alph.getXpLvlPlayer() << std::endl;
    std::cout << "lvl du joueur : " << alph.getLvl() << std::endl;
    // for(int i = 0; i < monstre.size(); i ++) std::cout << "vie du monstre" << i <<":" << monstre[i].statActuelles.getStat(HEALTH) << std::endl;

    // Contrôle du tour
    roundControl();
}

// Fonction pour initialiser la timeline du tour
void Game::initTimeLine() {
    timeLine.clear();

    std::map<int, unsigned char> initiative_ID; // Paires initiatives/id triées par initiative (négative pour que la plus haute soit en première)

    // Ajoute l'initiative du joueur à la timeline
    initiative_ID.emplace(-alph.attEntity.getStat(INITIATIVE), 0); // On rentre la paire initiative/ID du joueur

    // Ajoute l'initiative de chaque monstre à la timeline
    for (unsigned char i = 0; i < monstre.size(); ++i) { // On fait de même pour tous les monstres actuels
        initiative_ID.emplace(-monstre[i].attEntity.getStat(INITIATIVE), i + 1);
    }
    // Ajoute les ID à la timeline
    for (const auto &paire : initiative_ID) {

        // Étant donné que les std::map sont triées par la 1ere valeur on récupère l'indice et on le rentre dans timeLine
        timeLine.push_back(paire.second);
    }
}


// Fonction pour gérer le tour du joueur
void Game::playerRound(unsigned char& id) {

    std::vector<int> playerPos = alph.getPosEntity();
    level.updateGrid(playerPos, 'A');

    // Si une case est sélectionnée, déplacer le joueur
    if(selectTile == true ){
        registreMove[0].push_back(playerPos);
        if(registreMove[0].size() > 4){
            if(registreMove[0][registreMove[0].size() -3 ] == alph.getPosEntity()) selectTile = false;
        }
        alph.pathFindingPlayer(playerPos, playerMove, level.grid);

        alph.setPosEntity(playerPos);
        level.updateGrid(playerPos, 'A');
        if(playerPos[0] == playerMove[0] && playerPos[1] == playerMove[1]) selectTile = false;
    }

    // Si un monstre est sélectionné, lancer un sort
    if(select_monster){
        std::cout << "dedans copain";
        alph.SpellThrow(monstre[indexMonster], spellChoise);
        select_monster = false;
        select_spell = false;
    }

    // Gestion des points de mouvement
    int playerX = playerPos[0];
    int playerY = playerPos[1];
    int movementPoints = alph.statActuelles.getStat(MOVEMENT_POINT);

    // Fin du tour
    if (endRound) {
        idActuel ++;
        alph.resetPoint();
        endRound = false;
    }
}

// Fonction pour gérer le tour des monstres
void Game::monsterRound(Monster& monster, unsigned char& id) {
    // Vérifie si le monstre est mort
    if(monster.Death()){
        idActuel++;
        return;
    }

    Spell spell;

    std::vector<int> monsterPos = monster.getPosEntity();
    unsigned char movementPoints = monster.statActuelles.getStat(MOVEMENT_POINT);
    unsigned char actionPoints = monster.statActuelles.getStat(ACTION_POINT);

    bool endRound = false;

    std::cout << monster.statActuelles.getStat(MOVEMENT_POINT) << std::endl;
    // Déplacement du monstre s'il a des points de mouvement
    if(monster.statActuelles.getStat(MOVEMENT_POINT) > 0){
        /* Ancien pathfinding
        monster.pathFinding(monsterPos, alph.getPosEntity(), level.grid);
        monster.setPosEntity(monsterPos);
        level.updateGrid(monsterPos, 'M' + id);

        std::cout << (int) id <<std::endl;

        registreMove[id - 1].push_back(monsterPos);
        */
        monster.pathFinding(monsterPos, alph.getPosEntity(), level.grid);

        level.updateGrid(monsterPos, 'M' + id);

        registreMove[id - 1].push_back(monsterPos);

        std::vector<std::vector<int>> pif =registreMove[id - 1];

    }

    // Décrémente les points de mouvement du monstre
    monster.statActuelles.addStat(MOVEMENT_POINT, -1);

    std::cout << monster.statActuelles.getStat(ACTION_POINT) << std::endl;
    // Lance un sort si le monstre n'a plus de points de mouvement
    if(monster.statActuelles.getStat(MOVEMENT_POINT) == 0) monster.SpellThrow(alph, endRound);


    //std::cout << monstre.statActuelles.getStat(MOVEMENT_POINT) << std::endl;
    // Fin du tour du monstre
    if((monster.statActuelles.getStat(ACTION_POINT) == 0 || endRound) && monster.statActuelles.getStat(MOVEMENT_POINT) == 0  ) {

        idActuel++;
        monster.resetPoint();

    }
}

// Fonction de contrôle du tour
void Game::roundControl() {

    unsigned char id = timeLine[idActuel];

    // Si c'est le tour du joueur
    if (id == 0) {
        std::cout << "Tour du joueur" << std::endl;

        //idActuel++;
        playerRound(id);
        for (int i = 0; i < monstre.size(); ++i) {
            monstre[i].tabDeplacement.clear();
            monstre[i].deplacementId = 0;
        }
    }
    // Si c'est le tour d'un monstre
    else{
        std::cout << "Tour du monstres" << (int) id << std::endl;

        monsterRound(monstre[id - 1], id);

    }

    // Si tous les monstres sont passés, réinitialiser l'indice actuel
    if (idActuel >= timeLine.size()) idActuel = 0;
    //if(alph.Death()){
    std::cout << (int) id << std::endl;
    endGame();
    //}

}

// Fonction pour initialiser la position du joueur sur la carte
std::vector<int> Game::InitPositionPlayer() {
    int gridSizeX = level.grid.size();
    int gridSizeY = level.grid[0].size();

    std::vector<int> newPos(2);
    int attempts = 0;

    int centralMonsterX = monstre[0].getPosEntity()[0];
    int centralMonsterY = monstre[1].getPosEntity()[1];

    // Génère une position aléatoire pour le joueur
    do {
        newPos[0] = rand() % gridSizeX;
        newPos[1] = rand() % gridSizeY;
        attempts++;

        if (attempts > 100) {
            std::cerr << "Erreur" << std::endl;
            exit(EXIT_FAILURE);
        }
    } while (level.grid[newPos[0]][newPos[1]] == '1' ||
             abs(newPos[0] - centralMonsterX) <= 5 ||
             abs(newPos[1] - centralMonsterY) <= 5);

    return newPos; // Retourne la nouvelle position
}

// Fonction pour initialiser la position d'un monstre sur la carte
void Game::InitPositionMonster(Monster& monstre) {
    int gridSizeX = level.grid.size();
    int gridSizeY = level.grid[0].size();

    std::vector<int> newPos(2);
    int attempts = 0;

    // Génère une position aléatoire pour le monstre
    do {
        newPos[0] = rand() % gridSizeX;
        newPos[1] = rand() % gridSizeY;
        attempts++;

        if (attempts > 100) {
            std::cerr << "Erreur" << std::endl;
            exit(EXIT_FAILURE);
        }
    } while (level.grid[newPos[0]][newPos[1]] == '1');

    monstre.setPosEntity(newPos);
}

// Fonction pour changer de carte
void Game::Changement_Map(Level& level){
    lvl++;
    Level new_level;
    level = new_level;
    monstre = std::vector<Monster>(rand() % 4 + 2);
    createMonsters(monstre);

    alph.setPosEntity(InitPositionPlayer());
    level.updateGrid(alph.getPosEntity(), 'A');

    int tailleExterne = monstre.size() + 1;
    registreMove.resize(tailleExterne); // Redimensionne le vecteur externe avec la taille initiale

    // Initialisation des vecteurs internes
    for (int i = 0; i < tailleExterne; ++i) {
        registreMove[i].resize(2); // Redimensionne chaque vecteur interne avec une taille de 2
    }

    // Initialisation de la timeline
    initTimeLine();

    // Initialisation de l'indice actuel de la timeline
    idActuel = 0;

}

// Fonction de fin de jeu
void Game::endGame() {
    // Vérification si tous les monstres ont plus de vie
    bool tousMorts = true;
    for (const auto& monstre : monstre) {
        if (!monstre.Death()) {
            tousMorts = false;
            break;
        }
    }
    // Si le joueur est mort, terminer le jeu
    if(alph.Death()) exit(EXIT_FAILURE); // mettre ce qu'on veut dedans


    // Si tous les monstres sont morts, le joueur gagne
    if (tousMorts) {
        for(int i = 0; i < monstre.size(); i++) alph.MonterLvl(monstre[i], monterLvl, point);

        win = true;
    }
}

// Fonction pour créer les monstres du niveau
void Game::createMonsters(std::vector<Monster>& monstre) {
    for(int i = 0; i < monstre.size(); i++) {
        int type;
        int randomNum = rand() % 10; // Génère un nombre aléatoire entre 0 et 9

        // Si le nombre aléatoire est inférieur à 7 (70% de chance), crée un monstre de type BELZEBUTH
        if (randomNum < 7) {
            type = BELZEBUTH; // 70% de chance de créer un Belzebuth
        } else {
            type = OGREST; // 30% de chance de créer un Ogrest
        }

        // Initialise le monstre avec le type sélectionné
        monstre[i] = Monster(SelectMonster(type));
        monstre[i].attEntity.StatUp(std::floor(std::pow(1.1, lvl)));
        monstre[i].statActuelles.StatUp(std::floor(std::pow(1.1, lvl)));

        // Définit l'initiative du monstre en fonction de son indice
        monstre[i].attEntity.setStat(INITIATIVE, i);

        // Initialise la position du monstre sur la grille
        InitPositionMonster(monstre[i]);
        level.updateGrid(monstre[i].getPosEntity(), 'N' + i);
    }
    // Augmente les statistiques du premier monstre tous les 10 niveaux
    if (lvl % 10 == 0) {
        monstre[0].attEntity.StatUp(4.);
        monstre[0].statActuelles.StatUp(4.);
    }
}