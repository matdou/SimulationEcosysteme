#ifndef POPULATIONCONFIG_H
#define POPULATIONCONFIG_H

#include <iostream>
#include <map>
#include <string>
#include <vector>


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

    std::vector<std::string> globalCapteurs;

    double nageoiresSpeedFactor;
    double carapaceResistanceFactor;
    double carapaceSlownessFactor;
    double camouflageFactor;

    // Helper methods to manage current type state
    void setCurrentType(const std::string& typeName);
    void resetCurrentType();

public:
    PopulationConfig();

    // Modifier methods for type counts
    void addTypeCount(const std::string& typeName, int count);
    void removeTypeCount(const std::string& typeName);

    void addGlobalCapteur(std::string s);

    // Setters
    void setBirthRate(double rate) { birthRate = rate; }
    void setDeathRate(double a) { deathRate = a; }
    void setCloningRate(double a) { cloningRate = a; }
    void setAvgLifeTime(double a) { avgLifeTime = a; }
    void setLifeTimeStd(double a) { lifeTimeStd = a; }

    void addNageoires(double speedFactor);
    void addCarapace(double resistanceFactor, double slownessFactor);
    void addCamouflage(double factor);


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
    const std::vector<std::string>& getGlobalCapteurs() const { return globalCapteurs; }

    double getSpeedFactor() const { return nageoiresSpeedFactor; }
    double getProtectionFactor() const { return carapaceResistanceFactor; }
    double getSlownessFactor() const { return carapaceSlownessFactor; }
    double getCamouflageFactor() const { return camouflageFactor; }


};

#endif  // POPULATIONCONFIG_H
