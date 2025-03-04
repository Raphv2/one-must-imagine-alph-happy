#ifndef _IMAGE_VIEWER_H
#define _IMAGE_VIEWER_H 

#include "glcore.h"

#include "color.h"


/**
 * @brief Structure représentant un visualiseur d'image
 */
struct ImageViewer
{
    ImageViewer( ) : font(0), program(0), vao(0), ubo(0), width(0), height(0) {} // Constructeur par défaut

    int buffer[1]; // Tampon de données
    GLuint font;        //!< Texture contenant les caractères.
    GLuint program;     //!< Shader pour afficher le texte.
    GLuint vao;         //!< Vertex Array Object.
    GLuint ubo;         //!< Uniform Buffer Object, pour transférer le texte à afficher.
    int width; // Largeur de l'image
    int height; // Hauteur de l'image
};


/**
 * @brief Crée un visualiseur d'image à partir d'un fichier
 * @param filename Nom du fichier image
 * @return Un ImageViewer initialisé avec l'image du fichier spécifié
 */
ImageViewer create_ImageViewer(const char* filename);

/**
 * @brief Crée un visualiseur d'image recadré à partir d'un fichier
 * @param filename Nom du fichier image
 * @return Un ImageViewer initialisé avec l'image recadrée du fichier spécifié
 */
//ImageViewer create_crop_ImageViewer(const char* filename);

/**
 * @brief Détruit un visualiseur d'image
 * @param text ImageViewer à détruire
 */
void release_ImageViewer( ImageViewer& text );

/**
 * @brief Dessine un visualiseur d'image
 * @param text ImageViewer à dessiner
 * @param width Largeur de l'écran
 * @param height Hauteur de l'écran
 * @param x Position horizontale de l'image
 * @param y Position verticale de l'image
 * @param scaleX Facteur d'échelle horizontal
 * @param scaleY Facteur d'échelle vertical
 */
void draw( const ImageViewer& text, const int width, const int height , int x, int y, float scaleX, float scaleY);

/**
 * @brief Dessine un visualiseur d'image recadrée
 * @param text ImageViewer à dessiner
 * @param width Largeur de l'écran
 * @param height Hauteur de l'écran
 * @param x Position horizontale de l'image
 * @param y Position verticale de l'image
 * @param scaleX Facteur d'échelle horizontal
 * @param scaleY Facteur d'échelle vertical
 * @param coefMinX Coefficient de découpe minimal horizontal
 * @param coefMinY Coefficient de découpe minimal vertical
 * @param coefMaxX Coefficient de découpe maximal horizontal
 * @param coefMaxY Coefficient de découpe maximal vertical
 */
void draw_crop( const ImageViewer& text, const int width, const int height , int x, int y, float scaleX, float scaleY, float coefMinX, float coefMinY, float coefMaxX, float coefMaxY);

/**
 * @brief Dessine un arrière-plan avec un visualiseur d'image
 * @param text ImageViewer à utiliser comme arrière-plan
 * @param width Largeur de l'écran
 * @param height Hauteur de l'écran
 */
void draw_background( const ImageViewer& text, const int width, const int height);

#endif