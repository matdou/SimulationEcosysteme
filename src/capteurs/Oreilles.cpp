//  Yeux.cpp

#include "Oreilles.h"

#include <iostream>

#include "Bestiole.h"
#include "Milieu.h"

Oreilles::Oreilles() : Capteur() {
    distanceAudible = 80;
    capaciteDetection = 1;
    std::cout << "Oreilles created" << std::endl;
}

Oreilles::Oreilles(double distanceAudible, double capaciteDetection)
    : Capteur() {
    this->distanceAudible = distanceAudible;
    this->capaciteDetection = capaciteDetection;
    std::cout << "Oreilles created" << std::endl;
}

bool Oreilles::jeTeVois(const Bestiole& bestiole, const Bestiole& moi) {
    if (capaciteDetection < std::rand() / RAND_MAX) {
        return false;
    }

    double distance = sqrt(pow(bestiole.getX() - moi.getX(), 2) +
                           pow(bestiole.getY() - moi.getY(), 2));
    return distance < distanceAudible;
}

std::unique_ptr<Capteur> Oreilles::clone() const {
    return std::make_unique<Oreilles>(*this);
}