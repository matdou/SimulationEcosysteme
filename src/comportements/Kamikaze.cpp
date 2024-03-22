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
    setVitesse(2);
}

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
        if (voisins.size() >= 1) {
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

        }

        if (closestNeighbour != nullptr) {
            // calculate angle to closest Neighbour
            double angle = atan2(closestNeighbour->getY() - getY(),
                                 closestNeighbour->getX() - getX());
            double angleDifference = angle - getOrientation();

            if (angleDifference > M_PI) {
                angleDifference -= 2 * M_PI;
            } else if (angleDifference < -M_PI) {
                angleDifference += 2 * M_PI;
            }

            double newOrientation;
            if (abs(angleDifference) > 1) {
                newOrientation = getOrientation() + angleDifference / 5;
            } else {
                newOrientation = getOrientation() + angleDifference / 10;
            }
            setOrientation(newOrientation);
        }
    }
}


std::unique_ptr<Bestiole> Kamikaze::clone() const {
    return std::make_unique<Kamikaze>(*this);
}