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
    config.addTypeCount("ComportementMultiple", 10);
    config.addTypeCount("Gregaire", 10);

    config.setTotalCount(20);

    config.setBirthRate(0.5);   // births per second in average
    config.setAvgLifeTime(20);  // average life time in seconds
    config.addOreilles(80, 1);
    config.addYeux(M_PI_4, 200, 1);
    config.addNageoires(1.5);
    config.addCarapace(1.5, 1.5);

    milieu.addPopulationConfig(config);
    milieu.initFromConfigs();
    aquarium.run();
    
    
    //config.setDeathRate(0);  // No decay rate
    //config.setLifeTimeStd(2.);
    //config.setCloningRate(0.5);  // clones per second in average
    

    
    //config.addCamouflage(1.5);

 

    return 0;
}
