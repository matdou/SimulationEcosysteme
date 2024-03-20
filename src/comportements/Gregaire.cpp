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
Gregaire::~Gregaire() {
    std::cout << "Destructor of Gregaire" << std::endl;
    // Cleanup resources specific to Gregaire if any
}



// Update the behavior of the Gregaire Bestiole
void Gregaire::update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    this->setCouleur(0, 255, 0); // Set the color to green
    if (!voisins.empty()) {
        this->setCouleur(0, 155, 0); // Set the color to dark green
        double moyenneX = 0.0;
        double moyenneY = 0.0;
        for (const auto& voisinRef : voisins) {
            Bestiole& voisin = voisinRef.get(); // Obtenez une référence à l'objet Bestiole
            moyenneX += voisin.getX();
            moyenneY += voisin.getY();
        }

        moyenneX /= voisins.size();
        moyenneY /= voisins.size();

        // Calcul de l'angle en fonction des moyennes des positions X et Y
        double angle = atan2(moyenneY - getY(), moyenneX - getX());
        setOrientation(angle);
    }
    else {
        // Si aucun voisin n'est trouvé, la bestiole se déplace aléatoirement
        std::cout << "No neighbors found" << std::endl;
    }
}


std::unique_ptr<Bestiole> Gregaire::clone() const {
    return std::make_unique<Gregaire>(*this);
}


