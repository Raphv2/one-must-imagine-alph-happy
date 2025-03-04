// entity.cpp
#include "entity.h"
#include "spell.h"
#include "levelTest.h"
#include "calculConvex.h"
#include <iostream>
#include <cmath>

// Constructeur par défaut de la classe Entity
Entity::Entity() {
    initAttribute(0, 0, 0, 0, 0, 0, 0, 0);
    lvlEntity = 0;
    posEntity = {};
}

// Constructeur paramétré de la classe Entity
Entity::Entity(int lvl, std::vector<int> pos, int f, int w, int e, int wi, int h, int in, unsigned char action, unsigned char move) {
    initAttribute(f, w, e, wi, h, in, action, move);
    lvlEntity = lvl;
    posEntity = pos;
}

// Méthode pour obtenir la position de l'entité
std::vector<int> Entity::getPosEntity() const {
    return posEntity;
}

// Méthode pour définir la position de l'entité
std::vector<int> Entity::setPosEntity(std::vector<int> newPos) {
    posEntity = newPos;
    return posEntity;
}

// Méthode d'initialisation des attributs de l'entité
void Entity::initAttribute(int f, int w, int e, int wi, int h, int in, unsigned char action, unsigned char move) {
    // Initialise les attributs et statistiques de l'entité
    attEntity = Attribute(f, w, e, wi, h, in, action, move);
    statActuelles = Attribute(attEntity.getAttributes());
}

// Méthode pour vérifier si l'entité a suffisamment de points de mouvement
bool Entity::AssezPointMove(int move) {
    return (statActuelles.getStat(MOVEMENT_POINT) >= move && statActuelles.getStat(MOVEMENT_POINT) != 0);
}

// Méthode pour vérifier si l'entité a suffisamment de points d'action pour lancer un sort
bool Entity::AssezPointAction(Spell spellThrow) {
    return statActuelles.getStat(ACTION_POINT) >= spellThrow.actionPointCost;
}

// Méthode pour déterminer s'il y a une ligne de vue entre deux positions sur la grille
void Entity::lineOfSight(bool &test, std::vector<int> &posCible, const std::vector<std::vector<char>> &grid) {

    test = true;

    // Récupération des positions de départ et d'arrivée
    std::vector<int> start = getPosEntity();
    std::vector<int> end = posCible;

    // Calcul des différences en x et en y
    int dx, dy, sx, sy, err, e2 ;
    dx = std::abs(end[0] - start[0]);
    dy = - std::abs(end[1] - start[1]);
    sx = start[0] < end[0] ? 1 : -1;
    sy = start[1] < end[1] ? 1 : -1;
    err = dx + dy;

    // Boucle principale du tracé de la ligne de vue
    e2 = 2 * err;
    if (e2 >= dy){
        err += dy;
        start[0] += sx;
    }
    if (e2 <= dx){
        err += dx;
        start[1] += sy;
    }

    while (true){
        // Vérification si la position actuelle est dans la grille
        if (start[0] >= 0 &&
            start[0] < grid.size() &&
            start[1] >= 0 &&
            start[1] < grid[0].size()) {
            // Vérification si la position actuelle est la position cible
            if (start[0] == end[0] && start[1] == end[1]) {
                test = true;
                return;
            };

            // Vérification si la position actuelle est obstruée par un obstacle
            if (grid[start[0]][start[1]] != 0){
                // Mise à jour de la position cible et du drapeau de test
                posCible = start;
                test = false;
                return;
            }

            // Mise à jour des erreurs pour le tracé de la ligne
            e2 = 2 * err;
            if (e2 >= dy){
                err += dy;
                start[0] += sx;
            } else if (e2 <= dx){
                err += dx;
                start[1] += sy;
            }
        } else {
            // Si la position actuelle est en dehors de la grille, la ligne de vue est bloquée
            return;
        }
    }
}

// Méthode pour calculer la distance de Manhattan entre deux points
float Entity::manhattan_distance(std::vector<int> start, std::vector<int> end) {
    return std::abs((float)start[0] - (float)end[0]) + std::abs((float)start[1] - (float)end[1]);
}

// Méthode pour vérifier si une entité est touchée par un sort
bool Entity::TouchEntity(Entity& otherEntity, Spell spellEntity) {
    return manhattan_distance(posEntity, otherEntity.posEntity) <= spellEntity.range;
}

