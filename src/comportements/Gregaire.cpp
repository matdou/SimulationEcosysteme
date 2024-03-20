#include "Gregaire.h"

#include "BestioleFactory.h"

static bool dummy = []() {
    BestioleFactory::registerType("Gregaire",
                                  []() -> Bestiole* { return new Gregaire(); });
    return true;
}();

Gregaire::Gregaire() { setCouleur(0, 255, 0); }
