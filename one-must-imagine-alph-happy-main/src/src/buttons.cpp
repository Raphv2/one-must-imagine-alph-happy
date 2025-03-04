
#include "buttons.h" // Inclure le fichier d'en-tête contenant les déclarations nécessaires

void Button::initButton(const ImageViewer& imageViewern, int xn, int yn, float scaleXn, float scaleYn) {
    // Initialise les paramètres du bouton avec les valeurs fournies
    x = xn;
    y = yn;
    scaleX = scaleXn;
    scaleY = scaleYn;
    imageViewer = imageViewern;
    buttonDimension.w = static_cast<int>(imageViewer.width * scaleXn);
    buttonDimension.h = static_cast<int>(imageViewer.height * scaleYn);
    buttonDimension.x1 = x;
    buttonDimension.y1 = y;
    buttonDimension.x2 = x + buttonDimension.w;
    buttonDimension.y2 = y - buttonDimension.h;
    
}

void draw_button(Button button, const int width, const int height) {
    // Dessine le bouton sur l'écran avec la fonction draw en utilisant les informations du bouton
    draw(button.getImageViewer(), width, height, button.getx(), button.gety(), button.getScaleX(), button.getScaleY()); // Assumant draw est correctement définie
}

void Button::interacted(bool& status, int mouseX, int mouseY, int mb, bool & area) {
    // Vérifie si la souris interagit avec le bouton et modifie le statut du bouton si nécessaire
    if (mouseX >= buttonDimension.x1 && mouseX <= buttonDimension.x2 &&
        mouseY <= buttonDimension.y1 && mouseY >= buttonDimension.y2) {
        area = true;    
        
        if (mb & SDL_BUTTON(SDL_BUTTON_LEFT)) { // Utiliser SDL_BUTTON_LEFT pour le bouton gauche de la souris
            status = true;
        }
    }
    else area = false;
    
}
void Button::interacted2(bool& status, int mouseX, int mouseY, int mb) {
    // Vérifie si la souris interagit avec le bouton et modifie le statut du bouton si nécessaire
    if (mouseX >= buttonDimension.x1 && mouseX <= buttonDimension.x2 &&
        mouseY <= buttonDimension.y1 && mouseY >= buttonDimension.y2) {
           
        
        if (mb & SDL_BUTTON(SDL_BUTTON_LEFT) && !status) { // Utiliser SDL_BUTTON_LEFT pour le bouton gauche de la souris
            status = true;
        }
    }
    
}
void Button::interacted(bool& status, int mouseX, int mouseY, int mb) {
    // Vérifie si la souris interagit avec le bouton et modifie le statut du bouton si nécessaire,
    // en maintenant le suivi de l'état précédent pour éviter les interactions répétées
    static bool previousState = false; 

    if (mouseX >= buttonDimension.x1 && mouseX <= buttonDimension.x2 &&
        mouseY <= buttonDimension.y1 && mouseY >= buttonDimension.y2) {
           
        
        if ((mb & SDL_BUTTON(SDL_BUTTON_LEFT)) && !previousState) {
            status = !status; 
            previousState = true; 
        } else if (!(mb & SDL_BUTTON(SDL_BUTTON_LEFT))) {
            previousState = false; 
        }
    }
}