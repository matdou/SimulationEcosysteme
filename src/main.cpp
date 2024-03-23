#include <iostream>

#include "Aquarium.h"
#include "Bestiole.h"
#include "BestioleFactory.h"
#include "Gregaire.h"
#include "Kamikaze.h"
#include "Milieu.h"
#include "Peureuse.h"
#include "PopulationConfig.h"
#include "PopulationGenerator.h"
#include "Prevoyante.h"

int main() {
    Aquarium aquarium(640, 480, 30);
    Milieu& milieu = aquarium.getMilieu();

    PopulationConfig config;

    config.addTypeCount("Kamikaze", 70);
    config.addTypeCount("Prevoyante", 10);
    config.addTypeCount("Peureuse", 10);
    config.addTypeCount("Gregaire", 10);
    config.setTotalCount(10);
    config.setBirthRate(0.0);   // births per second in average
    config.setAvgLifeTime(20);  // average life time in seconds
    // config.setDeathRate(0);  // No decay rate
    // config.setLifeTimeStd(2.);
    config.setCloningRate(0.0);  // clones per second in average
    config.addOreilles(80, 1);

    std::cout << "Total population size: " << config.getTotalPopulationSize()
              << std::endl;

    milieu.addPopulationConfig(config);

    milieu.initFromConfigs();
    aquarium.run();

    return 0;
}
