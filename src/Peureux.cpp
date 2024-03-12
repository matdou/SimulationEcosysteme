#include "Peureux.h"
#include "BestioleFactory.h"

static bool dummy = []() {
    BestioleFactory::registerType("Peureux", []() -> Bestiole* { return new Peureux(); });
    return true;
}();

Peureux::Peureux() {

    // Change color to blue
    setCouleur(0, 0, 255);
}
