#include "PopulationGenerator.h"

std::vector<std::unique_ptr<Bestiole>>
PopulationGenerator::generateInitialPopulation(const PopulationConfig& config) {
    std::vector<std::unique_ptr<Bestiole>> population;

    for (const auto& typeCount : config.typeCounts) {
        for (int i = 0; i < typeCount.second; ++i) {
            std::unique_ptr<Bestiole> bestiole(
                BestioleFactory::createBestiole(typeCount.first));
            if (bestiole) {
                population.push_back(std::move(bestiole));
            }
        }
    }

    return population;
}
