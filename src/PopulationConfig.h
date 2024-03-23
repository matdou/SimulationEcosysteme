#ifndef POPULATIONCONFIG_H
#define POPULATIONCONFIG_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Capteur.h"


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

    std::vector<std::unique_ptr<Capteur>> capteurs;

    double nageoiresSpeedFactor;
    double carapaceResistanceFactor;
    double carapaceSlownessFactor;
    double camouflageFactor;

    // Helper methods to manage current type state
    void setCurrentType(const std::string& typeName);
    void resetCurrentType();

public:
    PopulationConfig();
    PopulationConfig(const PopulationConfig& other); // Copy constructor
    PopulationConfig& operator=(const PopulationConfig& other);

    // Modifier methods for type counts
    void addTypeCount(const std::string& typeName, int count);
    void removeTypeCount(const std::string& typeName);

    // Setters
    void setBirthRate(double rate) { birthRate = rate; }
    void setDeathRate(double a) { deathRate = a; }
    void setCloningRate(double a) { cloningRate = a; }
    void setAvgLifeTime(double a) { avgLifeTime = a; }
    void setLifeTimeStd(double a) { lifeTimeStd = a; }

    void addNageoires(double speedFactor);
    void addCarapace(double resistanceFactor, double slownessFactor);
    void addCamouflage(double factor);

    void addYeux(double champVision, double distanceVision, double capaciteDetection);
    void addOreilles(double distanceAudible, double capaciteDetection);


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
     std::vector<std::unique_ptr<Capteur>>& getCapteurs() { return capteurs; }
    double getSpeedFactor() const { return nageoiresSpeedFactor; }
    double getProtectionFactor() const { return carapaceResistanceFactor; }
    double getSlownessFactor() const { return carapaceSlownessFactor; }
    double getCamouflageFactor() const { return camouflageFactor; }


};

#endif  // POPULATIONCONFIG_H
