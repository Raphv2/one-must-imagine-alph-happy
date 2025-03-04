#ifndef _CALCUL_CONVEX_H
#define _CALCUL_CONVEX_H

#include <iostream>
#include <vector>


/**
 * @brief Retourne l'indice de l'obstacle le plus à gauche
 * @param obstacles Liste des positions des obstacles
 * @return Un indice de obstacles
*/
int leftMost (const std::vector<std::vector<int>> & obstacles);


/**
 * @brief Retourne l'indice de l'obstacle le plus à droite
 * @param obstacles Liste des positions des obstacles
 * @return Un indice de obstacles
*/
int rightMost (const std::vector<std::vector<int>> & obstacles);

/**
 * @brief Calcule le produit mixte des vecteurs AB et AC
 * @param A Positon du point A
 * @param B Positon du point B
 * @param C Positon du point C
 * @return Le produit mixte calculé, peut importe la précision on ne veut que le signe
*/
int produitMixte (const std::vector<int> &A, const std::vector<int> &B, const std::vector<int> &C);

/**
 * @brief Vérifie si le point P est à l'intérieur du triangle ABC
 * @param A Positon du point A
 * @param B Positon du point B
 * @param C Positon du point C
 * @param P Positon du point P
 * @return Un booléen à true si à l'intérieur, false sinon.
*/
bool isInsideTriangle (const std::vector<int> &A, const std::vector<int> &B, const std::vector<int> &C, const std::vector<int> &P);

/**
 * @brief Calcule l'aire d'un triangle ABC
 * @param A Point A
 * @param B Point B
 * @param C Point C
 * @return L'aire du triangle ABC
*/
double triangleArea (const std::vector<int> &A, const std::vector<int> &B, const std::vector<int> &C);

/**
 * @brief Calcule l'enveloppe convexe des points passé en paramètre
 * @param nuage Nuage de point 2 dimension
 * @return Liste des points entourant les points de nuage
*/
std::vector<std::vector<int>> enveloppeConvexe (std::vector<std::vector<int>> nuage);

/**
 * @brief Trouve tous les points de l'enveloppe de manière récursive
 * @param pointGauche Point le plus à gauche du sousNuage
 * @param pointDroit Point le plus à droite du sousNuage
 * @param sousNuage Sous partie du nuage de point initial
 * @param result Paramètre résultat
*/
void findHull (const std::vector<int> &pointGauche, const std::vector<int> &pointDroit, const std::vector<std::vector<int>> &sousNuage, std::vector<std::vector<int>> &result);

#endif // _CALCUL_CONVEX_H