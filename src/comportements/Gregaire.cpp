#include "Gregaire.h"

#include "BestioleFactory.h"
#include "Capteur.h"

static bool dummy = []() {
    BestioleFactory::registerType("Gregaire",
                                  []() -> Bestiole* { return new Gregaire(); });
    return true;
}();

Gregaire::Gregaire() {
    setCouleur(0, 255, 0);
    setVitesse(2);
    }

// Destructor
Gregaire::~Gregaire() {
}



// Update the behavior of the Gregaire Bestiole
void Gregaire::update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    this->setCouleur(0, 255, 0); // Set the color to green
    if (!voisins.empty()) {
        this->setCouleur(0, 155, 0); // Set the color to dark green
        double directionMoyenne = 0.0;
        for (const auto& voisinRef : voisins) {
            Bestiole& voisin = voisinRef.get();
            directionMoyenne += voisin.getOrientation();
        }

        directionMoyenne /= voisins.size();

        double currentDirection = getOrientation();

        double direction_diff = directionMoyenne - currentDirection;

        if (direction_diff > M_PI) {
            direction_diff -= 2 * M_PI;
        } else if (direction_diff < -M_PI) {
            direction_diff += 2 * M_PI;
        }

        if (direction_diff > 0) {
            setCouleur(255,0,0);
        } else {
            setCouleur(0,0,255);
        }

        double newOrientation = getOrientation() + direction_diff/10;
        setOrientation(newOrientation);

    }
}


std::unique_ptr<Bestiole> Gregaire::clone() const {
    return std::make_unique<Gregaire>(*this);
}


