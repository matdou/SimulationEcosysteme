#ifndef LIFECYCLEMANAGER_H
#define LIFECYCLEMANAGER_H

#include <memory>
#include <vector>

#include "Bestiole.h"
#include "PopulationConfig.h"

class Milieu;

class LifeCycleManager {
public:
    static const int ESTIMATION_TIME; // Time estimation for memory allocation
    static const int MAX_POPULATION_SIZE; // Maximum population size
    static const int MEMORY_MARGIN; // Memory margin for vector allocation
    static const double MIN_COLLISION_TIME; // Minimum time between collisions
    static const double COMPORTMENT_CHANGE_RATE; // Rate of changing ComportementMultiple
    
    /**
     * Constructs a LifeCycleManager associated with a specific milieu.
     * @param milieu Reference to the milieu that this manager will manipulate.
     */
    LifeCycleManager(Milieu& milieu);

    ~LifeCycleManager() = default;

    /**
     * Handles the creation of new bestioles based on the birth rates specified in the population configs.
     */
    void handleBirths();

    /**
     * Randomly removes bestioles from the population based on death rates.
     */
    void handleRandomDeaths();

    /**
     * Handles the cloning of existing bestioles based on cloning rates.
     */
    void handleCloning();

    /**
     * Updates the life expectancy of all bestioles in the milieu and removes those whose life expectancy has expired.
     */
    void updateLifeExpectancyAndRemoveExpired();

    /**
     * Checks for collisions between bestioles and handles them accordingly.
     */
    void handleCollisions();

    /**
     * Updates the state of bestioles based on the inputs from their sensors/capteurs.
     */
    void updateBestiolesFromCapteurs();

    /**
     * Adds a new bestiole to the population based on a given configuration.
     * @param config The population configuration from which to create the bestiole.
     */
    void addBestioleFromConfig(PopulationConfig& config);

    /**
     * Initializes the population of bestioles based on initial configurations.
     */
    void initFromConfigs();

    /**
     * Removes a bestiole from the population by its identity.
     * @param identite The unique identifier of the bestiole to remove.
     */
    void killMember(int identite);

    /**
     * Calculates the total size of the population across all types.
     * @return The total population size.
     */
    int calculateTotalPopulationSize() const;

    /**
     * Estimates the required memory size for the bestiole vector, adjusting for growth rates.
     * @return The estimated memory size needed.
     */
    int calculateMemorySize() const;

    /**
     * Finds all neighbors visible to a given bestiole.
     * @param b The bestiole whose neighbors to find.
     * @return A vector of reference wrappers to the visible neighbors.
     */
    std::vector<std::reference_wrapper<Bestiole>> visibleNeighbors(std::unique_ptr<Bestiole>& b);

    /**
     * Updates the behaviour of ComportementMultiple bestioles from one base Comportement to another.
     */
    void updateComportementMultiple();

private:
    Milieu& milieu; // Reference to the milieu to interact with the bestioles
    std::vector<std::unique_ptr<Bestiole>>& bestioles; // Direct access to the bestioles within the milieu

    /**
     * Calculates the probability of an event occurring within a given time frame.
     * @param rate The rate of the event (per second).
     * @param delay The time frame in milliseconds.
     * @return The probability of the event occurring within the given delay.
     */
    double calculateProbability(double rate, int delay) const;

    /**
     * Configures a bestiole's factors based on the specified population config.
     * @param bestiole The bestiole to configure.
     * @param config The population configuration providing the factors.
     */
    void setupBestioleFactors(Bestiole& bestiole, PopulationConfig& config);
};

#endif // LIFECYCLEMANAGER_H
