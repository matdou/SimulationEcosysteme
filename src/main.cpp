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
    config.addTypeCount("Peureuse", 10);
    config.addTypeCount("ComportementMultiple", 20);
    config.addTypeCount("Gregaire", 10);

    config.setTotalCount(20);

    config.setBirthRate(0.5);   // births per second in average
     //config.setDeathRate(0);  // No decay rate
    config.setAvgLifeTime(20);  // average life time in seconds
    //config.setLifeTimeStd(2.);
    //config.setCloningRate(0.5);  // clones per second in average
    config.addOreilles(80, 1);
    config.addYeux(M_PI_4, 200, 1);
    config.addNageoires(1.5);
    config.addCarapace(1.5, 1.5);
    //config.addCamouflage(1.5);

    milieu.addPopulationConfig(config); // Multiple population configs can be added
    milieu.initFromConfigs();
    aquarium.run();

    return 0;
}
