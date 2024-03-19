#include "PopulationConfig.h"

PopulationConfig::PopulationConfig()
    : birthRate(0.0),
      deathRate(0.0),
      avgLifeTime(-1),
      currentTypeName(""),
      lifeTimeStd(0.5) {}

void PopulationConfig::addTypeCount(const std::string& typeName, int count) {
    if (typeCounts.empty()) {
        currentTypeName = typeName;
    }
    typeCounts[typeName] = count;
}

void PopulationConfig::removeTypeCount(const std::string& typeName) {
    typeCounts.erase(typeName);
    if (currentTypeName == typeName) {
        if (!typeCounts.empty()) {
            currentTypeName = typeCounts.begin()->first;
        } else {
            currentTypeName = "";
        }
    }
}

void PopulationConfig::setBirthRate(double rate) { birthRate = rate; }

std::string PopulationConfig::getNextBirthType() {


    auto it = typeCounts.find(currentTypeName);
    currentTypeCount++;
    std::cout << "Current type count: " << currentTypeCount << std::endl;
    std::cout << "Current type name: " << currentTypeName << std::endl;

    if (currentTypeCount >= it->second) {
        std::cout << "Current type count is greater than or equal to type count" << std::endl;
        currentTypeCount = 0;
        ++it;
    }

    if (it == typeCounts.end()) {
        std::cout << "Iterator is at the end" << std::endl;
        it = typeCounts.begin();
        currentTypeName = it->first;
    }
    currentTypeName = it->first;


    std::string nextBirthType = it->first;


    return nextBirthType;
}

void PopulationConfig::setDeathRate(double a) { deathRate = a; }

void PopulationConfig::setAvgLifeTime(double a) { avgLifeTime = a; }

void PopulationConfig::setLifeTimeStd(double a) { lifeTimeStd = a; }

int PopulationConfig::getTotalPopulationSize() const {
    int total = 0;
    for (auto& pair : typeCounts) {
        total += pair.second;
    }
    return total;
}