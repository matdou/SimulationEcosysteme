#include <iostream>
#include <random>
#include "Oreilles.h"


const double Oreilles::GAMMA_OR_MAX = 1.0;
const double Oreilles::GAMMA_OR_MIN = 1.0; //0.5;
const double Oreilles::DELTA_OR_MAX = 30.0;
const double Oreilles::DELTA_OR_MIN = 0.0; //10.;

Oreilles::Oreilles() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist_gamma(GAMMA_OREILLES_MIN, GAMMA_OREILLES_MAX);
    std::uniform_real_distribution<double> dist_delta(DELTA_OREILLES_MIN, DELTA_OREILLES_MAX);
    gamma = dist_gamma(gen);
    delta = dist_delta(gen);
}

Oreilles::Oreilles(const Oreilles & o) {
    gamma = o.getGamma();
    delta = o.getDelta();
}

bool Oreilles::isYeux() {
    return false;
}

bool Oreilles::isOreilles() {
    return true;
}

double Oreilles::getGamma() {
    return gamma;
}

double Oreilles::getDelta() {
    return delta;
}

bool Oreilles::isCapting(Bestiole& b, int x, int y, double orientation) override {
    
}