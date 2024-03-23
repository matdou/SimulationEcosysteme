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
}

Peureuse::~Peureuse() {
    // Destructor
}

void Peureuse::update(
    const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    this->setCouleur(0, 0, 255);  // blue when

    if (voisins.size() >= 3) {
        setCouleur(150, 0, 150);  // purple when there are 3 or more neighbors

        if (turnCooldown == 0) {
            setVitesse(10);
            setOrientation(getOrientation() + M_PI);
            turnCooldown = 20;
        }
    }

    if (turnCooldown > 0) {
        turnCooldown--;
        setCouleur(0, 0, 150);  // dark blue when the cooldown is active
    } else {
        setVitesse(getInitialMultipliedVitesse());  // reset the speed
    }
}

std::unique_ptr<Bestiole> Peureuse::clone() const {
    return std::make_unique<Peureuse>(*this);
}
