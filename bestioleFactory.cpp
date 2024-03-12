#include "bestioleFactory.h"
#include "Comportement.h"

BestioleFactory* BestioleFactory::instance = nullptr;

BestioleFactory* BestioleFactory::getInstance() {
    if (instance == nullptr) {
        instance = new BestioleFactory();
    }
    return instance;
}

Bestiole* BestioleFactory::createBestiole(const std::string& type) {
    Bestiole* bestiole = new Bestiole();
    if (type == "Peureux") {
        bestiole->setComportement(new ComportementPeureux());
    } else if (type == "Kamikaze") {
        bestiole->setComportement(new ComportementKamikaze());
    } else if (type == "Gregaire") {
        bestiole->setComportement(new ComportementGregaire());
    }
    bestiole->appliquerComportement();
    return bestiole; // if type is not recognized, return a default Bestiole
}
