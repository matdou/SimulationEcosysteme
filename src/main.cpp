#include <iostream>

#include "Aquarium.h"
#include "Bestiole.h"
#include "BestioleFactory.h"
#include "Milieu.h"
#include "Peureuse.h"
#include "Gregaire.h"
#include "Kamikaze.h"
#include "Prevoyante.h"
#include "PopulationConfig.h"
#include "PopulationGenerator.h"


using namespace std;

int main() {
    // BestioleFactory::registerType("Peureux", []() -> Bestiole* { return new
    // Peureux(); });

    Aquarium aquarium(640, 480, 30);
    Milieu& milieu = aquarium.getMilieu();

    PopulationConfig config;
    config.addTypeCount("Peureuse", 100);
    config.addTypeCount("Gregaire", 10);
    config.addTypeCount("Kamikaze", 20);
    config.addTypeCount("Prevoyante", 200);
    config.setBirthRate(1); // 1 births per second in average
    config.setDeathRate(0); // No decay rate
    config.setAvgLifeTime(10);

    milieu.addPopulationConfig(config);

    milieu.initFromConfigs();
    

   
    for (int i = 0; i < 0; i++) {
        milieu.artificialBirth(config);
    }

    aquarium.run();

    return 0;
}
