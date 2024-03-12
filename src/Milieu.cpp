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

    // Ajouter les Bestioles en fonction des configurations (birthRate)

    for (auto& config : populationConfigs) { // 
        if (std::rand() < config.birthRate * RAND_MAX) {
            // Birth
            std::cout << "Milieu : birth" << std::endl;
            std::unique_ptr<Bestiole> bestiole(BestioleFactory::createBestiole(config.getNextBirthType())); 
            if (bestiole) {
                addMember(*bestiole);
            }
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
    populationConfigs.push_back(config);
}

void Milieu::initFromConfigs(){
    for (const auto& config : populationConfigs) {
        for (const auto& typeCount : config.typeCounts) {
            for (int i = 0; i < typeCount.second; ++i) {
                std::unique_ptr<Bestiole> bestiole(BestioleFactory::createBestiole(typeCount.first));
                if (bestiole) {
                    addMember(*bestiole);
                }
            }
        } 
    }
}

void Milieu::artificialBirth(PopulationConfig config){
    for (const auto& typeCount : config.typeCounts) {
        for (int i = 0; i < typeCount.second; ++i) {
            std::unique_ptr<Bestiole> bestiole(BestioleFactory::createBestiole(typeCount.first));
            if (bestiole) {
                addMember(*bestiole);
            }
        }
    }
}