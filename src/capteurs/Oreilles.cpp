//  Yeux.cpp

#include "Oreilles.h"

#include <iostream>

#include "Bestiole.h"
#include "Milieu.h"

const double Oreilles::MIN_DISTANCE = 0;
const double Oreilles::MAX_DISTANCE = 1000;
const double Oreilles::MIN_DETECTION = 0.0;
const double Oreilles::MAX_DETECTION = 1.0;

Oreilles::Oreilles() : Capteur() {
    distanceAudible = MAX_DISTANCE;
    capaciteDetection = MAX_DETECTION;
    std::cout << "Oreilles created" << std::endl;
}

Oreilles::Oreilles(double distanceAudible, double capaciteDetection)
    : Capteur() {
    distanceAudible = std::max(MIN_DISTANCE, std::min(MAX_DISTANCE, distanceAudible));
    capaciteDetection = std::max(MIN_DETECTION, std::min(MAX_DETECTION, capaciteDetection));
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