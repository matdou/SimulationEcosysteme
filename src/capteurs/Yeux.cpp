//  Yeux.cpp

#include "Yeux.h"
#include "Milieu.h"
#include "Bestiole.h"

#include <iostream>


Yeux::Yeux() : Capteur(), champVision(2), distanceVision(40), capaciteDetection(1) {}

void Capteur::percevoirEnvironnement(const Milieu& milieu, const Bestiole& bestiole) {
    // Nothing to do here
    return;
}

bool Yeux::jeTeVois(const Bestiole& bestiole, const Bestiole& moi) {
    double distance = sqrt(pow(bestiole.getX() - moi.getX(), 2) + pow(bestiole.getY() - moi.getY(), 2));
    if (distance > distanceVision) {
        return false;
    }
    //calculons l'angle entre l'orientation de moi et la direction de moi-bestiole
    double angle = atan2(bestiole.getY() - moi.getY(), bestiole.getX() - moi.getX());
    double angleDifference = abs(angle - moi.getOrientation());
    return angleDifference < champVision;
    
}
