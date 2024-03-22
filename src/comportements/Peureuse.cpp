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
    setVitesse(1);
}

Peureuse::~Peureuse() {
    // Destructor
}

void Peureuse::update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    this->setCouleur(0, 0, 255);
    if (voisins.size() >= 3){
        setCouleur(0, 0, 120);
        double new_speed = getVitesse()*2;
        double new_orientation;
        if(getOrientation()>0){
            new_orientation = getOrientation()-M_PI/10; #TODO
        }
        else {
            new_orientation = getOrientation()+M_PI/10; #TODO
        }
        setVitesse(new_speed);
        setOrientation(new_orientation);
    }
    else{
        setVitesse(getVitesseInitiale());
    }
    
}

std::unique_ptr<Bestiole> Peureuse::clone() const {
    return std::make_unique<Peureuse>(*this);
}

