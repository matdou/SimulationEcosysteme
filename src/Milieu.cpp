#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "BestioleFactory.h"
#include "Capteur.h"
#include "LifeCycleManager.h"

const T Milieu::white[] = {(T)255, (T)255, (T)255};

Milieu::Milieu(int _width, int _height, int _delay)
    : UImg(_width, _height, 1, 3),
      width(_width),
      height(_height),
      lifeCycleManager(*this) {
    std::cout << "const Milieu" << std::endl;
    delay = _delay;
    std::srand(time(NULL));
}

Milieu::~Milieu(void) { std::cout << "dest Milieu" << std::endl; }

void Milieu::addMember(std::unique_ptr<Bestiole> b) {  // TODO MAKE CONST
    b->initCoords(width, height);
    listeBestioles.push_back(std::move(b));
}

void Milieu::clearEnvironment() {
    cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);
}

void Milieu::processBestiolesActionsAndDrawings() {
    for (auto& bestiole : listeBestioles) {
        bestiole->action(*this);
        bestiole->draw(*this);
    }
}

void Milieu::step() {
    clearEnvironment();
    processBestiolesActionsAndDrawings();
    lifeCycleManager.handleBirths();
    lifeCycleManager.handleRandomDeaths();
    lifeCycleManager.handleCloning();
    lifeCycleManager.updateLifeExpectancyAndRemoveExpired();
    lifeCycleManager.updateBestiolesFromCapteurs();
    lifeCycleManager.handleCollisions();
    lifeCycleManager.updateComportementMultiple();
    timeSim++;
}

void Milieu::addPopulationConfig(PopulationConfig& config) {
    populationConfigs.push_back(config);  // Copy the config // clone called
}

int Milieu::calculateTotalPopulationSize() const {
    int sum = 0;
    for (const auto& config : populationConfigs) {
        for (const auto& typeCount : config.getTypeCounts()) {
            sum += typeCount.second;
        }
    }
    return sum;
}

void Milieu::initFromConfigs() { lifeCycleManager.initFromConfigs(); }

void Milieu::killMember(int identite) { lifeCycleManager.killMember(identite); }
