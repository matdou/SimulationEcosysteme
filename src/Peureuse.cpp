#include "Peureuse.h"
#include "BestioleFactory.h"

static bool dummy = []() {
    BestioleFactory::registerType("Peureuse",
                                  []() -> Bestiole* { return new Peureuse(); });
    return true;
}();

Peureuse::Peureuse() {
    // Change color to blue
    setCouleur(0, 0, 255);
}
