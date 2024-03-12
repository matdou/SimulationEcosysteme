#ifndef POPULATIONGENERATOR_H
#define POPULATIONGENERATOR_H

#include "BestioleFactory.h"
#include "PopulationConfig.h"
#include <vector>
#include <memory>

class PopulationGenerator {
public:
    static std::vector<std::unique_ptr<Bestiole>> generateInitialPopulation(const PopulationConfig& config);
};

#endif // POPULATIONGENERATOR_H
