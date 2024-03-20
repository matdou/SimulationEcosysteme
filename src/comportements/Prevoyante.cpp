#include "Prevoyante.h"

#include "BestioleFactory.h"
#include "Capteur.h"

static bool dummy = []() {
    BestioleFactory::registerType(
        "Prevoyante", []() -> Bestiole* { return new Prevoyante(); });
    return true;
}();

Prevoyante::Prevoyante() {
    setCouleur(255, 255, 0);  // Jaune
}

Prevoyante::~Prevoyante() {
    // Destructor
}

void Prevoyante::update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    // On ne fait rien
}

std::unique_ptr<Bestiole> Prevoyante::clone() const {
    return std::make_unique<Prevoyante>(*this);
}

