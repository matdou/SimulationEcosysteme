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

using namespace std;

int main() {
    Aquarium aquarium(640, 480, 30);
    Milieu& milieu = aquarium.getMilieu();

    PopulationConfig config;

    //config.addTypeCount("Peureuse", 1);
    config.addTypeCount("Gregaire", 100);
    config.addTypeCount("Kamikaze", 10);
    //config.addTypeCount("Prevoyante", 1);
    config.setBirthRate(0);  // 1 births per second in average
    config.setDeathRate(0);  // No decay rate
    config.setAvgLifeTime(30);
    config.setLifeTimeStd(2.);
    config.setCloningRate(0);

    //config.addGlobalCapteur("Yeux");
    config.addGlobalCapteur("Oreilles");


    
    milieu.addPopulationConfig(config);

    milieu.initFromConfigs();
    std::cout << "Total population size: " << config.getTotalPopulationSize() << std::endl;

                                    
    aquarium.run();

    return 0;
}