// Méthode pour déplacer l'entité vers une nouvelle position
void Entity::Move(std::vector<int> posMove, std::vector<std::vector<char>>& map) {
    int move = manhattan_distance(posEntity, posMove);

    if (AssezPointMove(move)) {
        pathFindingPlayer(posEntity, posMove, map);
    } else {
        std::cout << "pas assez de point move" << std::endl;
        return;
    }
}

// Méthode pour lancer un sort sur une cible
void Entity::SpellActive(Spell spellThrow, Entity& cible) {

    if (!AssezPointAction(spellThrow)) {
        std::cout << "Pas assez de points d'action." << std::endl;
        return;
    }
    // Calcul des dégâts infligés par le sort
    int damage = rand() % (spellThrow.getSpellStat(MAX_BASE_DAMAGE) - spellThrow.getSpellStat(MIN_BASE_DAMAGE)) + spellThrow.getSpellStat(MIN_BASE_DAMAGE);

    damage += damage * statActuelles.getStat(spellThrow.getSpellStat(ELEMENT_TYPE)) / 100.f;

    std::cout << damage << std::endl;
    // Application des dégâts à la cible
    cible.TakeDamage(damage, spellThrow.getSpellStat(ELEMENT_TYPE));
}

// Méthode pour infliger des dégâts à l'entité
void Entity::TakeDamage(int damage, int elementType) {

    int currentHealth = statActuelles.getStat(HEALTH);

    int damageMitigated = damage * (1.f - statActuelles.getStat(elementType + 100) / 100.f) - statActuelles.getStat(elementType + 200);

    int newHealth = currentHealth - damageMitigated;

    newHealth = std::max(0, newHealth);

    statActuelles.setStat(HEALTH, newHealth);

}

// Méthode pour vérifier si l'entité est morte
bool Entity::Death() const{
    return statActuelles.getStat(HEALTH) == 0;
}


int Entity::getLvl() const {
    return lvlEntity;
}

// Méthode pour réinitialiser les points de mouvement et d'action de l'entité
void Entity::resetPoint() {
    statActuelles.setStat(MOVEMENT_POINT, attEntity.getStat(MOVEMENT_POINT));
    statActuelles.setStat(ACTION_POINT, attEntity.getStat(ACTION_POINT));
}

