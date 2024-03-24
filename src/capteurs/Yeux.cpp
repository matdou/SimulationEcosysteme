//  Yeux.cpp

#include "Yeux.h"

#include <iostream>

#include "Bestiole.h"
#include "Milieu.h"
const double Yeux::MIN_ANGLE = 0;
const double Yeux::MAX_ANGLE = 2 * M_PI;
const double Yeux::MIN_DISTANCE = 0;
const double Yeux::MAX_DISTANCE = 1000;
const double Yeux::MIN_DETECTION = 0.0;
const double Yeux::MAX_DETECTION = 1.0;

Yeux::Yeux() : Capteur() {
    champVision = M_PI_4;
    distanceVision = MAX_DISTANCE;
    capaciteDetection = MAX_DETECTION;
    std::cout << "Yeux created" << std::endl;
}

Yeux::Yeux(double champVision, double distanceVision, double capaciteDetection)
    : Capteur() {
    champVision = std::max(MIN_ANGLE, std::min(MAX_ANGLE, champVision));
    distanceVision = std::max(MIN_DISTANCE, std::min(MAX_DISTANCE, distanceVision));
    capaciteDetection = std::max(MIN_DETECTION, std::min(MAX_DETECTION, capaciteDetection));
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
