#ifndef RAY_H
#define RAY_H

#include "vec.h"
#include "mat.h"
#include "mesh.h"
#include <cfloat>

/**
 * @brief Représente un rayon dans l'espace.
 */
struct Ray
{
    Point o;                //!< Origine du rayon.
    Vector d;               //!< Direction du rayon.
    float tmax;             //!< Position maximale du rayon, définissant la longueur maximale du rayon.
    
    /**
     * @brief Constructeur d'un rayon pour un segment défini par son origine et son extrémité.
     * @param origine Origine du rayon.
     * @param extremite Extrémité du rayon.
     */
    Ray(const Point& origine, const Point& extremite) : o(origine), d(Vector(origine, extremite)), tmax(1) {}
    
    /**
     * @brief Constructeur d'un rayon pour une demi-droite définie par son origine et sa direction.
     * @param origine Origine du rayon.
     * @param direction Direction du rayon.
     */
    Ray(const Point& origine, const Vector& direction) : o(origine), d(direction), tmax(FLT_MAX) {}
    
    /**
     * @brief Calcule le point correspondant sur le rayon pour un paramètre donné.
     * @param t Paramètre indiquant la position le long du rayon.
     * @return Point sur le rayon pour le paramètre donné.
     */
    Point point(const float t) const { return o + t * d; }
};

/**
 * @brief Représente les informations sur un point d'intersection entre un rayon et un triangle.
 */
 struct Hit
{
    float t;            //!< Position du point d'intersection sur le rayon.
    float u, v;         //!< Coordonnées barycentriques du point d'intersection sur le triangle.
    int triangle_id;    //!< Identifiant du triangle dans le maillage.
    
    /**
     * @brief Constructeur par défaut initialisant les informations d'intersection avec des valeurs par défaut.
     */
    Hit() : t(FLT_MAX), u(), v(), triangle_id(-1) {}

    /**
     * @brief Constructeur initialisant les informations d'intersection avec les valeurs fournies.
     * @param _t Position du point d'intersection sur le rayon.
     * @param _u Coordonnée barycentrique u du point d'intersection.
     * @param _v Coordonnée barycentrique v du point d'intersection.
     * @param _id Identifiant du triangle dans le maillage.
     */
    Hit(const float _t, const float _u, const float _v, const int _id) : t(_t), u(_u), v(_v), triangle_id(_id) {}
    
    /**
     * @brief Opérateur de conversion implicite en booléen, indiquant si une intersection est détectée.
     * @return true si une intersection est détectée, sinon false.
     */
    operator bool() { return (triangle_id != -1); }
};

/**
 * @brief Représente un triangle dans l'espace.
 */
struct Triangle
{
    Point p;            //!< Sommet a du triangle.
    Vector e1, e2;      //!< Arêtes ab et ac du triangle.
    int id;             //!< Identifiant du triangle dans le maillage.
    
    /**
     * @brief Constructeur initialisant le triangle avec les données fournies.
     * @param data Données du triangle, contenant les positions des sommets.
     * @param _id Identifiant unique du triangle dans le maillage.
     */
    Triangle(const TriangleData& data, const int _id) : p(data.a), e1(Vector(data.a, data.b)), e2(Vector(data.a, data.c)), id(_id) {}

    /**
     * @brief Calcule le point d'intersection entre le rayon donné et ce triangle.
     * @param ray Rayon à tester pour l'intersection.
     * @param tmax Position maximale sur le rayon pour la recherche d'intersection.
     * @return Informations sur le point d'intersection, ou Hit vide si aucune intersection n'est trouvée.
     */
    Hit intersect( const Ray &ray, const float tmax ) const
    {
        Vector pvec= cross(ray.d, e2);
        float det= dot(e1, pvec);
        
        float inv_det= 1 / det;
        Vector tvec(p, ray.o);
        
        float u= dot(tvec, pvec) * inv_det;
        if(u < 0 || u > 1) return Hit();        // pas d'intersection
        
        Vector qvec= cross(tvec, e1);
        float v= dot(ray.d, qvec) * inv_det;
        if(v < 0 || u + v > 1) return Hit();    // pas d'intersection
        
        float t= dot(e2, qvec) * inv_det;
        if(t > tmax || t < 0) return Hit();     // pas d'intersection
        
        return Hit(t, u, v, id);                // p(u, v)= (1 - u - v) * a + u * b + v * c
    }
};

#endif // RAY_TRIANGLE_INTERSECTION_H