// Méthode pour trouver le chemin optimal pour que l'entité se déplace vers une position donnée
void Entity::pathFinding(std::vector<int>& monster, const std::vector<int>& posEntity, std::vector<std::vector<char>>& map) {
    /*
    // Déclare des variables pour stocker les informations sur le chemin le plus court
    std::vector<int> cheminMinTemp, Case;
    std::vector<int> monsterPos = monster;
    std::vector<int> playerPos = posEntity;
    float minValue = 10000.0f; // Coût minimal en float
    Case = monsterPos;

    // Parcours les cases adjacentes à la position actuelle du monstre
    for (int i = Case[0] - 1; i <= Case[0] + 1; i++) {
        for (int j = Case[1] - 1; j <= Case[1] + 1; j++) {
            if (i >= 0 && i < map.size() && j >= 0 && j < map.size()) {
                // Vérifie si la case est accessible et ne contient pas le joueur
                if (map[i][j] < '1' && (i != playerPos[0] || j != playerPos[1])) {
                    // Calcule le coût pour atteindre la case en fonction de la distance de Manhattan et des obstacles
                    float g = (i == Case[0] || j == Case[1]) ? 1.0f : 2.0f; // Coût g en float
                    if (map[i][j] > '1') {
                        g = 100.0f;
                    }
                    float h = manhattan_distance({i, j}, playerPos); // Coût h en float
                    float f = h + g; // Coût f en float
                    // Met à jour la case avec le coût minimal si nécessaire
                    if (f <= minValue && f > 0.0f) {
                        cheminMinTemp = {i, j};
                        minValue = f;
                    }
                }
            }
        }
    }

    // Met à jour la position du monstre si un chemin minimal a été trouvé
    Case = cheminMinTemp;
    if (!Case.empty()) {
        monster = Case;
    }
    */
   // Si la case cible est une sortie et que le monstre est à proximité, il arrête son mouvement
    if (map[posEntity[0]][posEntity[1]] == 65 && (std::abs(monster[0] - posEntity[0]) + std::abs(monster[1] - posEntity[1]) <= 2)){
        this->statActuelles.setStat(MOVEMENT_POINT, 0); // Définit les points de mouvement à zéro
        tabDeplacement.clear(); // Efface le tableau de déplacement
        deplacementId = 0; // Réinitialise l'ID de déplacement
        return;
    }
    // Si le tableau de déplacement est vide, c'est le premier déplacement vers la cible
    if (tabDeplacement.empty()) {
        bool test; // Drapeau pour vérifier s'il y a une ligne de vue
        std::vector<int> destination = posEntity; // Initialise la destination à la position de l'entité cible
        std::vector<std::vector<int>> obstacles; // Stocke les positions des obstacles
        std::vector<std::vector<int>> enveloppeConv; // Stocke les positions de l'enveloppe convexe
        // Boucle pour calculer la ligne de vue vers la destination
        do{
            lineOfSight(test, destination, map); // Vérifie s'il y a une ligne de vue
            if (!test){
                obstacles.clear(); // Efface les obstacles
                obstacles.push_back(destination); // Ajoute la destination comme obstacle
                findWallGroup(destination, map, &obstacles); // Trouve les groupes d'obstacles
                // Si un seul obstacle est présent, l'évite
                if (obstacles.size() == 1) {
                    destination = avoidWall(obstacles, getPosEntity(),map); // Évite l'obstacle
                } else {
                    enveloppeConv = enveloppeConvexe(obstacles); // Trouve l'enveloppe convexe des obstacles
                    destination = avoidWall(enveloppeConv, getPosEntity(), map); // Évite les obstacles
                }
                // Si le monstre est à proximité de la destination, il arrête son mouvement
                if (std::abs(monster[0] - destination[0]) + std::abs(monster[1] - destination[1]) <= 2){
                    test = true; // La ligne de vue est dégagée
                    tabDeplacement.push_back(avoidWall(obstacles, getPosEntity(), map)); // Ajoute la destination dans le tableau de déplacement
                }
                // Si le monstre est à 2 cases de distance et que seul un obstacle est présent, ajuste le mouvement
                if (std::abs(monster[0] - destination[0]) + std::abs(monster[1] - destination[1]) == 2 &&
                    monster[0] != destination[0] &&
                    monster[1] != destination[1] &&
                    obstacles.size() == 1){
                        // Si la ligne horizontale est claire, déplace le monstre horizontalement
                    if (map[monster[0]][destination[1]] == 0){
                        fillTabDeplacement({monster[0],destination[1]},map); // Remplit le tableau de déplacement
                        return;
                    } else {
                        fillTabDeplacement({destination[0],monster[1]},map); // Remplit le tableau de déplacement
                        return;
                    }
                }
            }
        }while (!test); // Continue jusqu'à ce qu'une ligne de vue soit établie
        fillTabDeplacement(destination, map); // Remplit le tableau de déplacement avec la destination

    } else {
        // Si le monstre n'est pas encore à la position cible ou à portée de 2 cases
        if ((std::abs(monster[0] - posEntity[0]) + std::abs(monster[1] - posEntity[1]) > 2) || (map[tabDeplacement[deplacementId][0]][tabDeplacement[deplacementId][1]] == 65)) {
            this->setPosEntity(tabDeplacement[deplacementId]); // Déplace le monstre vers la prochaine case dans le tableau de déplacement
            deplacementId++; // Incrémente l'ID de déplacement
            this->statActuelles.addStat(MOVEMENT_POINT, -1); // Réduit les points de mouvement
            if (deplacementId >= tabDeplacement.size()) { // Si le tableau de déplacement est terminé
                tabDeplacement.clear(); // Efface le tableau de déplacement
                deplacementId = 0; // Réinitialise l'ID de déplacement
            }
        } else {
            // Si le monstre est à portée de 2 cases du joueur, ajuste le mouvement
            std::vector<int> rectification; // Vecteur pour rectifier le mouvement
            if(posEntity[0] > monster[0]){ // Si le joueur est au-dessus du monstre
                rectification.push_back(1); // Ajoute un déplacement vers le bas
                rectification.push_back(0); // Aucun déplacement horizontal
            } else if (posEntity[0] < monster[0]){ // Si le joueur est en dessous du monstre
                rectification.push_back(-1); // Ajoute un déplacement vers le haut
                rectification.push_back(0); // Aucun déplacement horizontal
            } else { // Si le joueur est à la même hauteur que le monstre
                rectification.push_back(0); // Aucun déplacement vertical
                if(posEntity[1] > monster[1]){ // Si le joueur est à droite du monstre
                    rectification.push_back(1); // Ajoute un déplacement vers la droite
                } else if (posEntity[1] < monster[1]){ // Si le joueur est à gauche du monstre
                    rectification.push_back(-1); // Ajoute un déplacement vers la gauche
                } else { // Si le joueur est à la même position horizontale que le monstre
                    rectification.push_back(0); // Aucun déplacement horizontal
                }
            }
            this->statActuelles.setStat(MOVEMENT_POINT, 0); // Définit les points de mouvement à zéro
        }
    }
}


