#include "spell.h"
#include "attribute.h"


// Définition du constructeur par défaut de la classe Spell
Spell::Spell(){
    elementType = 0;
    minBaseDamage = 0;
    maxBaseDamage = 0;
    range = 0;
    actionPointCost = 1;
    lineOfSight = true;
    isLineOnly = false;
    isAffectedByRangePoint = true;
}

// Définition du constructeur surchargé de la classe Spell
Spell::Spell(std::string nameA, int elementTypeA, int minBaseDamageA,
              int maxBaseDamageA, int rangeA, int AoERadiusA, int actionPointCostA,
              bool lineOfSightA, bool isAffectedByRangeA, bool isLineOnlyA, bool isAoEA) {

    elementType = elementTypeA;
    minBaseDamage = minBaseDamageA;
    maxBaseDamageA = maxBaseDamageA;
    range = rangeA;
    AoERadius = AoERadiusA;
    actionPointCost = actionPointCostA;
    lineOfSight = lineOfSightA;
    isAffectedByRangePoint = isAffectedByRangeA;
    isLineOnly = isLineOnlyA;
    isAoE = isAoEA;
    name = nameA;
}

// Instance de sort "fireWork" prédéfinie
Spell fireWork = Spell("fireWork", 1, 5, 2, 5, -1, 1, true, true, true, false);

// Méthode pour sélectionner un sort en fonction de son code
Spell Spell::SelectSpell(int codeSpell) {
    switch (codeSpell) {
    case FIREWORK:
        return fireWork;
    default:
        return Spell("no spell", 0, 0, 0, 0, 0, 0, false, false, false, false);
    }
}

// Méthode pour obtenir la valeur d'une statistique du sort
int Spell::getSpellStat(int statIndex) const {
    switch (statIndex) {
    case RANGE:
        return range;
    case ELEMENT_TYPE:
        return elementType;
    case MIN_BASE_DAMAGE:
        return minBaseDamage;
    case MAX_BASE_DAMAGE:
        return maxBaseDamage;
    case AOE_RADIUS:
        return AoERadius;
    case ACTION_POINT_COST:
        return actionPointCost;
    default:
        return 1;
    }
}