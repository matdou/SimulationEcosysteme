#include "Peureuse.h"

#include "BestioleFactory.h"
#include "Capteur.h"

static bool dummy = []() {
    BestioleFactory::registerType("Peureuse",
                                  []() -> Bestiole* { return new Peureuse(); });
    return true;
}();

Peureuse::Peureuse() {
    // Change color to blue
    setCouleur(0, 0, 255);
    setVitesse(1);
}

Peureuse::~Peureuse() {
    // Destructor
}

void Peureuse::update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    
}

std::unique_ptr<Bestiole> Peureuse::clone() const {
    return std::make_unique<Peureuse>(*this);
}

