//  Yeux.cpp

#include "Yeux.h"

#include <iostream>

#include "Bestiole.h"
#include "Milieu.h"

Yeux::Yeux() : Capteur() {
    champVision = 6;
    distanceVision = 800;
    capaciteDetection = 1;
    std::cout << "Yeux created" << std::endl;
}

Yeux::Yeux(double champVision, double distanceVision, double capaciteDetection)
    : Capteur() {
    this->champVision = champVision;
    this->distanceVision = distanceVision;
    this->capaciteDetection = capaciteDetection;
    std::cout << "Yeux created" << std::endl;
}

bool Yeux::jeTeVois(const Bestiole& bestiole, const Bestiole& moi) {
    if (capaciteDetection < std::rand() / RAND_MAX) {
        return false;
    }
    double distance = sqrt(pow(bestiole.getX() - moi.getX(), 2) +
                           pow(bestiole.getY() - moi.getY(), 2));
    if (distance > distanceVision) {
        return false;
    }
    // calculons l'angle entre l'orientation de moi et la direction de
    // moi-bestiole
    double angle =
        atan2(bestiole.getY() - moi.getY(), bestiole.getX() - moi.getX());
    double angleDifference = abs(angle - moi.getOrientation());

    return angleDifference < champVision;
}

std::unique_ptr<Capteur> Yeux::clone() const {
    return std::make_unique<Yeux>(*this);
}
