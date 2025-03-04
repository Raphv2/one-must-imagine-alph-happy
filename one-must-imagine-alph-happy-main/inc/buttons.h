#ifndef _BUTTONS_H
#define _BUTTONS_H

#include <iostream>
#include <vector>
#include "image_viewer.h"
#include <vector>
#include "wavefront.h"
#include "texture.h"
#include "orbiter.h"
#include "draw.h"
#include "app_camera.h"
#include "game.h"
#include "program.h"
#include "uniforms.h"
#include "mat.h"
#include "mesh.h"
#include "ray.h"
#include "color.h"
#include "vec.h"
#include <cfloat>

/**
 * @brief Structure représentant un rectangle
 * @param x1 Coordonnée x du coin supérieur gauche
 * @param y1 Coordonnée y du coin supérieur gauche
 * @param x2 Coordonnée x du coin inférieur droit
 * @param y2 Coordonnée y du coin inférieur droit
 * @param w Largeur du rectangle
 * @param h Hauteur du rectangle
 */
struct Rect
{
    int x1, y1, x2, y2;
    int w, h;
};

/**
 * @brief Classe représentant un bouton
 */
class Button{
    public:
        /**
         * @brief Constructeur par défaut
         */
        Button( ) : imageViewer(), buttonDimension(), x(0), y(0), scaleX(1.), scaleY(1.){}

        /**
         * @brief Initialise le bouton avec une image, des dimensions et une échelle
         * @param imageViewern ImageViewer de l'image du bouton
         * @param xn Coordonnée x du bouton
         * @param yn Coordonnée y du bouton
         * @param scaleXn Echelle en x du bouton
         * @param scaleYn Echelle en y du bouton
         */
        void initButton(const ImageViewer& imageViewern,  int xn, int yn, float scaleXn, float scaleYn);
        
        ImageViewer getImageViewer() const { return imageViewer;}
        Rect getButtonDimension() const { return buttonDimension;}
        int getx() const { return x;}
        int gety() const { return y;}
        int getScaleX() const { return scaleX;}
        int getScaleY() const { return scaleY;}
        
        /**
         * @brief Gère l'interaction avec le bouton (clic et relâchement de souris) en vérifiant la position du curseur
         * @param status Statut de l'interaction (true si le bouton est enfoncé)
         * @param mouseX Coordonnée x du curseur
         * @param mouseY Coordonnée y du curseur
         * @param mb Bouton de la souris utilisé
         * @param area Booléen indiquant si le curseur se trouve dans la zone du bouton
         */
        void interacted(bool& status, int mouseX, int mouseY, int mb, bool& area);

        /**
         * @brief Gère l'interaction avec le bouton (clic et relâchement de souris) en vérifiant la position du curseur
         * @param status Statut de l'interaction (true si le bouton est enfoncé)
         * @param mouseX Coordonnée x du curseur
         * @param mouseY Coordonnée y du curseur
         * @param mb Bouton de la souris utilisé
         */
        void interacted(bool& status, int mouseX, int mouseY, int mb);

        /**
         * @brief Gère l'interaction avec le bouton (clic et maintien enfoncé) en vérifiant la position du curseur
         * @param status Statut de l'interaction (true si le bouton est enfoncé)
         * @param mouseX Coordonnée x du curseur
         * @param mouseY Coordonnée y du curseur
         * @param mb Bouton de la souris utilisé
         */
        void interacted2(bool& status, int mouseX, int mouseY, int mb);

    private:
        Rect buttonDimension; ///< Dimensions du bouton
        ImageViewer imageViewer; ///< ImageViewer de l'image du bouton
        int x; ///< Coordonnée x du bouton
        int y; ///< Coordonnée y du bouton
        int scaleX; ///< Echelle en x du bouton
        int scaleY; ///< Echelle en y du bouton
};

/**
 * @brief Dessine un bouton sur l'écran
 * @param button Bouton à dessiner
 * @param width Largeur de l'écran
 * @param height Hauteur de l'écran
 */
void draw_button(Button button, const int width, const int height);

#endif 