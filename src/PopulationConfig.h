#ifndef POPULATIONCONFIG_H
#define POPULATIONCONFIG_H

#include <iostream>
#include <map>
#include <string>

class PopulationConfig {
private:
    std::map<std::string, int> typeCounts; // Typename to count mapping
    double birthRate;
    double deathRate;
    double cloningRate;
    double avgLifeTime;
    double lifeTimeStd;

    int currentTypeCount;
    std::string currentTypeName;

    // Helper methods to manage current type state
    void setCurrentType(const std::string& typeName);
    void resetCurrentType();

public:
    PopulationConfig();

    // Modifier methods for type counts
    void addTypeCount(const std::string& typeName, int count);
    void removeTypeCount(const std::string& typeName);

    // Setters
    void setBirthRate(double rate) { birthRate = rate; }
    void setDeathRate(double a) { deathRate = a; }
    void setCloningRate(double a) { cloningRate = a; }
    void setAvgLifeTime(double a) { avgLifeTime = a; }
    void setLifeTimeStd(double a) { lifeTimeStd = a; }

    // Accessor methods
    std::string getNextBirthType();
    int getTotalPopulationSize() const;
    double getBirthRate() const { return birthRate; }
    double getDeathRate() const { return deathRate; }
    double getCloningRate() const { return cloningRate; }
    double getAvgLifeTime() const { return avgLifeTime; }
    double getLifeTimeStd() const { return lifeTimeStd; }
    std::string getCurrentTypeName() const { return currentTypeName; }
    const std::map<std::string, int>& getTypeCounts() const { return typeCounts; }

};

#endif  // POPULATIONCONFIG_H
