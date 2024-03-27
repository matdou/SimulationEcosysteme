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

    config.addTypeCount("Kamikaze", 40);
    config.addTypeCount("Prevoyante", 20);
    config.addTypeCount("Peureuse", 20);
    config.addTypeCount("Gregaire", 20);


    config.setTotalCount(100);
    config.setBirthRate(0.5);   // births per second in average
    config.setAvgLifeTime(20);  // average life time in seconds
    // config.setDeathRate(0);  // No decay rate
    // config.setLifeTimeStd(2.);
    //config.setCloningRate(0.5);  // clones per second in average
    config.addOreilles(80, 1);
    config.addYeux(M_PI_4, 200, 1);

    config.addNageoires(1.5);
    config.addCarapace(1.5, 1.5);
    //config.addCamouflage(1.5);


    std::cout << "Total population size: " << config.getTotalPopulationSize()
              << std::endl;

    milieu.addPopulationConfig(config);

    milieu.initFromConfigs();
    aquarium.run();

    return 0;
}
