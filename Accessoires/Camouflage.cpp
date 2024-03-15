#include <stdlib.h>
#include <cmath>
#include <random>
#include "Camouflage.h"

const double Camouflage::PSI_MAX = .9;
const double Camouflage::PSI_MIN = .1;

Camouflage::Camouflage() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(PSI_MIN, PSI_MAX);
    Camouflage::psi = distribution(gen);
}

bool Camouflage::isNageoire() {
    return false;
}

bool Camouflage::isCarapace() {
    return false;
}

bool Camouflage::isCamouflage() {
    return true;
}

double Camouflage::getPsi() {
    return psi;
}