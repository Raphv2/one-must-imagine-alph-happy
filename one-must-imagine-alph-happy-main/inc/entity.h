// entity.h
#ifndef ENTITY_H
#define ENTITY_H

#include "attribute.h"
#include "spell.h"
#include <vector>

/**
 * @brief Cette classe décrit une entité, qu'il s'agisse d'un joueur ou d'un monstre, et toutes les actions communes aux deux
 * @param attEntity Les attributs hors combat de l'entité
 * @param statActuelles Les attributs en combat de l'entité
 * @param posEntity La position de l'entité
 * @param lvlEntity Le niveau de l'entité
 * @param tabDeplacement La liste des deplacements a effectuer
 * @param deplacementId L'indice de la prochaine position a effectuer
*/

class Entity {
public:

    /**
     * @brief Constructeur par défaut
    */
    Entity();

    /**
     * @brief Constructeur par valeur
     * @param lvl Valeur du niveau de l'entité
     * @param pos Position de l'entité
     */
    Entity(int lvl, std::vector<int> pos, int f, int w, int e, int wi, int h, int in, unsigned char action, unsigned char move);

    /**
    * @brief Renvoie la position de l'entité.
    *
    * @return std::vector<int> Position de l'entité.
    */
    std::vector<int> getPosEntity() const;

    /**
     * @brief Définit la position de l'entité.
     *
     * @param newPos Nouvelle position de l'entité.
     * @return std::vector<int> Position mise à jour de l'entité.
     */
    std::vector<int> setPosEntity(std::vector<int> newPos);

    /**
     * @brief Vérifie si l'entité a suffisamment de points de mouvement pour effectuer une action.
     *
     * @param move Points de mouvement nécessaires pour l'action.
     * @return true Si l'entité a suffisamment de points de mouvement.
     * @return false Sinon.
     */
    bool AssezPointMove(int move);

    /**
     * @brief Vérifie si l'entité a suffisamment de points d'action pour lancer un sort.
     *
     * @param spellThrow Sort à lancer.
     * @return true Si l'entité a suffisamment de points d'action.
     * @return false Sinon.
     */
    bool AssezPointAction(Spell spellThrow);

    /**
     * @brief Fonction de détection de ligne de vue entre deux positions.
     * @param test Booléen pour indiquer si la ligne de vue est valide.
     * @param posCible Position ciblée, modifiée par la position du premier obstacle rencontré si c'est le cas
     * @param grid Grille de jeu.
    */

    void lineOfSight(bool & test, std::vector<int> & posCible, const std::vector<std::vector<char>> & grid);

    /**
     * @brief Calcule la distance de Manhattan entre deux positions.
     *
     * @param start Position de départ.
     * @param end Position d'arrivée.
     * @return int Distance de Manhattan.
     */
    float manhattan_distance(std::vector<int> start, std::vector<int> end);

    /**
     * @brief Vérifie si une entité est touchée par un sort lancé par une autre entité
     * @param otherEntity Entité lançant le sort
     * @param spellEntity Sort lancé
     * @return true si l'entité est touchée, sinon false
     */
    bool TouchEntity(Entity& otherEntity, Spell spellEntity);

    /**
     * @brief Déplace l'entité vers une nouvelle position sur la carte
     * @param posMove Nouvelle position
     * @param map Carte représentant l'environnement
     */
    void Move(std::vector<int> posMove, std::vector<std::vector<char>>& map);

    /**
     * @brief Active un sort sur une cible et calcule les dégâts suivant le type élémentaire
     * @param spellThrow Sort à lancer
     * @param cible Cible du sort
     */
    void SpellActive(Spell spellThrow, Entity& cible);

    /**
     * @brief Inflige des dégâts à l'entité après application des résistances
     * @param damage Les dégâts infligés
     * @param elementType Type élémentaire des dégâts
     */
    void TakeDamage(int damage, int elementType);

    /**
     * @brief Vérifie si l'entité est morte
     * @return true si l'entité est morte, sinon false
     */
    bool Death() const;

    /**
     * @brief Obtient le niveau de l'entité
     * @return Le niveau de l'entité
     */
    int getLvl() const;

    void setLvl(int level){ lvlEntity = level;}

    /**
     * @brief Réinitialise les points de l'entité
     */
    void resetPoint();

    /**
     * @brief Trouve un chemin pour déplacer l'entité (monstre) vers une position donnée
     * @param monster Position actuelle du monstre (modifiable pour mettre à jour la position)
     * @param posEntity Position de l'entité (joueur)
     * @param map Carte représentant l'environnement
     */
    void pathFinding(std::vector<int>& monster, const std::vector<int>& posEntity, std::vector<std::vector<char>>& map);

    /**
     * @brief Trouve un chemin pour déplacer le joueur vers une position donnée
     * @param monster Position actuelle du monstre
     * @param posEntity Position du joueur (modifiable pour mettre à jour la position)
     * @param map Carte représentant l'environnement
     */
    void pathFindingPlayer(std::vector<int>& monster, const std::vector<int>& posEntity, std::vector<std::vector<char>>& map);

    /**
     * @brief Initialise les attributs de l'entité.
     *
     */
    void initAttribute(int f, int w, int e, int wi, int h, int in, unsigned char action, unsigned char move);

    /**
     * @brief Calcule la distance minimum entre une position donnée et l'ensemble des positions du tableau donné
     * @param pos Position
     * @param tab Tableau de position
     * @return L'indice de l'élément du tableau le plus proche de pos
    */
    int distanceManMin (std::vector<int> pos, std::vector<std::vector<int>> tab);

    /**
     * @brief Fonction cherchant un groupe de murs collés entre eux à partir d'une position de mur initiale
     * @param wall Position de mur initiale
     * @param grid Carte de jeu contenant les obstacles
    */
    void findWallGroup (std::vector<int> wall, const std::vector<std::vector<char>> &grid, std::vector<std::vector<int>> *result);

    /**
     * @brief Renvoie la position de la case libre pour contourner le mur
     * @param walls Enveloppe convexe des murs à éviter
     * @param posPlayer Position du joueur
     * @param map Tableau de cases du niveau
    */
    std::vector<int> avoidWall (const std::vector<std::vector<int>> &walls, const std::vector<int> &posPlayer, std::vector<std::vector<char>> &map);

    /**
     * @brief Remplit un tableau avec toutes les cases a parcourir pour arriver a la case donnee
     * @param tab Le tableau de position resultat
     * @param pos Position a atteindre
     * @param grid Carte du niveau actuel
    */
    void fillTabDeplacement (std::vector<int> pos, std::vector<std::vector<char>> grid);

private:

    
    
    int deplacementId;
    std::vector<std::vector<int>> tabDeplacement;
    
    Attribute attEntity; // Attributs hors combat de l'entité
    Attribute statActuelles; // Attributs en combat de l'entité
    std::vector<int> posEntity; // Position de l'entité
    int lvlEntity; // Niveau de l'entité
    
    friend class Monster;
    friend class Player;
    friend class Game;
    friend class ConsoleDisplay;
    friend class Scene;
    friend class WidgetPoint;
};

#endif // ENTITY_H
