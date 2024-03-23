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
    this->setCouleur(0, 255, 0);  // Set the color to green
    if (!voisins.empty()) {
        this->setCouleur(
            0, 200, 0);  // Set the color to dark green when there are neighbors
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

        double newOrientation = getOrientation() + direction_diff / 7;
        setOrientation(newOrientation);
    }
}

std::unique_ptr<Bestiole> Gregaire::clone() const {
    return std::make_unique<Gregaire>(*this);
}
