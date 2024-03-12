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

    for (int i = 1; i <= 20; ++i) {
        /*
        Bestiole* peureux = BestioleFactory::createBestiole("Gregaire");
        Bestiole* kamikaze = BestioleFactory::createBestiole("Kamikaze");
        Bestiole* gregaire = BestioleFactory::createBestiole("Peureuse");
        Bestiole* prevoyante = BestioleFactory::createBestiole("Prevoyante");

        aquarium.getMilieu().addMember(*peureux);
        aquarium.getMilieu().addMember(*kamikaze);
        aquarium.getMilieu().addMember(*gregaire);
        aquarium.getMilieu().addMember(*prevoyante);

        */
        

        
        // aquarium.getMilieu().addMember(*peureux);

        // TODO : Milieu is storing a copy of the Bestiole, WARNING
    }


    PopulationConfig config;
    config.addTypeCount("Peureuse", 80);
    config.addTypeCount("Gregaire", 20);
    config.addTypeCount("Kamikaze", 20);
    config.addTypeCount("Prevoyante", 200);

    auto population = PopulationGenerator::generateInitialPopulation(config);

    for (auto& bestiole : population) {
        aquarium.getMilieu().addMember(*bestiole);
    }



    aquarium.run();

    return 0;
}
