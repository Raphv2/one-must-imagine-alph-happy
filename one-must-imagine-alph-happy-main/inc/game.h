#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "monster.h"
#include "levelTest.h"
#include <cmath>

/**
 * @brief Classe permettant de gérer le fonctionnement du jeu
 * @param level Carte actuelle du jeu
 * @param alph Informations concernant le joueur
 * @param monstre Tableau dynamique des monstres que le joueur est en train d'affronter
 * @param timeLine Tableau contenant l'ordre de déroulement des tours
 * @param switchRound Booléen permettant de savoir si l'on doit changer de tour
 */

class Game {
private:
    friend class ConsoleDisplay;
    friend class Scene;


    Level level; // Carte actuelle du jeu
    Player alph; // Informations concernant le joueur
    std::vector<Monster> monstre; // Tableau dynamique des monstres que le joueur est en train d'affronter
    std::vector<int> playerMove;

    std::vector<unsigned char> timeLine; // Tableau contenant l'ordre de déroulement des tours
    std::vector<std::vector<std::vector<int>>> registreMove;

    int lvl = 0;

    int indexMonster;

    /**
     @param idActuel Indice acuel de timeLine
     */
    unsigned char idActuel; // Indice actuel de timeLine
    bool selectTile = false;
    bool win = false;
    bool lose = false;
    bool endRound = false;
    bool select_spell = false;
    bool select_monster = false;
    bool monterLvl = false;
    int spellChoise = 0;

    int point = 0;


public:

    /**
     * @brief Constructeur par défaut
    */
    Game();

    /**
     * @brief Constructeur avec paramètre
     * @param i Entier utilisé pour initialiser l'objet Game
     */
    Game(int i);

    /**
     * @brief Test de certaines fonctionnalités
    */
    void testFonctionnalites();

    /**
     * @brief Mise à jour de la carte de jeu (level.grid)
    */
    void updateGrid();


    /**
     * @brief Initialisation de timeLine, tableau contenant l'indice des entités qui joue dans le combat 
    */
    void initTimeLine();

    /**
     * @brief Actions réalisée par le joueur pendant son tour de jeu
     * @param id ??? A MODIFIER J'AI PAS COMPRIS CE QUE C'ETAIT
    */
    void playerRound(unsigned  char& id);

    /**
     * @brief Actions réalisées par un monstre pendant son tour de jeu
     * @param monstre Tableau des monstres ??? C'EST PAS INUTILE VU QU'ON EST DANS GAME ?
     * @param id Indice du monstre dans le tableau de monstres
    */
    void monsterRound(Monster& monster, unsigned  char& id);

    /**
     * @brief Gestion des tours de jeu, en fonction de timeLine
     * @param id ??? INUTILE NON ?
    */
    void roundControl();

    /**
     * @brief Initialise la postion du joueur en fonction de la postion moyenne des monstres
     * @return La position du joueur après calcul 
    */
    std::vector<int> InitPositionPlayer();

    /**
     * @brief Positionne un monstre de manière aléatoire
     * @return La position du monstre après calcul 
    */
    void InitPositionMonster(Monster& monstre);

    /**
     * @brief Renvoie l'identifiant actuel
     * @return L'identifiant actuel
     */
    unsigned char getIdActuel() const {return idActuel;}

    /**
     * @brief Change la carte de jeu
     * @param level Référence vers l'objet Level représentant la carte de jeu à changer
     */
    void Changement_Map(Level& level);

    /**
     * @brief Met fin au jeu
     */
    void endGame();

    /**
     * @brief Crée des monstres
     * @param monstre Vecteur contenant les objets Monster à créer
     */
    void createMonsters(std::vector<Monster>& monstre);

    /**
    * @brief Initialise le jeu
    */
    void init();
};

#endif // GAME_H
