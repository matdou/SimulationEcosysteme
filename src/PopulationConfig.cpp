#include "PopulationConfig.h"

PopulationConfig::PopulationConfig() : birthRate(0.0), deathRate(0.0), avgLifeTime(-1), currentTypeName(""), lifeTimeStd(0.5) {}

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

void PopulationConfig::setBirthRate(double rate) {
    birthRate = rate;
}

std::string PopulationConfig::getNextBirthType() {
    if (typeCounts.empty()) {
        std::cerr << "typeCounts is empty" << std::endl;
        return "";
    }

    if (currentTypeName.empty()) {
        currentTypeName = typeCounts.begin()->first;
    }

    auto it = typeCounts.find(currentTypeName);
    if (it == typeCounts.end()) {
        it = typeCounts.begin();
        currentTypeName = it->first;
    }

    std::string nextBirthType = it->first;

    ++it;
    if (it == typeCounts.end()) {
        it = typeCounts.begin();
    }
    currentTypeName = it->first;

    return nextBirthType;
}

void PopulationConfig::setDeathRate(double a) {
    deathRate = a;
}

void PopulationConfig::setAvgLifeTime(double a) {
    avgLifeTime = a;
}
