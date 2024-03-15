#include "BestioleKamikaze.h"
#include "Milieu.h" // Inclure la définition de la classe Milieu

void BestioleKamikaze::bouge(Milieu & monMilieu) {
    double nx, ny;
    int cx, cy;
    int xLim = monMilieu.getWidth();
    int yLim = monMilieu.getHeight();
    const Bestiole* bestioleProche = nullptr;
    double distanceMin = std::numeric_limits<double>::max();

    // Recherche de la bestiole la plus proche
    for (const Bestiole& autreBestiole : monMilieu.getlisteBestioles()) {
        if (!(&autreBestiole == this)) {
            double distance = sqrt(pow(autreBestiole.getx() - x, 2) + pow(autreBestiole.gety() - y, 2));
            if (distance < distanceMin) {
                distanceMin = distance;
                bestioleProche = &autreBestiole;
            }
        }
    }

    // Vérifier si une bestiole proche a été trouvée
    // Calcul de la nouvelle direction vers la bestiole la plus proche
    double nouvelle_direction = atan2(bestioleProche->gety() - y, bestioleProche->getx() - x);
    
    orientation = nouvelle_direction;
    // Calcul des composantes de déplacement en fonction de la direction vers la bestiole la plus proche
    double dx = cos(nouvelle_direction) * vitesse;
    double dy = sin(nouvelle_direction) * vitesse;

    cx = static_cast<int>(cumulX); cumulX -= cx;
    cy = static_cast<int>(cumulY); cumulY -= cy;

    nx = x + dx + cx;
    ny = y + dy + cy;

    // Gestion des limites de l'environnement
    if ((nx < 0) || (nx > xLim - 1)) {
        orientation = M_PI - orientation;
        cumulX = 0.;
    }
    else {
        x = static_cast<int>(nx);
        cumulX += nx - x;
    }

    if ((ny < 0) || (ny > yLim - 1)) {
        orientation = -orientation;
        cumulY = 0.;
    }
    else {
        y = static_cast<int>(ny);
        cumulY += ny - y;
    }
}
 

