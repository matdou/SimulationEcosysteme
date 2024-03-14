#ifndef POPULATIONCONFIG_H
#define POPULATIONCONFIG_H

#include <iostream>
#include <map>
#include <string>

class PopulationConfig {
   public:
    std::map<std::string, int> typeCounts;
    double birthRate;
    double deathRate;
    // Use currentTypeName to track the current type instead of a direct
    // iterator to avoid invalidation issues.
    std::string currentTypeName;

    PopulationConfig() : birthRate(0.0), currentTypeName("") {}

    void addTypeCount(const std::string& typeName, int count) {
        if (typeCounts.empty()) {
            // If adding the first type, set it as the current type.
            currentTypeName = typeName;
        }
        typeCounts[typeName] = count;
    }

    void removeTypeCount(const std::string& typeName) {
        typeCounts.erase(typeName);
        if (currentTypeName == typeName) {
            // If the current type was removed, reset to the beginning of the
            // map, if possible.
            if (!typeCounts.empty()) {
                currentTypeName = typeCounts.begin()->first;
            } else {
                // If the map is now empty, reset currentTypeName.
                currentTypeName = "";
            }
        }
    }

    void setBirthRate(double rate) { birthRate = rate; }

    std::string getNextBirthType() {
        if (typeCounts.empty()) {
            std::cerr << "typeCounts is empty" << std::endl;
            return "";
        }

        if (currentTypeName.empty()) {
            // This condition should not happen if methods are used correctly,
            // but added as a safety measure.
            currentTypeName = typeCounts.begin()->first;
        }

        auto it = typeCounts.find(currentTypeName);
        if (it == typeCounts.end()) {
            // In case currentTypeName is not found, which should not normally
            // occur, reset to the first element.
            it = typeCounts.begin();
            currentTypeName = it->first;
        }

        // Preparing to return the current type and advance to the next one
        std::string nextBirthType = it->first;

        // Move to the next type, or wrap around to the beginning if at the end
        ++it;
        if (it == typeCounts.end()) {
            it = typeCounts.begin();
        }
        currentTypeName = it->first;

        return nextBirthType;
    }

    void setDeathRate(T a) {
        deathRate = a;
    };
};

#endif  // POPULATIONCONFIG_H
