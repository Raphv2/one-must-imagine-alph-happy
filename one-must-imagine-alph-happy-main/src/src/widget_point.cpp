#include "widget_point.h"

// Constructeur par défaut de la classe WidgetPoint
WidgetPoint::WidgetPoint() : pointView(5), realPointView(5), b_flecheRight(5), b_flecheLeft(5){
    point = 10;
    save = false;
    i_widget = create_ImageViewer("asset/widget_point.png");
    i_save = create_ImageViewer("asset/save.png");
    i_right = create_ImageViewer("asset/right.png");
    i_left = create_ImageViewer("asset/left.png");

    for(int i = 0; i< pointView.size(); i++){
        pointView[i] = 0;
        realPointView[i] = 0;
    }

    widgets = create_widgets();
    
    
}

// Initialisation des widgets dans l'interface graphique
void WidgetPoint::Init_Widget(int width, int height){
    for(int i = 0; i< b_flecheRight.size(); i++){
        b_flecheRight[i].initButton(i_right, width/8 *4.8, height/8 * 3.3 + i *72, 1., 1.);
        b_flecheLeft[i].initButton(i_left, width/8 * 3, height/8 * 3.3 + i *72, 1., 1.);
    }

    b_save.initButton(i_save, width/2 - i_save.width /2.1 , height/8 * 6.7, 1., 1.);
}

// Libération des ressources utilisées par les widgets
void WidgetPoint::Release_Widget(){
    release_ImageViewer(i_widget);
    release_ImageViewer(i_save);
    release_ImageViewer(i_right);
    release_ImageViewer(i_left);
    release_widgets(widgets);
}

// Séparation des points pour la distribution
void WidgetPoint::PointSplit(int width, int height, int mousex, int mousey, int mb, bool& open, Player& player){
    draw_background(i_widget, width, height);
    
    // Affichage et gestion des boutons de sélection vers la gauche
    draw_button(b_flecheLeft[0], width, height);
    b_flecheLeft[0].interacted(leftHealth, mousex, mousey, mb);
    draw_button(b_flecheLeft[1], width, height);
    b_flecheLeft[1].interacted(leftInitiative, mousex, mousey, mb);
    draw_button(b_flecheLeft[2], width, height);
    b_flecheLeft[2].interacted(leftRange, mousex, mousey, mb);
    draw_button(b_flecheLeft[3], width, height);
    b_flecheLeft[3].interacted(leftMove, mousex, mousey, mb);
    draw_button(b_flecheLeft[4], width, height);
    b_flecheLeft[4].interacted(leftAction, mousex, mousey, mb);

    // Affichage et gestion des boutons de sélection vers la droite
    draw_button(b_flecheRight[0], width, height);
    b_flecheRight[0].interacted(rightHealth, mousex, mousey, mb);    
    draw_button(b_flecheRight[1], width, height);
    b_flecheRight[1].interacted(rightInitiative, mousex, mousey, mb);   
    draw_button(b_flecheRight[2], width, height);
    b_flecheRight[2].interacted(rightRange, mousex, mousey, mb);   
    draw_button(b_flecheRight[3], width, height);
    b_flecheRight[3].interacted(rightMove, mousex, mousey, mb);   
    draw_button(b_flecheRight[4],width, height);
    b_flecheRight[4].interacted(rightAction, mousex, mousey, mb);   
    
    // Affichage et gestion du bouton de sauvegarde
    draw_button(b_save, width, height );
    b_save.interacted(save, mousex, mousey, mb);

    // Attribution des points selon les actions des boutons
    // et mise à jour des statistiques du joueur
    if(rightHealth && point > 0){
        awardPoints(pointView[0]);
        rightHealth = false;
        
    }
    if(leftHealth && pointView[0] > 0){
        deductPoints(pointView[0]);
        leftHealth = false;
        
    }



    if(rightInitiative && point > 0){
        awardPoints(pointView[1]);
        rightInitiative = false;
        
    }
    if(leftInitiative && pointView[1] > 0){
        deductPoints(pointView[1]);
        leftInitiative = false;
        
    }

    if(rightRange && point > 0){
        awardPoints(pointView[2]);
        rightRange = false;
        
    }
    if(leftRange && pointView[2] > 0){
        deductPoints(pointView[2]);
        leftRange = false;
        
    }


    if(rightMove && point > 0){
        awardPoints(pointView[3]);
        rightMove = false;
        
    }
    if(leftMove && pointView[3] > 0){
        deductPoints(pointView[3]);
        leftMove = false;
        
    }

     if(rightAction && point > 0){
        awardPoints(pointView[4]);
        rightAction = false;
        
    }
    if(leftAction && pointView[4] > 0){
        deductPoints(pointView[4]);
        leftAction = false;
        
    }

    // Affichage des points distribués et restants
    for(int i = 0; i< pointView.size(); i++){
        draw_point(widgets, width/8 *6., height/8 * 5.1 - i *72, Color(0.1f,0.1f,0.1f,1.f) , realPointView[i] + pointView[i]);
    }
    draw_point(widgets, width/8 *6., height/8 * 2.5, Color(0.1f,0.1f,0.1f,1.f) , point);

    
    // Sauvegarde des points attribués si tous les points sont distribués
    if(save && point == 0){
        
        // Mise à jour des statistiques du joueur
        for(int i =0; i > realPointView.size(); i++){
            realPointView[i] += pointView[i];
            pointView[i] = 0;
        } 

        player.attEntity.addStat(HEALTH, pointView[0] * 20);
        player.statActuelles.addStat(HEALTH, pointView[0] * 20);

        player.attEntity.addStat(INITIATIVE, pointView[1] * 10);
        player.statActuelles.addStat(INITIATIVE, pointView[1] * 10);

        player.attEntity.addStat(RANGE_POINT, pointView[2]);
        player.statActuelles.addStat(RANGE_POINT, pointView[2]);

        player.attEntity.addStat(MOVEMENT_POINT, pointView[3]);
        player.statActuelles.addStat(MOVEMENT_POINT, pointView[3]);

        player.attEntity.addStat(ACTION_POINT, pointView[4]);
        player.statActuelles.addStat(ACTION_POINT, pointView[4]);
        
        open = false;
        save = false;
    }
}

// Dessine un point sur l'interface graphique
void WidgetPoint::draw_point(Widgets widgets, int width, int height, const Color& color , int text)
{

    begin(widgets);
        begin_line(widgets);
        default_color(  widgets,  color );
        label(widgets, "%d", text);
    end(widgets);
    
    // afficher l'interface
    draw(widgets, width, height);

}

