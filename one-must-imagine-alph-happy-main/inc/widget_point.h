#ifndef WIDGET_POINT_H
#define WIDGET_POINT_H

#include "image_viewer.h"
#include "buttons.h"
#include "player.h"
#include "widgets.h"
#include "color.h"

/**
 * @brief Cette classe gère un widget permettant d'attribuer des points aux attributs d'un joueur.
 */
class WidgetPoint  {


public:
    /**
     * @brief Constructeur par défaut.
     */
    WidgetPoint();

    /**
     * @brief Initialise le widget avec une taille spécifiée.
     * @param width La largeur du widget.
     * @param height La hauteur du widget.
     */
    void Init_Widget(int width, int height);

    /**
     * @brief Libère les ressources du widget.
     */
    void Release_Widget();

    /**
     * @brief Répartit les points attribuables sur les attributs du joueur.
     * @param width La largeur de l'écran.
     * @param height La hauteur de l'écran.
     * @param mousex La position X de la souris.
     * @param mousey La position Y de la souris.
     * @param mb Le bouton de la souris enfoncé.
     * @param open Indique si le widget est ouvert.
     * @param player Le joueur à modifier.
     */
    void PointSplit(int width, int height, int mousex, int mousey, int mb, bool& open, Player &player);

    /**
     * @brief Dessine le widget des points.
     * @param widgets Les widgets disponibles.
     * @param width La largeur de l'écran.
     * @param height La hauteur de l'écran.
     * @param color La couleur à utiliser.
     * @param text Le texte à afficher.
     */
    void draw_point(Widgets widgets, int width, int height, const Color& color , int text);

    /**
     * @brief Augmente le nombre de points attribuables.
     * @param points Le nombre de points à attribuer.
     */
    void awardPoints(int& points) {
        points++;
        point--;
    }

    /**
     * @brief Diminue le nombre de points attribuables.
     * @param points Le nombre de points à retirer.
     */
    void deductPoints(int& points) {
        points--;
        point++;
    }

    /**
     * @brief Définit le nombre de points attribuables.
     * @param value La valeur à définir.
     */
    void setPoint(int value){point += value;}
   

private:
    int point; //!< Le nombre de points attribuables.
    std::vector<bool> right; //!< Indique si le côté droit est sélectionné.
    std::vector<bool> left; //!< Indique si le côté gauche est sélectionné.
    bool rightHealth = false; //!< Indique si la santé du côté droit est sélectionnée.
    bool rightInitiative = false; //!< Indique si l'initiative du côté droit est sélectionnée.
    bool rightRange = false; //!< Indique si la portée du côté droit est sélectionnée.
    bool rightMove = false; //!< Indique si le mouvement du côté droit est sélectionné.
    bool rightAction = false; //!< Indique si l'action du côté droit est sélectionnée.
    bool leftHealth = false; //!< Indique si la santé du côté gauche est sélectionnée.
    bool leftInitiative = false; //!< Indique si l'initiative du côté gauche est sélectionnée.
    bool leftRange = false; //!< Indique si la portée du côté gauche est sélectionnée.
    bool leftMove = false; //!< Indique si le mouvement du côté gauche est sélectionné.
    bool leftAction = false; //!< Indique si l'action du côté gauche est sélectionnée.
    std::vector<int> pointView; //!< Les points à afficher.
    std::vector<int> realPointView; //!< Les points réels à afficher.
    bool save; //!< Indique si les changements doivent être sauvegardés.

    ImageViewer i_widget; //!< Visionneuse d'images pour le widget.
    ImageViewer i_right; //!< Visionneuse d'images pour le côté droit.
    ImageViewer i_left; //!< Visionneuse d'images pour le côté gauche.
    ImageViewer i_save; //!< Visionneuse d'images pour la sauvegarde.

    std::vector<Button> b_flecheRight; //!< Boutons de flèche pour le côté droit.
    std::vector<Button> b_flecheLeft; //!< Boutons de flèche pour le côté gauche.
    Button b_save; //!< Bouton de sauvegarde.

    Widgets widgets; //!< Les widgets disponibles.
    
};

#endif // WIDGET_POINT_H