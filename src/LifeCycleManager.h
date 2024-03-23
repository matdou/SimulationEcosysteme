#ifndef LIFECYCLEMANAGER_H
#define LIFECYCLEMANAGER_H

#include <vector>
#include <memory>
#include "Bestiole.h"
#include "PopulationConfig.h"

class Milieu;

class LifeCycleManager {
public:
    LifeCycleManager(Milieu& milieu);
    void handleBirths();
    void handleRandomDeaths();
    void handleCloning();
    void updateLifeExpectancyAndRemoveExpired();

private:
    Milieu& milieu; // Reference to the milieu to interact with the bestioles
    std::vector<std::unique_ptr<Bestiole>>& bestioles; // Direct access to the bestioles within the milieu

    void addBestioleFromConfig(PopulationConfig& config); // NOT CONST config because it shuffles through the bestioles
    double calculateProbability(double rate, int delay) const;
};

#endif // LIFECYCLEMANAGER_H
