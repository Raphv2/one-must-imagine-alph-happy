#ifndef _SPELL_H
#define _SPELL_H

#include <string>

/**
 * @brief Enumération des sorts prédéfinis.
 */
enum listSpell{
    DEFAULT = 0, //!< Sort par défaut.
    FIREWORK = 1 //!< Sort feu d'artifice.
};

/**
 * @brief Enumération des statistiques des sorts.
 */
enum spellStat{
    
    RANGE = 1, //!< Portée du sort.
    ELEMENT_TYPE = 2, //!< Type d'élément du sort.
    MIN_BASE_DAMAGE = 3, //!< Dommages de base minimaux du sort.
    MAX_BASE_DAMAGE = 4, //!< Dommages de base maximaux du sort.
    AOE_RADIUS = 5, //!< Rayon de l'effet de zone du sort.
    ACTION_POINT_COST = 6 //!< Coût en points d'action du sort.
};


/**
 * @brief This class describes a spell
 * @param name Spell's name
 * @param elementType The type of element in wich th spell will damage (1 -> fire, 2 -> water, 3 -> earth, 4 -> wind)
 * @param minBaseDamage The minimum amout of the damage range before damage calculation
 * @param maxBaseDamage The maximum amout of the damage range before damage calculation
 * @param range The max distance the spell can be cast to (affected by rangePoint)
 * @param AoERadius The radius of the "circle" affected by the spell (if isAoE = false then -1)
 * @param actionPointCost The cost of the spell (default = 1)
 * @param lineOfSight Does the spell go through walls (default = true)
 * @param isLineOnly Is the spell castable in line only (default = false)
 * @param isAoE Does the spell affect an area (default = false)
 * @param isAffectedByRangePoint Is the spell affected by range point (default = true)
*/
class Spell {
    private:
    friend class Entity; //!< Permet d'accéder aux membres privés de la classe Entity.
    std::string name; //!< Nom du sort.
    int elementType, minBaseDamage, maxBaseDamage, range, AoERadius , actionPointCost; //!< Caractéristiques du sort.
    bool lineOfSight, isAffectedByRangePoint ,isLineOnly , isAoE ; 

    public:
    /**
     * @brief Constructeur par défaut
     */
    Spell();

    /**
     * @brief Constructeur par valeur.
     * @param nameA Nom du sort.
     * @param elementTypeA Type d'élément du sort.
     * @param minBaseDamageA Dommages de base minimaux du sort.
     * @param maxBaseDamageA Dommages de base maximaux du sort.
     * @param rangeA Portée du sort.
     * @param AoERadiusA Rayon de l'effet de zone du sort.
     * @param actionPointCostA Coût en points d'action du sort.
     * @param lineOfSightA Indique si le sort nécessite une ligne de vue.
     * @param isAffectedByRangeA Indique si le sort est affecté par la portée.
     * @param isLineOnlyA Indique si le sort peut être lancé en ligne uniquement.
     * @param isAoEA Indique si le sort a un effet de zone.
     */
    Spell(std::string nameA, int elementTypeA, int minBaseDamageA ,
          int maxBaseDamageA , int rangeA , int AoERadiusA , int actionPointCostA , 
          bool lineOfSightA , bool isAffectedByRangeA , bool isLineOnlyA , bool isAoEA );

    /**
     * @brief Sélectionne un sort avec son indice déclaré dans l'énumération.
     * @param codeSpell L'indice du sort.
     * @return Le sort sélectionné.
     */
    Spell SelectSpell (int codeSpell);

    /**
     * @brief Récupère une statistique du sort.
     * @param statIndex Indice de la statistique recherchée.
     * @return La valeur de la statistique.
     */
    int getSpellStat(int statIndex) const;
};

#endif //_SPELL_H