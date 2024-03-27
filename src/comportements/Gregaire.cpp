#include "Gregaire.h"

#include "BestioleFactory.h"
#include "Capteur.h"

static bool dummy = []() {
    BestioleFactory::registerType("Gregaire",
                                  []() -> Bestiole* { return new Gregaire(); });
    return true;
}();

Gregaire::Gregaire() { setCouleur(0, 255, 0); }

// Destructor
Gregaire::~Gregaire() {}

// Update the Orientation of the Bestiole based on the average orientation of
// its neighbors
void Gregaire::update(
    const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    Comportement::gregaireUpdate(voisins);
}

std::unique_ptr<Bestiole> Gregaire::clone() const {
    return std::make_unique<Gregaire>(*this);
}
