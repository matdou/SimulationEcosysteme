#include <iostream>
#include <random>
#include "Yeux.h"


const double Yeux::ALPHA_YE_MIN = 0;//0;
const double Yeux::ALPHA_YE_MAX = M_PI/2;
const double Yeux::GAMMA_YE_MAX = 1.;
const double Yeux::GAMMA_YE_MIN = 0;//0.5;
const double Yeux::DELTA_YE_MAX = 50;
const double Yeux::DELTA_YE_MIN = 0;//50.;


Yeux::Yeux() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist_alpha(ALPHA_YE_MIN, ALPHA_YE_MAX);
    std::uniform_real_distribution<double> dist_gamma(GAMMA_YE_MIN, GAMMA_YE_MAX);
    std::uniform_real_distribution<double> dist_delta(DELTA_YE_MIN, DELTA_YE_MAX);
    alpha = dist_alpha(gen);
    gamma = dist_gamma(gen);
    delta = dist_delta(gen);
}

Yeux::Yeux(const Yeux & y) {
    alpha = y.getAlpha();
    gamma = y.getGamma();
    delta = y.getDelta();
}

bool Yeux::isYeux() {
    return true;
}

bool Yeux::isOreilles() {
    return false;
}

double Yeux::getAlpha() {
    return alpha;
}

double Yeux::getDelta() {
    return delta;
}

double Yeux::getGamma() {
    return gamma;
}