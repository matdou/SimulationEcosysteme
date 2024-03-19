#ifndef POPULATIONCONFIG_H
#define POPULATIONCONFIG_H

#include <iostream>
#include <map>
#include <string>

struct PopulationConfig {
    std::map<std::string, int> typeCounts;  // typename, count
    double birthRate;
    double deathRate;
    double avgLifeTime;
    double lifeTimeStd;

    int currentTypeCount;
    std::string currentTypeName;
    

    PopulationConfig();

    void addTypeCount(const std::string& typeName, int count);
    void removeTypeCount(const std::string& typeName);
    void setBirthRate(double rate);
    std::string getNextBirthType();
    void setDeathRate(double a);
    void setAvgLifeTime(double a);
    void setLifeTimeStd(double a);
    int getTotalPopulationSize() const;
};

#endif  // POPULATIONCONFIG_H
