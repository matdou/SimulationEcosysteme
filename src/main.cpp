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

 
    config.addTypeCount("Kamikaze", 100);
    // config.addTypeCount("Prevoyante", 2);
    config.setBirthRate(0.5);  // 1 births per second in average
    // config.setDeathRate(0);  // No decay rate
    config.setAvgLifeTime(10);
    // config.setLifeTimeStd(2.);
    config.setCloningRate(1);
    config.addOreilles(80, 1);

    // config.addCarapace(5, 5);
    std::cout << "Total population size: " << config.getTotalPopulationSize() << std::endl;
    milieu.addPopulationConfig(config);
   /*
    PopulationConfig config2;
 
    // config.addNageoires(3);
    config2.addTypeCount("Peureuse", 10);
    config2.addTypeCount("Gregaire", 10);
    config2.addOreilles(80, 1);
    milieu.addPopulationConfig(config2);
    */
    
    milieu.initFromConfigs();                      
    aquarium.run();

    return 0;
}
