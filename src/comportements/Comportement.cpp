#include "Comportement.h"

void Comportement::gregaireUpdate(const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
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

void Comportement::kamikazeUpdate(const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
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
void Comportement::peureuseUpdate(const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    this->setCouleur(0, 0, 255);  // blue when

    if (voisins.size() >= 3) {
        setCouleur(150, 0, 150);  // purple when there are 3 or more neighbors

        if (turnCooldown == 0) {
            setVitesse(Bestiole::MAX_VITESSE);
            setOrientation(getOrientation() + M_PI);
            turnCooldown = TURN_COOLDOWN;
        }
    }

    if (turnCooldown > 0) {
        turnCooldown--;
        setCouleur(0, 0, 150);  // dark blue when the cooldown is active
    } else {
        setVitesse(getInitialMultipliedVitesse());  // reset the speed
    }
}

void Comportement::prevoyanteUpdate(
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