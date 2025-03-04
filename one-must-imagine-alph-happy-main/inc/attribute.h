#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H


/* Cette énumération sera utilisée pour passer facilement entre les statistiques
   stat < 10 -> Statistique offensive
   10 < stat < 20 -> Non offensif
   20 < stat < 100 -> Lié à l'action
   100 < stat < 200 -> Résistance en pourcentage
   200 < stat -> Résistance
*/
enum stat {
    FIRE = 1,
    WATER = 2,
    EARTH = 3,
    WIND = 4,
    HEALTH = 11,
    INITIATIVE = 12,
    HEAL_BOOST = 13,
    ESCAPE = 14,
    GRASP = 15,
    ACTION_POINT = 21,
    MOVEMENT_POINT = 22,
    RANGE_POINT = 23,
    FIRE_RESIST_PERCENT = FIRE + 100,
    WATER_RESIST_PERCENT = WATER + 100,
    EARTH_RESIST_PERCENT = EARTH + 100,
    WIND_RESIST_PERCENT = WIND + 100,
    FIRE_RESIST = FIRE + 200,
    WATER_RESIST = WATER + 200,
    EARTH_RESIST = EARTH + 200,
    WIND_RESIST = WIND + 200
    
};

/**
 * @brief Classe concernant les statistiques que chaque entité dans le jeu possède, y compris le joueur
 * @param fire Paramètre améliorant les dégâts de feu (0+)
 * @param water Paramètre améliorant les dégâts d'eau (0+)
 * @param earth Paramètre améliorant les dégâts de terre (0+)
 * @param wind Paramètre améliorant les dégâts de vent (0+)
 * @param health Nombre de points de vie (1+)
 * @param initiative La statistique qui classe les entités dans la chronologie (0+)
 * @param actionPoint Paramètre définissant le nombre de points d'action qu'une entité a (6+)
 * @param movementPoint Paramètre définissant le nombre de points de mouvement qu'une entité a (3+) 
 * @param rangePoint Paramètre définissant le nombre de points de portée qu'une entité a (0+)
 * @param fireResistPercent Réduit les dégâts de feu entrants de fireResitePercent % (-inf - +100)
 * @param waterResistPercent Réduit les dégâts d'eau entrants de waterResitePercent % (-inf - +100)
 * @param earthResistPercent Réduit les dégâts de terre entrants de earthResitePercent % (-inf - +100)
 * @param windResistPercent Réduit les dégâts de vent entrants de windResitePercent % (-inf - +100)
 * @param fireResist Réduit les dégâts de feu entrants de fireResist (-inf - +inf)
 * @param waterResist Réduit les dégâts d'eau entrants de waterResist (-inf - +inf)
 * @param earthResist Réduit les dégâts de terre entrants de earthResist (-inf - +inf)
 * @param windResist Réduit les dégâts de vent entrants de windResist (-inf - +inf)
 * @param healBoost Ajoute healBoost à tout soin lancé (0+)
 * @param escape Capacité à échapper à un ennemi (0+)
 * @param grasp Capacité à maintenir un ennemi dans la prise de l'entité (0+)  
*/

class Attribute {
private:
    friend class Entity;
    friend class Player;
    friend class Monster;
    int fire, water, earth, wind, health, initiative;
    unsigned char actionPoint, movementPoint, rangePoint;
    char fireResist, waterResist, earthResist, windResist, fireResistPercent, waterResistPercent, earthResistPercent, windResistPercent , healBoost, escape, grasp;

public:
    /**
     * @brief Constructeur par défaut 
     * @return Une instance de la classe Attribute avec les paramètres par défaut
    */
    Attribute();

    /**
     * @brief Constructeur par valeur
     * @param f int feu
     * @param w int eau
     * @param e int terre
     * @param wi int vent
     * @param h int points de vie
     * @param in int initiative
     * @param action unsigned char points d'action
     * @param move unsigned char points de mouvement
     * @return Une instance de la classe Attribute avec les paramètres précédents
    */
    Attribute(int f, int w, int e, int wi, int h, int in, unsigned char action, unsigned char move);

    /**
     * @brief Constructeur par copie
     * @param copy L'attribut à copier
     * @return Une copie de l'Attribute copy passé en paramètre
    */
    Attribute(const Attribute & copy);


    /**
     * @brief Accesseur pour toute la classe
     * @return Retourne elle-même
    */
    Attribute getAttributes () const;

    /**
     * @brief Accesseur simple pour chaque statistique
     * @param codeStat Le sélecteur de la statistique (ils sont répertoriés dans l'énumération) 
    */
    int getStat(int codeStat) const;

    /**
     * @brief Ajout simple, vérifie si nécessaire si la valeur est valide
     * @param codeStat Le sélecteur de la statistique (ils sont répertoriés dans l'énumération)
     * @param value Les données à ajouter/définir
    */
    void addStat(int codeStat, int value);

    /**
     * @brief Setter simple, initialise le membre codeStat avec la valeur
     * @param codeStat Le sélecteur de la statistique (ils sont répertoriés dans l'énumération) 
     * @param value Les données à définir
    */
    int setStat(int codeStat, int value);

    void StatUp(int coef);
};

#endif // _ATTRIBUTE_H
