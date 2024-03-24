#include "LifeCycleManager.h"

#include <algorithm>
#include <cstdlib>

#include "BestioleFactory.h"
#include "Milieu.h"

const int ESTIMATED_TIME = 60 * 2;  // 2 minutes
const int MAX_VECTOR_SIZE = 100000;
const int STORAGE_MARGIN = 2;  // 2 times the estimated memory size
const double MIN_TIME_BETWEEN_COLLISIONS = 0.5;  // 0.5 seconds

LifeCycleManager::LifeCycleManager(Milieu& milieu)
    : milieu(milieu), bestioles(milieu.getBestioles()) {}

void LifeCycleManager::handleBirths() {
    for (auto& config : milieu.getPopulationConfigs()) {
        double probability =
            calculateProbability(config.getBirthRate(), milieu.getDelay());
        if (static_cast<double>(rand()) / RAND_MAX < probability) {
            addBestioleFromConfig(config);
        }
    }
}

void LifeCycleManager::handleRandomDeaths() {
    for (auto& config : milieu.getPopulationConfigs()) {
        double probability =
            calculateProbability(config.getDeathRate(), milieu.getDelay()) *
            bestioles.size();
        if (!bestioles.empty() &&
            static_cast<double>(rand()) / RAND_MAX < probability) {
            int index = rand() % bestioles.size();
            bestioles.erase(bestioles.begin() + index);
        }
    }
}

void LifeCycleManager::handleCloning() {
    double probability;
    for (auto& config : milieu.getPopulationConfigs()) {
        probability =
            calculateProbability(config.getCloningRate(), milieu.getDelay()) *
            bestioles.size();
        if (!bestioles.empty() &&
            static_cast<double>(rand()) / RAND_MAX < probability) {
            int index = rand() % bestioles.size();
            std::unique_ptr<Bestiole> clone = bestioles[index]->clone();
            clone->setLastCollisionTime(milieu.getTimeSim());
            bestioles.push_back(std::move(clone));
        }
    }
}

void LifeCycleManager::updateLifeExpectancyAndRemoveExpired() {
    for (auto it = bestioles.begin(); it != bestioles.end();) {
        if ((*it)->getLifeExpectancy() == -1) {
            ++it;  // -1 denotes immortality
        } else if ((*it)->getLifeExpectancy() <= 0) {
            it = bestioles.erase(it);  // Remove expired bestiole
        } else {
            (*it)->setLifeExpectancy((*it)->getLifeExpectancy() -
                                     milieu.getDelay() / 1000.0);
            ++it;
        }
    }
}

void LifeCycleManager::addBestioleFromConfig(PopulationConfig& config) {
    std::unique_ptr<Bestiole> bestiole(
        BestioleFactory::createBestiole(config.getNextBirthType()));
    if (bestiole) {
        bestiole->setLifeExpectancyFromAvg(config.getAvgLifeTime(),
                                           config.getLifeTimeStd());
        for (const std::unique_ptr<Capteur>& capteur : config.getCapteurs()) {
            bestiole->addCapteur(capteur->clone());
        }

        setupBestioleFactors(*bestiole, config);
        bestioles.push_back(std::move(bestiole));
    }
}

void LifeCycleManager::setupBestioleFactors(Bestiole& bestiole,
                                            PopulationConfig& config) {
    bestiole.setMultiplicateurVitesse(config.getSpeedFactor(),
                                      config.getSlownessFactor());
    bestiole.setMultiplicateurProtection(config.getProtectionFactor());
    bestiole.setMultiplicateurDiscretion(config.getCamouflageFactor());
}

double LifeCycleManager::calculateProbability(double rate, int delay) const {
    return std::min((delay / 1000.0) * rate, 1.0);
}

