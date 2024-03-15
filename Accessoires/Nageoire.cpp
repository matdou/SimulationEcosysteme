#include <stdlib.h>
#include <cmath>
#include <random>
#include "Nageoire.h"

const double Nageoire::MULT_MAX = 3;

Nageoire::Nageoire() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, MULT_MAX);
    Nageoire::mult = distribution(gen);
}

bool Nageoire::isNageoire() {
    return true;
}

bool Nageoire::isCarapace() {
    return false;
}

bool Nageoire::isCamouflage() {
    return false;
}

double Nageoire::getMultplicateur() {
    return mult;
}