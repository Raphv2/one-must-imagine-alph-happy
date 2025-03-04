#include "attribute.h"

Attribute::Attribute(){
    // Définition du constructeur par défaut de la classe Attribute
    // Initialise toutes les variables membres à 0 ou à des valeurs par défaut
    fire = 0;
    water = 0;
    earth = 0;
    wind = 0;
    health = 100;
    initiative = 0;
    actionPoint = 6;
    movementPoint = 3;
    rangePoint = 0;
    fireResistPercent = 0;
    waterResistPercent = 0;
    earthResistPercent = 0;
    windResistPercent = 0;
    fireResist = 0;
    waterResist = 0;
    earthResist = 0;
    windResist = 0;
    healBoost = 0;
    escape = 0;
    grasp = 0;
}

Attribute::Attribute(int f, int w, int e, int wi, int h, int in, unsigned char action, unsigned char move){
    // Constructeur prenant des valeurs initiales pour les attributs
    // Initialise les variables membres avec les valeurs passées en paramètres
    fire = f;
    water = w;
    earth = e;
    wind = wi;
    health = h;
    initiative = in;
    actionPoint = action;
    movementPoint = move;
    rangePoint = 0;
    fireResistPercent = 0;
    waterResistPercent = 0;
    earthResistPercent = 0;
    windResistPercent = 0;
    fireResist = 0;
    waterResist = 0;
    earthResist = 0;
    windResist = 0;
    healBoost = 0;
    escape = 0;
    grasp = 0;
}

Attribute::Attribute(const Attribute &copy) {
    // Constructeur de copie, initialise les attributs en copiant les valeurs de l'objet source
    fire = copy.fire;
    water = copy.water;
    earth = copy.earth;
    wind = copy.wind;
    health = copy.health;
    initiative = copy.initiative;
    actionPoint = copy.actionPoint;
    movementPoint = copy.movementPoint;
    rangePoint = copy.rangePoint;
    fireResistPercent = copy.fireResistPercent;
    waterResistPercent = copy.waterResistPercent;
    earthResistPercent = copy.earthResistPercent;
    windResistPercent = copy.windResistPercent;
    fireResist = copy.fireResist;
    waterResist = copy.waterResist;
    earthResist = copy.earthResist;
    windResist = copy.windResist;
    healBoost = copy.healBoost;
    escape = copy.escape;
    grasp = copy.grasp;
}

Attribute Attribute::getAttributes() const {
    return *this; // Renvoie une copie des attributs actuels
}

int Attribute::getStat(int codeStat) const {
    // Méthode pour obtenir la valeur d'un attribut spécifique en fonction du code de statut fourni
    switch (codeStat)
    {
    case FIRE:
        return fire;
        break;
    case WATER:
        return water;
        break;
    case EARTH:
        return earth;
        break;
    case WIND:
        return wind;
        break;
    case HEALTH:
        return health;
        break;
    case INITIATIVE:
        return initiative + fire + water + earth + wind;
        break;
    case HEAL_BOOST:
        return healBoost + fire / 10;
        break;
    case ESCAPE:
        return escape + wind / 10;
        break;
    case GRASP:
        return grasp + wind / 10;
        break;
    case ACTION_POINT:
        return actionPoint;
        break;
    case MOVEMENT_POINT:
        return movementPoint;
        break;
    case RANGE_POINT:
        return rangePoint;
        break;
    case FIRE_RESIST_PERCENT:
        return fireResistPercent;
        break;
    case WATER_RESIST_PERCENT:
        return waterResistPercent;
        break;
    case EARTH_RESIST_PERCENT:
        return earthResistPercent;
        break;
    case WIND_RESIST_PERCENT:
        return windResistPercent;
        break;
    case FIRE_RESIST:
        return fireResist;
        break;
    case WATER_RESIST:
        return waterResist;
        break;
    case EARTH_RESIST:
        return earthResist;
        break;
    case WIND_RESIST:
        return windResist;
        break;
    default:
        return 1;
        break;
    }
}



