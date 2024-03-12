
#ifndef POPULATIONGENERATOR_H
#define POPULATIONGENERATOR_H

#include "BestioleFactory.h"
#include "PopulationConfig.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<Bestiole>> generatePopulation(const PopulationConfig& config) {
    std::vector<std::unique_ptr<Bestiole>> population;

    for (const auto& typeCount : config.typeCounts) {
        for (int i = 0; i < typeCount.second; ++i) {
            std::unique_ptr<Bestiole> bestiole(BestioleFactory::createBestiole(typeCount.first));
            if (bestiole) {
                population.push_back(std::move(bestiole));
            }
        }
    }

    return population;
}

#endif // POPULATIONGENERATOR_H
