#include "PopulationConfig.h"

PopulationConfig::PopulationConfig() : birthRate(0.0), deathRate(0.0), avgLifeTime(-1), lifeTimeStd(0.5), currentTypeCount(0) {}

void PopulationConfig::addTypeCount(const std::string& typeName, int count) {
    typeCounts[typeName] = count;
    if (typeCounts.size() == 1) {
        setCurrentType(typeName);
    }
}

void PopulationConfig::removeTypeCount(const std::string& typeName) {
    typeCounts.erase(typeName);
    if (currentTypeName == typeName) {
        if (!typeCounts.empty()) {
            setCurrentType(typeCounts.begin()->first);
        } else {
            resetCurrentType();
        }
    }
}

void PopulationConfig::setCurrentType(const std::string& typeName) {
    currentTypeName = typeName;
    currentTypeCount = 0; // Always reset count when setting a new type
}

void PopulationConfig::resetCurrentType() {
    currentTypeName = "";
    currentTypeCount = 0;
}

std::string PopulationConfig::getNextBirthType() {
    if (typeCounts.empty()) {
        return ""; // Return an empty string if no types are configured
    }

    if (++currentTypeCount >= typeCounts[currentTypeName]) {
        auto it = typeCounts.find(currentTypeName);
        if (++it == typeCounts.end()) {
            it = typeCounts.begin();
        }
        setCurrentType(it->first);
    }

    return currentTypeName;
}

int PopulationConfig::getTotalPopulationSize() const {
    int total = 0;
    for (const auto& pair : typeCounts) {
        total += pair.second;
    }
    return total;
}
