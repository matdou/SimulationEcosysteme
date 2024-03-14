#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "BestioleFactory.h"

const T Milieu::white[] = {(T)255, (T)255, (T)255};

Milieu::Milieu(int _width, int _height, int _delay)
    : UImg(_width, _height, 1, 3), width(_width), height(_height) {
    cout << "const Milieu" << endl;
    delay = _delay;
    std::srand(time(NULL));
}

Milieu::~Milieu(void) { cout << "dest Milieu" << endl; }

void Milieu::step(void) {
    cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);
    for (std::vector<Bestiole>::iterator it = listeBestioles.begin();
         it != listeBestioles.end(); ++it) {
        it->action(*this);
        std::cout << "Milieu : step : bestiole before draw" << std::endl;
        it->draw(*this);
        std::cout << "Milieu : step : bestiole after draw" << std::endl;
    }

    // Ajouter les Bestioles en fonction des configurations (birthRate)
    std::cout << "Milieu : step :  birthRate " << populationConfigs.size()
              << std::endl;
    for (auto& config : populationConfigs) {
        std::cout << "Milieu : step :  birthRate : BIRTH " << config.birthRate
                  << std::endl;
        double probability = (delay / 1000.0) / config.birthRate;
        if (probability > 1.0) probability = 1.0;
        if (std::rand() < probability * RAND_MAX) {
            std::cout << "Milieu : birth" << std::endl;
            std::unique_ptr<Bestiole> bestiole(
                BestioleFactory::createBestiole(config.getNextBirthType()));
            if (bestiole) {
                addMember(*bestiole);
            }
        }
    }
    // Suppression des bestioles basée sur la probabilité de décès
    double probability;
    for (auto& config : populationConfigs) {
        probability =
            (delay / 1000.0) / config.deathRate * listeBestioles.size();
        if (probability > 1.0)
            probability = 1.0;  // Assure que la probabilité ne dépasse pas 1

        if (!listeBestioles.empty() && std::rand() < probability * RAND_MAX) {
            // Sélectionne et supprime un élément aléatoire
            int index = std::rand() % listeBestioles.size();
            // Suppression sans itérateur
            listeBestioles.erase(listeBestioles.begin() + index);
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

void Milieu::initFromConfigs() {
    for (const auto& config : populationConfigs) {
        for (const auto& typeCount : config.typeCounts) {
            for (int i = 0; i < typeCount.second; ++i) {
                std::unique_ptr<Bestiole> bestiole(
                    BestioleFactory::createBestiole(typeCount.first));
                if (bestiole) {
                    addMember(*bestiole);
                }
            }
        }
    }
}

void Milieu::artificialBirth(PopulationConfig config) {
    for (const auto& typeCount : config.typeCounts) {
        for (int i = 0; i < typeCount.second; ++i) {
            std::unique_ptr<Bestiole> bestiole(
                BestioleFactory::createBestiole(typeCount.first));
            if (bestiole) {
                addMember(*bestiole);
            }
        }
    }
}