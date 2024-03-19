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
    config.addTypeCount("Peureuse", 10);
    config.addTypeCount("Gregaire", 10);
    config.addTypeCount("Kamikaze", 20);
    config.addTypeCount("Prevoyante", 20);
    config.setBirthRate(1);  // 1 births per second in average
    config.setDeathRate(0);  // No decay rate
    config.setAvgLifeTime(10);
    config.setLifeTimeStd(2.);
    
    milieu.addPopulationConfig(config);

    milieu.initFromConfigs();

    for (int i = 0; i < 10; i++) {
        milieu.killMember(i);
    }

    aquarium.run();

    return 0;
}
