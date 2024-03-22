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

        // Calcul de l'angle en fonction des moyennes des positions X et Y
        double angle = atan2(moyenneY - getY(), moyenneX - getX());
        double currentAngle = getOrientation();

        double angleDifference = angle - currentAngle;
        if (angleDifference > M_PI) {
            angleDifference -= 2 * M_PI;
        } else if (angleDifference < -M_PI) {
            angleDifference += 2 * M_PI;
        }

        setOrientation(currentAngle + angleDifference / 10.0); 
    }
}


std::unique_ptr<Bestiole> Gregaire::clone() const {
    return std::make_unique<Gregaire>(*this);
}