void Entity::pathFindingPlayer(std::vector<int>& monster, const std::vector<int>& posEntity, std::vector<std::vector<char>>& map) {
    // Récupère le nombre de points de mouvement du joueur
    int move = statActuelles.getStat(MOVEMENT_POINT);

    // Vérifie si le joueur a suffisamment de points de mouvement pour se déplacer
    if (!AssezPointMove(move)) return;

    // Réduit les points de mouvement du joueur après le déplacement
    statActuelles.addStat(MOVEMENT_POINT, -1);

    // Si le monstre est déjà à la position cible, il s'arrête
    if (monster == posEntity) return;

    // Déclare des variables pour stocker les informations sur le chemin le plus court
    std::vector<int> cheminMinTemp, Case;
    std::vector<int> monsterPos = monster;
    std::vector<int> playerPos = posEntity;
    int minValue = 10000 ;
    Case = monsterPos;

    // Parcours les cases adjacentes à la position actuelle du joueur
    for (int i = Case[0] - 1; i <= Case[0] + 1; i++) {
        for (int j = Case[1] - 1; j <= Case[1] + 1; j++) {
            if (i >= 0 && i < map.size() && j >= 0 && j < map.size()) {
                // Vérifie si la case est accessible

                // Calcule le coût pour atteindre la case en fonction de la distance de Manhattan et des obstacles
                int g = (i == Case[0] || j == Case[1]) ? 1 : 2;
                if (map[i][j] > 1) {
                    g = 100;
                }
                int h = manhattan_distance({i, j}, playerPos);
                int f = h + g;
                // Met à jour la case avec le coût minimal si nécessaire
                if (f <= minValue && f > 0) {
                    cheminMinTemp = {i, j};
                    minValue = f;
                }

            }
        }
    }

    // Met à jour la position du joueur si un chemin minimal a été trouvé
    if (!cheminMinTemp.empty()) {
        monster = cheminMinTemp;
    }
}

// Fonction pour trouver le groupe d'obstacles à partir d'une position de mur
void Entity::findWallGroup (std::vector<int> wall, const std::vector<std::vector<char>> &grid, std::vector<std::vector<int>> *result){
    int deplacementX [4] = {1,-1,0,0}; // Déplacements en X (droite, gauche, pas de déplacement)
    int deplacementY [4] = {0,0,-1,1}; // Déplacements en Y (pas de déplacement, pas de déplacement, haut, bas)

    int ligne = grid.size(); // Nombre de lignes dans la grille
    int colone = grid[0].size(); // Nombre de colonnes dans la grille

    for (unsigned char i = 0; i < 4; i++){

        int newX = wall[0] + deplacementX[i]; // Nouvelle position en X
        int newY = wall[1] + deplacementY[i]; // Nouvelle position en Y

        // Vérifie si la nouvelle position est dans la grille et si elle est un obstacle
        if (newX >= 0 && 
            newX < ligne && 
            newY >= 0 && 
            newY < colone &&
            grid[newX][newY] != 0){

            bool test = true; // Drapeau pour vérifier si la nouvelle position est déjà dans le résultat
            std::vector<int> newPos; // Nouvelle position
            newPos.push_back(newX); // Ajoute la nouvelle position en X
            newPos.push_back(newY); // Ajoute la nouvelle position en Y
            // Vérifie si la nouvelle position est déjà dans le résultat
            for (int i = 0; i < result->size(); i++){
                if ((*result)[i][0] == newPos[0] && (*result)[i][1] == newPos[1] ) test = false;
            }
            if (test) {
                result->push_back(newPos); // Ajoute la nouvelle position au résultat
                findWallGroup(newPos,grid,result); // Continue de trouver les obstacles dans le groupe
            }
        }
    }
}

