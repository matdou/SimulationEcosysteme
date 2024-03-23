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

void Prevoyante::update(
    const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    setCouleur(255, 255, 0);
    if (!voisins.empty()) {
        setCouleur(200, 200, 0);
        double sumX = 0;
        double sumY = 0;
        for (const auto& voisinRef : voisins) {
            // Find a projected position of the neighbor
            double directionVoisin = voisinRef.get().getOrientation();
            double speedVoisin = voisinRef.get().getVitesse();
            double xVoisin = voisinRef.get().getX();
            double yVoisin = voisinRef.get().getY();
            double coeff = 10.0;
            double xProjected =
                xVoisin + speedVoisin * coeff * cos(directionVoisin);
            double yProjected =
                yVoisin - speedVoisin * coeff * sin(directionVoisin);
            sumX += xProjected;
            sumY += yProjected;
        }

        double avgX = sumX / voisins.size();
        double avgY = sumY / voisins.size();
        // trying to avoid the average position of the projected neighbors
        double deltaX = avgX - getX();
        double deltaY = avgY - getY();

        double targetDirection = +std::atan2(deltaY, deltaX);
        double diff_orientation = targetDirection - getOrientation();

        while (diff_orientation >= M_PI) {
            diff_orientation -= 2.0 * M_PI;
        }
        while (diff_orientation < -M_PI) {
            diff_orientation += 2.0 * M_PI;
        }

        setOrientation(getOrientation() + diff_orientation / 10);
    }
}

std::unique_ptr<Bestiole> Prevoyante::clone() const {
    return std::make_unique<Prevoyante>(*this);
}
