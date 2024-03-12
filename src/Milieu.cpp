#include "Milieu.h"
#include "BestioleFactory.h"

#include <cstdlib>
#include <ctime>


const T Milieu::white[] = {(T)255, (T)255, (T)255};

Milieu::Milieu(int _width, int _height)
    : UImg(_width, _height, 1, 3), width(_width), height(_height) {
    cout << "const Milieu" << endl;

    std::srand(time(NULL));
}

Milieu::~Milieu(void) { cout << "dest Milieu" << endl; }

void Milieu::step(void) {
    cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);
    for (std::vector<Bestiole>::iterator it = listeBestioles.begin();
         it != listeBestioles.end(); ++it) {
        it->action(*this);
        it->draw(*this);
    } 

    // Ajouter les Bestioles qui naissent proportionellement à leur nombre
    // A chaque step on a aleatoirement (si random<birthRate) une naissance
    // a chaque naissance, on increment le compteur, et on ajoute une bestiole
    // correspondant a la config en position du compteur modulo la taille de la
    // config, en d'aitre terme, a chaque fois que une bestiole doit apparaitre, on
    // itere sur la config, et on ajoute une bestiole de chaque type


    for (auto& configPair : populationConfigs) {

    if (std::rand() < configPair.second.birthRate * RAND_MAX) {
        // Calculate the total number of types in the configuration
        int totalTypes = 0;
        for (const auto& typeCount : configPair.second.typeCounts) {
            totalTypes += typeCount.second;
        }

        // Get the index of the next type to create
        int currentIndex = configPair.first % totalTypes;

        // Find the corresponding type in the configuration
        int accumulatedCount = 0;
        std::string selectedType;
        for (const auto& typeCount : configPair.second.typeCounts) {
            accumulatedCount += typeCount.second;
            if (currentIndex < accumulatedCount) {
                selectedType = typeCount.first;
                break;
            }
        }

        // Create the selected type of bestiole
        std::unique_ptr<Bestiole> bestiole(BestioleFactory::createBestiole(selectedType));
        if (bestiole) {
            std::cout << "Adding new bestiole of type: " << selectedType << std::endl;
            addMember(*bestiole);
        }

        // Increment the counter for the current configuration
        configPair.first++;
    }
}

    

}

int Milieu::nbVoisins(const Bestiole& b) {
    int nb = 0;

    for (std::vector<Bestiole>::iterator it = listeBestioles.begin();
         it != listeBestioles.end(); ++it)
        if (!(b == *it) && b.jeTeVois(*it)) ++nb;

    return nb;
}

void Milieu::addPopulationConfig(const PopulationConfig& config) {
    populationConfigs.push_back(std::make_pair(0, config));
}

void Milieu::initFromConfigs(){
    for (const auto& config : populationConfigs) {
        for (const auto& typeCount : config.second.typeCounts) {
            for (int i = 0; i < typeCount.second; ++i) {
                std::unique_ptr<Bestiole> bestiole(BestioleFactory::createBestiole(typeCount.first));
                if (bestiole) {
                    addMember(*bestiole);
                }
            }
}
        
    
    }
}