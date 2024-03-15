#include "Kamikaze.h"
#include "BestioleFactory.h"

static bool dummy = []() {
    BestioleFactory::registerType("Kamikaze",
                                  []() -> Bestiole* { return new Kamikaze(); });
    return true;
}();

Kamikaze::Kamikaze() {
    setCouleur(255, 0, 0);
    setVitesse(10);
}
