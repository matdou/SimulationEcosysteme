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
    config.addTypeCount("Peureuse", 1);
    config.addTypeCount("Gregaire", 1);
    config.addTypeCount("Kamikaze", 1);
    config.addTypeCount("Prevoyante", 3);
    config.setBirthRate(0);  // 1 births per second in average
    config.setDeathRate(0);  // No decay rate
    config.setAvgLifeTime(10);
    config.setLifeTimeStd(2.);
    
    milieu.addPopulationConfig(config);

    milieu.initFromConfigs();
    std::cout << "Total population size: " << config.getTotalPopulationSize() << std::endl;


    aquarium.run();

    return 0;
}
