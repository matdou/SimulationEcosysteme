#include "Prevoyante.h"

#include "BestioleFactory.h"

static bool dummy = []() {
    BestioleFactory::registerType(
        "Prevoyante", []() -> Bestiole* { return new Prevoyante(); });
    return true;
}();

Prevoyante::Prevoyante() {
    setCouleur(255, 255, 0);  // Jaune
}
