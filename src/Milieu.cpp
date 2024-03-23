#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "BestioleFactory.h"
#include "Capteur.h"

const T Milieu::white[] = {(T)255, (T)255, (T)255};

Milieu::Milieu(int _width, int _height, int _delay)
    : UImg(_width, _height, 1, 3), width(_width), height(_height) {
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

void Milieu::handleBirths() {
    for (auto& config : populationConfigs) {
        double probability =
            std::min((delay / 1000.0) * config.getBirthRate(), 1.0);
        if (std::rand() < probability * RAND_MAX) {
            addBestioleFromConfig(config);
        }
    }
}

void Milieu::handleRandomDeaths() {
    double probability;
    for (auto& config : populationConfigs) {
        probability = std::min(
            (delay / 1000.0) * config.getDeathRate() * listeBestioles.size(),
            1.0);
        if (!listeBestioles.empty() && std::rand() < probability * RAND_MAX) {
            int index = std::rand() % listeBestioles.size();
            listeBestioles.erase(listeBestioles.begin() + index);
        }
    }
}

void Milieu::updateLifeExpectancyAndRemoveExpired() {
    for (auto it = listeBestioles.begin(); it != listeBestioles.end();) {
        if ((*it)->getLifeExpectancy() ==
            -1) {  // Assuming -1 denotes immortality or unmanaged life
                   // expectancy
            ++it;
        } else if ((*it)->getLifeExpectancy() <= 0) {
            it = listeBestioles.erase(
                it);  // Bestiole's life expectancy expired; remove it
        } else {
            (*it)->setLifeExpectancy((*it)->getLifeExpectancy() -
                                     delay / 1000.0);
            ++it;
        }
    }
}

// Add ONE bestiole from a population config
void Milieu::addBestioleFromConfig(PopulationConfig& config) {
    std::unique_ptr<Bestiole> bestiole(
        BestioleFactory::createBestiole(config.getNextBirthType()));
    if (bestiole) {
        bestiole->setLifeExpectancyFromAvg(config.getAvgLifeTime(),
                                           config.getLifeTimeStd());
        for (std::unique_ptr<Capteur>& capteur : config.getCapteurs()) {
            bestiole->addCapteur(capteur->clone());
        }


        bestiole->setMultiplicateurVitesse(config.getSpeedFactor(), config.getSlownessFactor());
        bestiole->setMultiplicateurProtection(config.getProtectionFactor());
        bestiole->setMultiplicateurDiscretion(config.getCamouflageFactor());
        addMember(std::move(bestiole));
    }
}

void Milieu::handleCloning() {
    double probability;
    for (auto& config : populationConfigs) {
        probability = std::min(
            (delay / 1000.0) * config.getCloningRate() * listeBestioles.size(),
            1.0);
        if (!listeBestioles.empty() && std::rand() < probability * RAND_MAX) {
            int index = std::rand() % listeBestioles.size();
            std::unique_ptr<Bestiole> clone = listeBestioles[index]->clone();
            addMember(std::move(clone));
        }
    }
}

void Milieu::step() {
    clearEnvironment();
    processBestiolesActionsAndDrawings();
    handleBirths();
    handleRandomDeaths();
    handleCloning();
    updateLifeExpectancyAndRemoveExpired();
    updateBestiolesFromCapteurs();
    handleCollisions();
}

int Milieu::nbVoisins(const Bestiole& b) {
    int nb = 0;

    for (const auto& bestiolePtr : listeBestioles)
        if (!(b == *bestiolePtr) && b.jeTeVois(*bestiolePtr)) ++nb;

    return nb;
}

void Milieu::addPopulationConfig(PopulationConfig& config) {
    std::cout << "COPYING POPULATION CONFIG" << std::endl;
    populationConfigs.push_back(config); // Copy the config // clone called
}

// Method to calculate total population size
int Milieu::calculateTotalPopulationSize() const {
    int sum = 0;
    for (const auto& config : populationConfigs) {
        for (const auto& typeCount : config.getTypeCounts()) {
            sum += typeCount.second;
        }
    }
    return sum;
}

void Milieu::initFromConfigs() {
    int totalPopulationSize = calculateTotalPopulationSize();
    listeBestioles.reserve(totalPopulationSize +
                           1000);  // TODO Consider changing that
    std::cout << "Reserve " << totalPopulationSize << " bestioles" << std::endl;

    for (auto& config : populationConfigs) {
        int popSize = config.getTotalPopulationSize();
        std::cout << "Adding " << popSize << " bestioles of type "
                  << config.getCurrentTypeName() << std::endl;
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

std::vector<std::reference_wrapper<Bestiole>> Milieu::visibleNeighbors(
    std::unique_ptr<Bestiole>& b) {
    std::vector<std::reference_wrapper<Bestiole>> neighbors;
    for (auto& bestiole : listeBestioles) {
        if (b->jeTeVois(*bestiole)) {
            if (*b == *bestiole) continue;  // Skip self
            neighbors.push_back(
                std::ref(*bestiole));  // Utilise std::ref pour ajouter une
                                       // référence au vecteur
        }
    }
    // Retourne le vecteur par valeur (RVO s'appliquera généralement ici,
    // évitant la copie inutile)
    return neighbors;
}

void Milieu::updateBestiolesFromCapteurs() {
    for (auto& bestiole : listeBestioles) {
        bestiole->update(visibleNeighbors(bestiole));
    }
}


void Milieu::handleCollisions() {
    for (auto& bestiole : listeBestioles) {
        //find all neighbors that collides with bestiole
        std::vector<std::reference_wrapper<Bestiole>> collidingNeighbors;
        for (auto& neighbor : listeBestioles) {
            if (bestiole->collidesWith(*neighbor)) {
                collidingNeighbors.push_back(std::ref(*neighbor));
            }
        }
        if (!collidingNeighbors.empty()) {
            collidingNeighbors.push_back(std::ref(*bestiole)); // add initial bestiole

            // Update all colliding neighbors to handle collision
            for (auto& collidingNeighbor : collidingNeighbors) {
                collidingNeighbor.get().updateCollision();
            }
        }

    }
}
