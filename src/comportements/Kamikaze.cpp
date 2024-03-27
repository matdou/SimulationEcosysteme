#include "Kamikaze.h"

#include "BestioleFactory.h"
#include "Capteur.h"

static bool dummy = []() {
    BestioleFactory::registerType("Kamikaze",
                                  []() -> Bestiole* { return new Kamikaze(); });
    return true;
}();

Kamikaze::Kamikaze() { setCouleur(255, 0, 0); }

Kamikaze::~Kamikaze() {
    // Destructor
}

void Kamikaze::update(
    const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    Comportement::kamikazeUpdate(voisins);
}

std::unique_ptr<Bestiole> Kamikaze::clone() const {
    return std::make_unique<Kamikaze>(*this);
}