void LifeCycleManager::handleCollisions() {
    for (auto& bestiole : bestioles) {
        // find all neighbors that collides with bestiole
        std::vector<std::reference_wrapper<Bestiole>> collidingNeighbors;
        for (auto& neighbor : bestioles) {
            if (bestiole->collidesWith(*neighbor)) {
                int timeSinceLastCollision =
                    std::min(milieu.getTimeSim() - neighbor->getLastCollisionTime(),
                             milieu.getTimeSim() - bestiole->getLastCollisionTime());
                if ( timeSinceLastCollision*milieu.getDelay()/1000 < MIN_TIME_BETWEEN_COLLISIONS) {
                    continue;
                }
                collidingNeighbors.push_back(std::ref(*neighbor));

            }
        }
        if (!collidingNeighbors.empty()) {
            collidingNeighbors.push_back(
                std::ref(*bestiole));  // add initial bestiole

            // Update all colliding neighbors to handle collision
            for (auto& collidingNeighbor : collidingNeighbors) {
                collidingNeighbor.get().updateCollision();
                collidingNeighbor.get().setLastCollisionTime(milieu.getTimeSim());
            }
        }
    }
}

void LifeCycleManager::updateBestiolesFromCapteurs() {
    for (auto& bestiole : bestioles) {
        bestiole->update(visibleNeighbors(bestiole));
    }
}

std::vector<std::reference_wrapper<Bestiole>>
LifeCycleManager::visibleNeighbors(std::unique_ptr<Bestiole>& b) {
    std::vector<std::reference_wrapper<Bestiole>> neighbors;
    for (auto& bestiole : bestioles) {
        if (*b == *bestiole) continue;  // Skip self
        if (b->jeTeVois(*bestiole)) {
            neighbors.push_back(
                std::ref(*bestiole));  // Utilise std::ref pour ajouter une
                                       // référence au vecteur
        }
    }
    // Retourne le vecteur de références
    return neighbors;
}

void LifeCycleManager::killMember(int identite) {
    bestioles.erase(
        std::remove_if(bestioles.begin(), bestioles.end(),
                       [identite](const std::unique_ptr<Bestiole>& b) {
                           return b->getIdentite() == identite;
                       }),
        bestioles.end());
}

int LifeCycleManager::calculateTotalPopulationSize() const {
    int totalPopulationSize = 0;
    for (const auto& config : milieu.getPopulationConfigs()) {
        totalPopulationSize += config.getTotalPopulationSize();
    }
    return totalPopulationSize;
}

// Estimate the memory size needed for the bestiole vector during simulation,
// based on rates
int LifeCycleManager::calculateMemorySize() const {
    double growingRate = 0.0;
    for (const auto& config : milieu.getPopulationConfigs()) {
        growingRate += config.getBirthRate();
        growingRate -= config.getDeathRate();
        growingRate += config.getCloningRate();
    }
    int estimatedMemorySize =
        calculateTotalPopulationSize() * ESTIMATED_TIME * growingRate;
    std::cout << "First estimated memory size: " << estimatedMemorySize
              << std::endl;
    estimatedMemorySize =
        STORAGE_MARGIN *
        std::max(estimatedMemorySize, calculateTotalPopulationSize());
    estimatedMemorySize = std::min(estimatedMemorySize, MAX_VECTOR_SIZE);
    std::cout << "Estimated memory size: " << estimatedMemorySize << std::endl;
    return estimatedMemorySize;
}

void LifeCycleManager::initFromConfigs() {
    int totalPopulationSize = calculateTotalPopulationSize();
    int reservedMemorySize = calculateMemorySize();
    bestioles.reserve(reservedMemorySize);
    std::cout << "Reserve " << reservedMemorySize << " bestioles" << std::endl;

    for (auto& config : milieu.getPopulationConfigs()) {
        int popSize = config.getTotalPopulationSize();
        std::cout << "Adding " << popSize << " bestioles of type "
                  << config.getCurrentTypeName() << std::endl;
        for (int i = 0; i < popSize; i++) {
            addBestioleFromConfig(config);
        }
    }

    for (auto& bestiole : bestioles) {
        int x = milieu.getWidth();
        int y = milieu.getHeight();
        bestiole->initCoords(x, y);
    }
}