#ifndef SCENE_H
#define SCENE_H

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

#include "image_viewer.h"
#include "buttons.h"
#include "widgets.h"
#include "widget_point.h"

/**
 * @brief Représente une scène de jeu.
 */
class Scene : public AppCamera {
private:
    std::vector<std::vector<Point>> tilePosition; //!< Positions des tuiles dans la scène.
    std::vector<std::vector<std::vector<Triangle>>> triangles; //!< Triangles définissant la géométrie de la scène.
    bool initCamera = true; //!< Indique si la caméra doit être initialisée.
    bool click = false; //!< Indique si un clic a été effectué.
    bool turnLeft = false; //!< Indique si la rotation de la caméra vers la gauche est demandée.
    bool turnRight = false; //!< Indique si la rotation de la caméra vers la droite est demandée.
    bool firework = false; //!< Indique si le feu d'artifice est activé.
    bool select = false; //!< Indique si une tuile est sélectionnée.
    int level = 0; //!< Niveau de la scène.
    bool distribAttributePoint = true; //!< Indique si la distribution des points d'attribut est active.
    bool play = false;

public:
    /**
     * @brief Constructeur par défaut de la classe Scene.
     */
    Scene();

    /**
     * @brief Initialise la scène.
     * @return Code d'erreur.
     */
    int init();

    /**
     * @brief Quitte la scène.
     * @return Code d'erreur.
     */
    int quit();

    /**
     * @brief Met à jour la scène.
     * @param time Temps écoulé depuis le début de la scène.
     * @param delta Temps écoulé depuis la dernière mise à jour.
     * @return Code d'erreur.
     */
    int update(const float time, const float delta);

    /**
     * @brief Rendu de la scène.
     * @return Code d'erreur.
     */
    int render();

    /**
     * @brief Interpolation entre deux points.
     * @param a Premier point.
     * @param b Deuxième point.
     * @param t Facteur d'interpolation.
     * @return Point interpolé.
     */
    Point interpolate(Point a, Point b, float t);

    /**
     * @brief Initialise la position de la caméra.
     * @param camera Caméra à initialiser.
     * @param x Position x initiale.
     * @param y Position y initiale.
     * @return Caméra initialisée.
     */
    Orbiter initPosCamera(Orbiter& camera, int x, int y);

    /**
     * @brief Calcule l'angle de rotation.
     * @param posActuelle Position actuelle.
     * @param posCible Position cible.
     * @return Angle de rotation.
     */
    float calculateRotationAngle(Point posActuelle, Point posCible);
 
    /**
     * @brief Conversion de coordonnées en fonction de la caméra.
     * @param camera Caméra.
     * @param point Point à convertir.
     * @return Point converti.
     */
    Point Canva_Point(Orbiter camera, Point point);

    /**
     * @brief Sélection d'une tuile pour le déplacement.
     * @param offset Décalage de la sélection.
     * @param width Largeur de l'écran.
     * @param height Hauteur de l'écran.
     * @param t Transform de la tuile sélectionnée.
     * @param m_texture Identifiant de la texture de la tuile.
     */
    void Select_Tile_Move(float offset, int width, int height, Transform& t, GLuint m_texture);

    /**
     * @brief Sélection d'une tuile pour le lancement d'un sort.
     * @param offset Décalage de la sélection.
     * @param width Largeur de l'écran.
     * @param height Hauteur de l'écran.
     * @param t Transform de la tuile sélectionnée.
     * @param m_texture Identifiant de la texture de la tuile.
     */
    void Select_Tile_Spell(float offset, int width, int height, Transform& t, GLuint m_texture);

    /**
     * @brief Initialisation de la grille de triangles.
     * @param width Largeur de la grille.
     * @param height Hauteur de la grille.
     */
    void Init_Triangle_grid(int width, int height);

    /**
     * @brief Mise à jour des monstres dans la scène.
     * @param width Largeur de l'écran.
     * @param height Hauteur de l'écran.
     */
    void Monster_Update(int width, int height);

