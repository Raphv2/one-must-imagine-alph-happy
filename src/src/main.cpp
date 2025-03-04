#include <iostream>
#include "scene.h"
#include "consoleDisplay.h"


// Fonction principale
int main()
{
    // Crée une instance de ConsoleDisplay pour afficher dans la console
    ConsoleDisplay consoleDisplay;

    // Crée une instance de Scene pour gérer la logique du jeu
    Scene scene;
    
    // Initialise le jeu dans la console
    consoleDisplay.initGameTest();
 
    // Lance la boucle principale du jeu
    scene.run();


    // Termine le programme
    return 0;

}


