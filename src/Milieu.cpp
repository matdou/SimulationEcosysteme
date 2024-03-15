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
        it->draw(*this);
    }

    // Ajouter les Bestioles en fonction des configurations (birthRate)
    for (auto& config : populationConfigs) {
        double probability = (delay / 1000.0) * config.birthRate;
        if (probability > 1.0) probability = 1.0;
        if (std::rand() < probability * RAND_MAX) {
            std::unique_ptr<Bestiole> bestiole(
                BestioleFactory::createBestiole(config.getNextBirthType()));
            if (bestiole) {
                bestiole.get()->setLifeExpectancyFromAvg(config.avgLifeTime, config.lifeTimeStd);// TODO : create method (encapsulation principle)
                addMember(*bestiole);
                std::cout << "Bestiole " << bestiole->getIdentite()
                          << " is born from birth " << std::endl;
            }
        }
    }
    // NOT NECESSARY :  Suppression des bestioles basée sur la probabilité de décès
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
            std::cout << "Bestiole " << listeBestioles[index].getIdentite()
                      << " is dead from death " << std::endl;
            listeBestioles.erase(listeBestioles.begin() + index);
        }
    }

    // Suppression des bestioles basée sur la duree de vie

    for (auto& config : populationConfigs) {
        for (auto it = listeBestioles.begin(); it != listeBestioles.end();) {
            //check if life expectancy is -1 = infinie life
            // in that case, ++it
            // else, check if lifeTime is negative in that case delete and ++it
            // else increse lifeTime and ++it
            if (it->getLifeExpectancy() == -1) {
                ++it;
            } else if (it->getLifeExpectancy() <= 0) {
                it = listeBestioles.erase(it);
            } else {
                it->setLifeExpectancy(it->getLifeExpectancy() - delay / 1000.0);
                std::cout << "Life expectancy of bestiole " << it->getIdentite()
                          << " is " << it->getLifeExpectancy() << std::endl;
                ++it;
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

void Milieu::initFromConfigs() {

    int sum = 0;
    for (const auto& config : populationConfigs) {
        for (const auto& typeCount : config.typeCounts) {
            sum += typeCount.second;
        }
    }
    listeBestioles.reserve(sum); // TODO 

    std::cout << "Reserve " << sum << " bestioles" << std::endl;
    for (const auto& config : populationConfigs) {
        for (const auto& typeCount : config.typeCounts) {
            for (int i = 0; i < typeCount.second; ++i) {
                std::unique_ptr<Bestiole> bestiole(
                    BestioleFactory::createBestiole(typeCount.first));
                    bestiole.get()->setLifeExpectancyFromAvg(config.avgLifeTime, config.lifeTimeStd);
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