    /**
     * @brief Utilisation d'une texture.
     * @param t Transform de l'objet à texturer.
     * @param m_texture Identifiant de la texture.
     */
    void Use_Texture(Transform t, GLuint m_texture);
    
    /**
     * @brief Mise à jour du joueur dans la scène.
     * @param width Largeur de l'écran.
     * @param height Hauteur de l'écran.
     */
    void Update_Player(int width, int height);

    /**
     * @brief Dessin des attributs.
     * @param widgets Widgets utilisés pour le dessin.
     * @param width Largeur de l'écran.
     * @param height Hauteur de l'écran.
     * @param color Couleur des attributs.
     * @param text Texte des attributs.
     */
    void draw_attribute(Widgets widgets, int width, int height, const Color& color, int text);

    /**
     * @brief Dessin du portrait du joueur.
     */
    void draw_portrait();

    /**
     * @brief Dessin de la grille.
     * @param width Largeur de l'écran.
     * @param height Hauteur de l'écran.
     */
    void draw_grid(int width, int height);

    /**
     * @brief Interaction avec les boutons de la scène.
     */
    void interactedButtonScene(); 

    /**
     * @brief Dessin des éléments 2D de la scène.
     * @param mb Bouton de la souris enfoncé.
     * @param mousex Position x de la souris.
     * @param mousey Position y de la souris.
     */
    void draw_element2d_scene(int mb, int mousex, int mousey);

    /**
     * @brief Initialisation des boutons de la scène.
     */
    void init_button_scene();


protected:
    WidgetPoint w_point; //!< Widget point utilisé dans la scène.

    Widgets t_pm; //!< Widgets pour la gestion du point de mouvement.
    Widgets t_pa; //!< Widgets pour la gestion du point d'attaque.

    Button b_endRound; //!< Bouton pour terminer le tour.
    Button b_turnLeft; //!< Bouton pour tourner la caméra vers la gauche.
    Button b_turnRight; //!< Bouton pour tourner la caméra vers la droite.
    Button b_firework; //!< Bouton pour activer le feu d'artifice.
    Button b_play;

    ImageViewer i_health; //!< Visionneuse pour la santé du joueur.
    ImageViewer i_turnLeft ; //!< Visionneuse pour la rotation de la caméra vers la gauche.
    ImageViewer i_turnRight ; //!< Visionneuse pour la rotation de la caméra vers la droite.
    ImageViewer i_passed ; //!< Visionneuse pour le passage.
    ImageViewer i_HUD ; //!< Visionneuse pour l'interface utilisateur.
    ImageViewer i_background; //!< Visionneuse pour l'arrière-plan.
    ImageViewer i_firework; //!< Visionneuse pour le feu d'artifice.
    ImageViewer i_portrait; //!< Visionneuse pour le portrait du joueur.
    ImageViewer i_health_m; //!< Visionneuse pour la santé du monstre.
    ImageViewer i_xp_bar; //!< Visionneuse pour la barre d'expérience.
    ImageViewer i_play;
    ImageViewer i_accueil;

    Mesh m_grid; //!< Maillage pour la grille.
    Mesh m_alph; //!< Maillage pour l'élément ALPH.
    Mesh m_monstre; //!< Maillage pour l'élément MONSTRE.
    Mesh m_death; //!< Maillage pour l'élément DEATH.

    Game game; //!< Instance du jeu.

    GLuint m_texture1; //!< Identifiant de texture 1.
    GLuint m_texture2; //!< Identifiant de texture 2.
    GLuint m_texture3; //!< Identifiant de texture 3.
    GLuint m_texture4; //!< Identifiant de texture 4.
    GLuint m_belze; //!< Identifiant de texture 5.
    GLuint m_ogrest; //!< Identifiant de texture 6.
    GLuint m_program; //!< Identifiant du programme.
    Transform m_model; //!< Transform du modèle.
    std::vector<Color> m_colors; //!< Vecteur de couleurs.

};

#endif // SCENE_H
