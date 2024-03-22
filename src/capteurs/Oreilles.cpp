//  Yeux.cpp

#include "Oreilles.h"
#include "Milieu.h"
#include "Bestiole.h"

#include <iostream>


Oreilles::Oreilles() : Capteur() {

    distanceAudible = 80;
    capaciteDetection = 1;
    std::cout << "Oreilles created" << std::endl;

}

bool Oreilles::jeTeVois(const Bestiole& bestiole, const Bestiole& moi) {
    if (capaciteDetection < std::rand()/RAND_MAX) {
        return false;
    }
    double distance = sqrt(pow(bestiole.getX() - moi.getX(), 2) + pow(bestiole.getY() - moi.getY(), 2));
    return distance < distanceAudible;
}

