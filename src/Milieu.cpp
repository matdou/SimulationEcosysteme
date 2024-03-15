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
    for (auto it = listeBestioles.begin(); it != listeBestioles.end(); ++it) {
        (*it)->action(*this);
        (*it)->draw(*this);
    }

    // Ajouter les Bestioles en fonction des configurations (birthRate)
    for (auto& config : populationConfigs) {
        double probability = (delay / 1000.0) * config.birthRate;
        if (probability > 1.0) probability = 1.0;
        if (std::rand() < probability * RAND_MAX) {
            std::unique_ptr<Bestiole> bestiole(
                BestioleFactory::createBestiole(config.getNextBirthType()));
            if (bestiole) {
                bestiole.get()->setLifeExpectancyFromAvg(
                    config.avgLifeTime,
                    config.lifeTimeStd);  // TODO : create method (encapsulation
                                          // principle)
                // initcoords
                addMember(std::move(bestiole));
            }
        }
    }
    // NOT NECESSARY :  Suppression des bestioles basée sur la probabilité de
    // décès
    double probability;
    for (auto& config : populationConfigs) {
        probability =
            (delay / 1000.0) * config.deathRate * listeBestioles.size();
        if (probability > 1.0)
            probability = 1.0;  // Assure que la probabilité ne dépasse pas 1

        if (!listeBestioles.empty() && std::rand() < probability * RAND_MAX) {
            // Sélectionne et supprime un élément aléatoire
            int index = std::rand() % listeBestioles.size();
            // Suppression sans itérateur
            listeBestioles.erase(listeBestioles.begin() + index);
        }
    }

    // Suppression des bestioles basée sur la duree de vie
    for (auto& config : populationConfigs) {
        for (auto it = listeBestioles.begin(); it != listeBestioles.end();) {
            if ((*it)->getLifeExpectancy() ==
                -1) {  

                ++it;
            } else if ((*it)->getLifeExpectancy() <= 0) {  
                it = listeBestioles.erase(it);
            } else {
                (*it)->setLifeExpectancy((*it)->getLifeExpectancy() -
                                         delay / 1000.0);  
                ++it;
            }
        }
    }
}

int Milieu::nbVoisins(const Bestiole& b) {
    int nb = 0;

    for (const auto& bestiolePtr : listeBestioles)
        if (!(b == *bestiolePtr) && b.jeTeVois(*bestiolePtr)) ++nb;

    return nb;
}


void Milieu::addPopulationConfig(const PopulationConfig& config) {
    populationConfigs.push_back(config);
}

void Milieu::initFromConfigs() {
    int sum = 0;
    for (const auto& config : populationConfigs) {
        for (const auto& typeCount : config.typeCounts) {
            sum += typeCount.second;
        }
    }
    listeBestioles.reserve(sum + 1000);  // TODO

    std::cout << "Reserve " << sum << " bestioles" << std::endl;
    for (const auto& config : populationConfigs) {
        for (const auto& typeCount : config.typeCounts) {
            for (int i = 0; i < typeCount.second; ++i) {
                std::unique_ptr<Bestiole> bestiole(
                    BestioleFactory::createBestiole(typeCount.first));
                bestiole.get()->setLifeExpectancyFromAvg(config.avgLifeTime,
                                                         config.lifeTimeStd);
                if (bestiole) {
                    addMember(std::move(bestiole));
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
                addMember(std::move(bestiole));
            }
        }
    }
}