// Fonction pour éviter les murs et trouver une position sûre
std::vector<int> Entity::avoidWall (const std::vector<std::vector<int>> &walls, const std::vector<int> &posPlayer, std::vector<std::vector<char>> &map){

    if (walls.size() == 1 ) return walls[0];

    int id = 0;

    // Boucle pour trouver le mur le plus proche du joueur
    for (int i = 0; i < walls.size(); ++i) {
        if(manhattan_distance(walls[i], posPlayer) < manhattan_distance(walls[id], posPlayer)) id = i;
    }

    std::vector<int> temp;
    std::vector<std::vector<int>> diags;

    int deplacementX [4] = {1,1,-1,-1};
    int deplacementY [4] = {1,-1,-1,1};
    bool test;

    // Boucle pour vérifier les positions diagonales autour du mur
    for (int i = 0; i < 4; ++i) {

        temp = walls[id];
        temp[0] += deplacementX[i];
        temp[1] += deplacementY[i];
        lineOfSight(test,temp,map);
        // Vérifie si la position est valide (dans la grille, pas un obstacle, avec ligne de vue)
        if (temp[0] < map.size() &&
            temp[0] >= 0 &&
            temp[1] >= 0 &&
            temp[1] < map[0].size() &&
            map[temp[0]][temp[1]] == 0 &&
            test) {

            diags.push_back(temp);
        }
    }
    // Si aucune position diagonale n'est sûre, trouve une position rectiligne sûre
    if (diags.empty()){
        std::vector<int> recti;
        if (walls[id][0] < posPlayer[0]){
            recti.push_back(-1);
        } else if (walls[id][0] == posPlayer[0]){
            recti.push_back(0);
        } else if (walls[id][0] > posPlayer[0]){
            recti.push_back(1);
        }
        if (walls[id][1] < posPlayer[1]){
            recti.push_back(-1);
        } else if (walls[id][1] == posPlayer[1]){
            recti.push_back(0);
        } else if (walls[id][1] > posPlayer[1]){
            recti.push_back(1);
        }
        recti[0] += walls[id][0];
        recti[1] += walls[id][1];
        return recti;
    }
    
    // Trouve la position diagonale la plus éloignée du joueur
    int result = 0;
    for (int i = 0; i < diags.size(); ++i) {
        if  (manhattan_distance(diags[i], posPlayer) > manhattan_distance(diags[result], posPlayer) &&
             manhattan_distance(diags[i], posPlayer) > 1) result = i;
    }
    return diags[result];

}

// Remplit le tableau des déplacements à partir de la position actuelle jusqu'à la destination
void Entity::fillTabDeplacement (std::vector<int> pos, std::vector<std::vector<char>> grid){
    tabDeplacement.clear();
    std::vector<int> start = getPosEntity();
    std::vector<int> end = pos;

    int dx, dy, sx, sy, err, e2 ;
    dx = std::abs(end[0] - start[0]);
    dy = - std::abs(end[1] - start[1]);
    sx = start[0] < end[0] ? 1 : -1;
    sy = start[1] < end[1] ? 1 : -1;
    err = dx + dy;


    e2 = 2 * err;
    if (e2 >= dy){
        err += dy;
        start[0] += sx;
    }
    if (e2 <= dx){
        err += dx;
        start[1] += sy;
    }

    while (true){
        if (start[0] >= 0 &&
            start[0] < grid.size() &&
            start[1] >= 0 &&
            start[1] < grid[0].size()) {
            if (grid[start[0]][start[1]] == 0){
                tabDeplacement.push_back(start);
            }

            if (start[0] == end[0] && start[1] == end[1]) return;
            if (std::abs(start[0] - end[0]) + std::abs(start[1] - end[1]) ==0) return;
            e2 = 2 * err;
            if (e2 >= dy){
                err += dy;
                start[0] += sx;
            }
            if (e2 <= dx){
                err += dx;
                start[1] += sy;
            }
        }
    }
    if (tabDeplacement.empty()){
    }
}