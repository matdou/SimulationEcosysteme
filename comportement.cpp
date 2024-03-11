#include "Comportement.h"

void ComportementPeureux::appliquer(Bestiole& bestiole) {
    bestiole.setVitesse(bestiole.getVitesse() * 0.2);
}

void ComportementKamikaze::appliquer(Bestiole& bestiole) {
    bestiole.setVitesse(bestiole.getVitesse() * 2);
}

void ComportementGregaire::appliquer(Bestiole& bestiole) {
    bestiole.setVitesse(bestiole.getVitesse() * 1.5);
}
