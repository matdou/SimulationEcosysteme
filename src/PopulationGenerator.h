#ifndef POPULATIONGENERATOR_H
#define POPULATIONGENERATOR_H

#include <memory>
#include <vector>

#include "BestioleFactory.h"
#include "PopulationConfig.h"

class PopulationGenerator {
   public:
    static std::vector<std::unique_ptr<Bestiole>> generateInitialPopulation(
        const PopulationConfig& config);
    static void generateNewBestioles(double rate,
                                     const PopulationConfig& config);
};

#endif  // POPULATIONGENERATOR_H