void Attribute::addStat(int codeStat, int value){
    // Méthode pour ajouter une valeur à un attribut spécifique en fonction du code de statut fourni
    switch (codeStat)
    {
    case FIRE:
        if (value >= 0) fire += value;
        break;
    case WATER:
        if (value >= 0) water += value;
        break;
    case EARTH:
        if (value >= 0) earth += value;
        break;
    case WIND:
        if (value >= 0) wind += value;
        break;
    case HEALTH:
        if (value > 0) health += value;
        break;
    case INITIATIVE:
        if (value >= 0) initiative += value;
        break;
    case HEAL_BOOST:
        if (value > 0) healBoost += value;
        break;
    case ESCAPE:
        if (value > 0) escape += value;
        break;
    case GRASP:
        if (value > 0) grasp += value;
        break;
    case ACTION_POINT:
        actionPoint += value;
        if (actionPoint > 10 && actionPoint < 20) actionPoint = 10;
        if (actionPoint > 20) actionPoint = 0;
        break;
    case MOVEMENT_POINT:
        movementPoint += value;
        if (movementPoint > 10 && movementPoint < 20) movementPoint = 10;
        if (movementPoint > 20) movementPoint = 0;
        break;
    case RANGE_POINT:
        rangePoint += value;
        if (rangePoint > 6 ) rangePoint = 6;
        if (rangePoint < 0) rangePoint = 0;
        break;

    case FIRE_RESIST_PERCENT:
        fireResistPercent += value;
        break;
    case WATER_RESIST_PERCENT:
        waterResistPercent += value;
        break;
    case EARTH_RESIST_PERCENT:
        earthResistPercent += value;
        break;
    case WIND_RESIST_PERCENT:
        windResistPercent += value;
        break;
    case FIRE_RESIST:
        fireResist += value;
        break;
    case WATER_RESIST:
        waterResist += value;
        break;
    case EARTH_RESIST:
        earthResist += value;
        break;
    case WIND_RESIST:
        windResist += value;
        break;
    default:
        
        break;
    }
}

int Attribute::setStat(int codeStat, int value){
    // Méthode pour définir la valeur d'un attribut spécifique en fonction du code de statut fourni
    switch (codeStat)
    {
    case FIRE:
        if (value >= 0) return fire = value;
        break;
    case WATER:
        if (value >= 0) return water = value;
        break;
    case EARTH:
        if (value >= 0) return earth = value;
        break;
    case WIND:
        if (value >= 0) return wind = value;
        break;
    case HEALTH:
        if (value >= 0) return health = value;
        break;
    case INITIATIVE:
        if (value >= 0) return initiative = value;
        break;
    case HEAL_BOOST:
        if (value > 0) return healBoost = value;
        break;
    case ESCAPE:
        if (value > 0) return  escape = value;
        break;
    case GRASP:
        if (value > 0) return grasp = value;
        break;
    case ACTION_POINT: // Modifier incohérence 
        return  actionPoint = value;
        if (actionPoint > 6 && actionPoint < 20) actionPoint = 6;
        if (actionPoint > 20) actionPoint = 0;
        break;
    case MOVEMENT_POINT:
        return  movementPoint = value;
        if (movementPoint > 6 && movementPoint < 20) movementPoint = 6;
        if (movementPoint > 20) movementPoint = 0;
        break;
    case RANGE_POINT:
        return rangePoint = value;
        if (rangePoint > 6 ) rangePoint = 6;
        if (rangePoint < 0) rangePoint = 0;
        break;

    case FIRE_RESIST_PERCENT:
        return fireResistPercent = value;
        break;
    case WATER_RESIST_PERCENT:
        return waterResistPercent = value;
        break;
    case EARTH_RESIST_PERCENT:
        return earthResistPercent = value;
        break;
    case WIND_RESIST_PERCENT:
        return windResistPercent = value;
        break;
    case FIRE_RESIST:
        return fireResist = value;
        break;
    case WATER_RESIST:
        return waterResist = value;
        break;
    case EARTH_RESIST:
        return earthResist = value;
        break;
    case WIND_RESIST:
        return windResist = value;
        break;
    default:
        break;
    }
}

void Attribute::StatUp(int coef){
    // Méthode pour augmenter tous les attributs par un coefficient donné
    fire *= coef;
    water *= coef;
    earth *= coef;
    wind *= coef;
    health *= coef;
    initiative *= coef;
    rangePoint *= coef;
}