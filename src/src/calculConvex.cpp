#include "../../inc/calculConvex.h"
#include <iostream>
#include <vector>

// Fonction pour trouver l'indice du point le plus à gauche dans le nuage de points
int leftMost (const std::vector<std::vector<int>> & obstacles ){
    int res = 0;
    for (int i = 0; i < obstacles.size() ; ++i) {
        if (obstacles[i][0] < obstacles[res][0]){
            res = i;
        }
    }
    return res;
}

// Fonction pour trouver l'indice du point le plus à droite dans le nuage de points
int rightMost (const std::vector<std::vector<int>> & obstacles ) {
    int res = 0;
    for (int i = 0; i < obstacles.size() ; ++i) {
        if (obstacles[i][0] >= obstacles[res][0]){
            res = i;
        }
    }
    return res;
}

// Fonction pour calculer le produit mixte de trois points
int produitMixte (const std::vector<int> &A, const std::vector<int> &B, const std::vector<int> &C){
    return (B[0] - A[0]) * (C[1] - A[1]) - (B[1] - A[1]) * (C[0] - A[0]);
}

// Fonction pour vérifier si un point est à l'intérieur d'un triangle
bool isInsideTriangle (const std::vector<int> &A, const std::vector<int> &B, const std::vector<int> &C, const std::vector<int> &P){
    int pm1 = produitMixte(A,B,P);
    int pm2 = produitMixte(B,C,P);
    int pm3 = produitMixte(C,A,P);

    bool sameSign = (pm1 >= 0 && pm2 >= 0 && pm3 >= 0) || (pm1 < 0 && pm2 < 0 && pm3 < 0);

    return sameSign;
}

// Fonction pour calculer l'aire d'un triangle formé par trois points
double triangleArea(const std::vector<int> &A, const std::vector<int> &B, const std::vector<int> &C){
    return  0.5 * std::abs(A[0] * (B[1] - C[1]) + B[0] * (C[1] - A[1]) + C[0] * (A[1] - B[1]));
}

// Fonction pour filtrer les points se trouvant du même côté qu'un segment de droite
std::vector<std::vector<int>> setOnRightOfLine(const std::vector<std::vector<int>> &set, const std::vector<int> &A, const std::vector<int> &B) {
    double a;
    if(B[0] != A[0]){
        a = (B[1] - A[1]) / (B[0] - A[0]);
    } else {
        a = 1;
    }

    const double b = A[1] - a * A[0];

    std::vector<std::vector<int>> subset;

    if(A[0] < B[0]) {
        for(const std::vector<int> &point: set) {
            if(point[0] * a + b < point[1]) {
                subset.push_back(point);
            }
        }
    } else {
        for(const std::vector<int> &point: set) {
            if(point[0] * a + b > point[1]) {
                subset.push_back(point);
            }
        }
    }

    return subset;
}

// Fonction récursive pour trouver l'enveloppe convexe du nuage de points
std::vector<std::vector<int>> enveloppeConvexe ( std::vector<std::vector<int>> nuage){
    if(nuage.size() <= 2){
        return nuage;
    }
    std::vector<std::vector<int>> hull;

    int idLeft = leftMost (nuage);
    int idRight = rightMost(nuage);
    double a,b;
    if (nuage[idRight][0] != nuage[idLeft][0] ){
        a = (nuage[idRight][1] - nuage[idLeft][1]) /(nuage[idRight][0] - nuage[idLeft][0]);
        b = nuage[idLeft][1] - a * nuage[idLeft][0];
    } else {
        a = (nuage[idRight][1] - nuage[idLeft][1]) / 1;
        b = nuage[idLeft][1] - a * nuage[idLeft][0];
    }



    std::vector<std::vector<int>> top, bot;

    for (const std::vector<int> point : nuage) {
        if (point[0] * a + b < point[1]){
            top.push_back(point);
        } else {
            bot.push_back(point);
        }
    }
    hull.push_back(nuage[idLeft]);
    hull.push_back(nuage[idRight]);

    findHull(nuage[idLeft],nuage[idRight],top,hull);
    findHull(nuage[idLeft],nuage[idRight],bot,hull);

    return hull;
}

// Fonction auxiliaire pour trouver les points formant l'enveloppe convexe
void findHull (const std::vector<int> &pointGauche, const std::vector<int> &pointDroit, const std::vector<std::vector<int>> &sousNuage, std::vector<std::vector<int>> &result){
    if(sousNuage.empty()){
        return;
    }

    int farthest = 0;
    for (int i = 1; i < sousNuage.size(); ++i){
        if(triangleArea(pointGauche,sousNuage[i],pointDroit) > triangleArea(pointGauche, sousNuage[farthest], pointDroit)){
            farthest = i;
        }
    }
    bool test = true;
    for (int i = 0; i < result.size(); i++){
        if (result[i][0] == sousNuage[farthest][0] && result[i][1] == sousNuage[farthest][1] ) test = false;
    }

    if(test) result.push_back(sousNuage[farthest]);


    std::vector<std::vector<int>> outsideAFB;
    for(const std::vector<int> &point: sousNuage) {
        if(!isInsideTriangle(pointGauche, sousNuage[farthest], pointDroit, point)) {
            outsideAFB.push_back(point);
        }
    }


    findHull(pointGauche, sousNuage[farthest], setOnRightOfLine(outsideAFB, pointGauche, sousNuage[farthest]), result);
    findHull(sousNuage[farthest], pointDroit, setOnRightOfLine(outsideAFB, sousNuage[farthest], pointDroit), result);
}