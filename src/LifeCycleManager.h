#ifndef LIFECYCLEMANAGER_H
#define LIFECYCLEMANAGER_H

#include <vector>
#include <memory>
#include "Bestiole.h"
#include "PopulationConfig.h"

class Milieu;

class LifeCycleManager {
public:
    static const int ESTIMATION_TIME;
    static const int MAX_POPULATION_SIZE;
    static const int MEMORY_MARGIN;

    LifeCycleManager(Milieu& milieu);
    void handleBirths();
    void handleRandomDeaths();
    void handleCloning();
    void updateLifeExpectancyAndRemoveExpired();
    void handleCollisions();
    void updateBestiolesFromCapteurs();
    void addBestioleFromConfig(PopulationConfig& config);
    void setupBestioleFactors(Bestiole& bestiole, PopulationConfig& config);
    void initFromConfigs();

    void killMember(int identite);

    int calculateTotalPopulationSize() const;
    int calculateMemorySize() const;
    std::vector<std::reference_wrapper<Bestiole>> visibleNeighbors(std::unique_ptr<Bestiole>& b);

private:
    Milieu& milieu; // Reference to the milieu to interact with the bestioles
    std::vector<std::unique_ptr<Bestiole>>& bestioles; // Direct access to the bestioles within the milieu
    double calculateProbability(double rate, int delay) const;
};

#endif // LIFECYCLEMANAGER_H
