#include "LifeCycleManager.h"
#include "Milieu.h"
#include "BestioleFactory.h"
#include <algorithm>
#include <cstdlib>

LifeCycleManager::LifeCycleManager(Milieu& milieu)
    : milieu(milieu), bestioles(milieu.getBestioles()) {}

void LifeCycleManager::handleBirths() {
    for (auto& config : milieu.getPopulationConfigs()) {
        double probability = calculateProbability(config.getBirthRate(), milieu.getDelay());
        if (static_cast<double>(rand()) / RAND_MAX < probability) {
            addBestioleFromConfig(config);
        }
    }
}

void LifeCycleManager::handleRandomDeaths() {
    for (auto& config : milieu.getPopulationConfigs()) {
        double probability = calculateProbability(config.getDeathRate(), milieu.getDelay()) * bestioles.size();
        if (!bestioles.empty() && static_cast<double>(rand()) / RAND_MAX < probability) {
            int index = rand() % bestioles.size();
            bestioles.erase(bestioles.begin() + index);
        }
    }
}

void LifeCycleManager::handleCloning() {
    double probability;
    for (auto& config : milieu.getPopulationConfigs()) {
        probability = calculateProbability(config.getCloningRate(), milieu.getDelay()) * bestioles.size();
        if (!bestioles.empty() && static_cast<double>(rand()) / RAND_MAX < probability) {
            int index = rand() % bestioles.size();
            std::unique_ptr<Bestiole> clone = bestioles[index]->clone();
            bestioles.push_back(std::move(clone));
        }
    }
}

void LifeCycleManager::updateLifeExpectancyAndRemoveExpired() {
    for (auto it = bestioles.begin(); it != bestioles.end();) {
        if ((*it)->getLifeExpectancy() == -1) {
            ++it; // -1 denotes immortality
        } else if ((*it)->getLifeExpectancy() <= 0) {
            it = bestioles.erase(it); // Remove expired bestiole
        } else {
            (*it)->setLifeExpectancy((*it)->getLifeExpectancy() - milieu.getDelay() / 1000.0);
            ++it;
        }
    }
}

void LifeCycleManager::addBestioleFromConfig(PopulationConfig& config) {
    std::unique_ptr<Bestiole> bestiole(BestioleFactory::createBestiole(config.getNextBirthType()));
    if (bestiole) {
        bestiole->setLifeExpectancyFromAvg(config.getAvgLifeTime(), config.getLifeTimeStd());
        for (const std::unique_ptr<Capteur>& capteur : config.getCapteurs()) {
            bestiole->addCapteur(capteur->clone());
        }

        bestiole->setMultiplicateurVitesse(config.getSpeedFactor(), config.getSlownessFactor());
        bestiole->setMultiplicateurProtection(config.getProtectionFactor());
        bestiole->setMultiplicateurDiscretion(config.getCamouflageFactor());
        bestioles.push_back(std::move(bestiole));
    }
}


double LifeCycleManager::calculateProbability(double rate, int delay) const {
    return std::min((delay / 1000.0) * rate, 1.0);
}
