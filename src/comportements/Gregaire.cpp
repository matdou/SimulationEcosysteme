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
        double moyenneX = 0.0;
        double moyenneY = 0.0;
        for (const auto& voisinRef : voisins) {
            Bestiole& voisin = voisinRef.get();
            moyenneX += voisin.getX();
            moyenneY += voisin.getY();
        }

        moyenneX /= voisins.size();
        moyenneY /= voisins.size();

        // Calcul de l'angle en fonction des moyennes des positions X et Y"
        double angle_pos = atan2(moyenneY - getY(), moyenneX - getX());
        double currentAngle_pos = getOrientation();

        double angle_diff = angle_pos - currentAngle_pos;

        if (angle_diff > M_PI) {
            angle_diff -= 2 * M_PI;
        } else if (angle_diff < -M_PI) {
            angle_diff += 2 * M_PI;
        }

        if (angle_diff > 0) {
            setCouleur(255,0,0);
        } else {
            setCouleur(0,0,255);
        }

        double newOrientation = getOrientation() + angle_diff/10;
        setOrientation(newOrientation);

    }
}


std::unique_ptr<Bestiole> Gregaire::clone() const {
    return std::make_unique<Gregaire>(*this);
}


