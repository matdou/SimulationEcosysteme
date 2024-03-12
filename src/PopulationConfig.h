#ifndef POPULATIONCONFIG_H
#define POPULATIONCONFIG_H

#include <map>
#include <string>

class PopulationConfig {
public:
    // Map contenant le nombre de bestioles de chaque type
    std::map<std::string, int> typeCounts;
    //taux de naissance
    double birthRate;

    // Ajouter une méthode pour faciliter l'ajout de nouveaux types
    void addTypeCount(const std::string& typeName, int count) {
        typeCounts[typeName] = count;
    }

    void removeTypeCount(const std::string& typeName) {
        typeCounts.erase(typeName);
    }

    void setBirthRate(double rate) {
        birthRate = rate;
    }


};

#endif // POPULATIONCONFIG_H
