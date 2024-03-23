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
    setCouleur(255, 0, 0);
    if (!voisins.empty()) {
        setCouleur(200, 0, 0);
        // find closest Neighbour
        Bestiole* closestNeighbour = nullptr;
        double minDistance = 1000000;
        for (const auto& voisinRef : voisins) {
            Bestiole& voisin = voisinRef.get();
            double distance = sqrt(pow(voisin.getX() - getX(), 2) +
                                   pow(voisin.getY() - getY(), 2));
            if (distance < minDistance) {
                minDistance = distance;
                closestNeighbour = &voisin;
            }
        }
        double deltaX = closestNeighbour->getX() - getX();
        double deltaY = closestNeighbour->getY() - getY();

        double newDirection = -std::atan2(deltaY, deltaX);

        while (newDirection >= M_PI) {
            newDirection -= 2.0 * M_PI;
        }
        while (newDirection < -M_PI) {
            newDirection += 2.0 * M_PI;
        }

        double diff_orientation = newDirection - getOrientation();

        while (diff_orientation >= M_PI) {
            diff_orientation -= 2.0 * M_PI;
        }
        while (diff_orientation < -M_PI) {
            diff_orientation += 2.0 * M_PI;
        }

        setOrientation(getOrientation() + diff_orientation / 10);
    }
}

std::unique_ptr<Bestiole> Kamikaze::clone() const {
    return std::make_unique<Kamikaze>(*this);
}