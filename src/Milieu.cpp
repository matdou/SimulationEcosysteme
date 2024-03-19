#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "BestioleFactory.h"

const T Milieu::white[] = {(T)255, (T)255, (T)255};

Milieu::Milieu(int _width, int _height, int _delay)
    : UImg(_width, _height, 1, 3), width(_width), height(_height) {
    cout << "const Milieu" << endl;
    delay = _delay;
    std::srand(time(NULL));
}

Milieu::~Milieu(void) { cout << "dest Milieu" << endl; }

void Milieu::addMember(std::unique_ptr<Bestiole> b) { // TODO MAKE CONST
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

void Milieu::handleBirths() {
    for (auto& config : populationConfigs) {
        double probability = std::min((delay / 1000.0) * config.birthRate, 1.0);
        if (std::rand() < probability * RAND_MAX) {
            addBestioleFromConfig(config);
        }
    }
}

void Milieu::handleRandomDeaths() {
    double probability;
    for (auto& config : populationConfigs) {
        probability = std::min((delay / 1000.0) * config.deathRate * listeBestioles.size(), 1.0);
        if (!listeBestioles.empty() && std::rand() < probability * RAND_MAX) {
            int index = std::rand() % listeBestioles.size();
            listeBestioles.erase(listeBestioles.begin() + index);
        }
    }
}

void Milieu::updateLifeExpectancyAndRemoveExpired() {
    for (auto it = listeBestioles.begin(); it != listeBestioles.end();) {
        if ((*it)->getLifeExpectancy() == -1) {  // Assuming -1 denotes immortality or unmanaged life expectancy
            ++it;
        } else if ((*it)->getLifeExpectancy() <= 0) {
            it = listeBestioles.erase(it);  // Bestiole's life expectancy expired; remove it
        } else {
            (*it)->setLifeExpectancy((*it)->getLifeExpectancy() - delay / 1000.0);
            ++it;
        }
    }
}

// Add ONE bestiole from a population config
void Milieu::addBestioleFromConfig(PopulationConfig& config) {
    std::unique_ptr<Bestiole> bestiole(BestioleFactory::createBestiole(config.getNextBirthType()));
    if (bestiole) {
        bestiole.get()->setLifeExpectancyFromAvg(config.avgLifeTime, config.lifeTimeStd);
        addMember(std::move(bestiole));
    }
}


void Milieu::step() {
    clearEnvironment();
    processBestiolesActionsAndDrawings();
    handleBirths();
    handleRandomDeaths();
    updateLifeExpectancyAndRemoveExpired();
}


int Milieu::nbVoisins(const Bestiole& b) {
    int nb = 0;

    for (const auto& bestiolePtr : listeBestioles)
        if (!(b == *bestiolePtr) && b.jeTeVois(*bestiolePtr)) ++nb;

    return nb;
}


void Milieu::addPopulationConfig(const PopulationConfig& config) {
    populationConfigs.push_back(config);
}

// Method to calculate total population size
int Milieu::calculateTotalPopulationSize() const {
    int sum = 0;
    for (const auto& config : populationConfigs) {
        for (const auto& typeCount : config.typeCounts) {
            sum += typeCount.second;
        }
    }
        return sum;
}
/*
// Add bestioles from a population type and count
void Milieu::createAndAddBestiole(const PopulationConfig& config, const std::pair<const std::string, int>& typeCount) {
    for (int i = 0; i < typeCount.second; ++i) {
        std::unique_ptr<Bestiole> bestiole(BestioleFactory::createBestiole(typeCount.first));
        bestiole.get()->setLifeExpectancyFromAvg(config.avgLifeTime, config.lifeTimeStd);
        if (bestiole) {
            addMember(std::move(bestiole));
        }
    }
}
*/

void Milieu::initFromConfigs() {
    int totalPopulationSize = calculateTotalPopulationSize();
    listeBestioles.reserve(totalPopulationSize + 1000); // Consider changing that
    std::cout << "Reserve " << totalPopulationSize << " bestioles" << std::endl;

    for (auto& config : populationConfigs) {
        int popSize = config.getTotalPopulationSize();
        std::cout << "Adding " << popSize << " bestioles of type " << config.currentTypeName << std::endl;
        for (int i = 0; i < popSize; i++) {
            addBestioleFromConfig(config);
        }   
    }
}


void Milieu::killMember(int identite) {
    for (auto it = listeBestioles.begin(); it != listeBestioles.end(); ++it) {
        if ((*it)->getIdentite() == identite) {
            listeBestioles.erase(it);
            return;
        }
    }
}