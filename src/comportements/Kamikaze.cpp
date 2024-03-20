#include "Kamikaze.h"

#include "BestioleFactory.h"
#include "Capteur.h"

static bool dummy = []() {
    BestioleFactory::registerType("Kamikaze",
                                  []() -> Bestiole* { return new Kamikaze(); });
    return true;
}();

Kamikaze::Kamikaze() {
    setCouleur(255, 0, 0);
    setVitesse(10);
}

Kamikaze::~Kamikaze() {
    // Destructor
}

void Kamikaze::update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    // Implementation specific to Kamikaze
}

std::unique_ptr<Bestiole> Kamikaze::clone() const {
    return std::make_unique<Kamikaze>(*this);
}