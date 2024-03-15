#include <stdlib.h>
#include <cmath>
#include <random>
#include "Carapace.h"

const double Carapace::OMEGA_MAX = 3;
const double Carapace::MU_MAX = 3;

Carapace::Carapace() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution_omega(1, OMEGA_MAX);
    std::uniform_int_distribution<int> distribution_mu(1, MU_MAX);
    Carapace::omega = distribution_omega(gen);
    Carapace::mu = distribution_mu(gen);
}

bool Carapace::isNageoire() {
    return false;
}

bool Carapace::isCarapace() {
    return true;
}

bool Carapace::isCamouflage() {
    return false;
}

double Carapace::getOmega() {
    return omega;
}

double Carapace::getMu() {
    return mu;
}