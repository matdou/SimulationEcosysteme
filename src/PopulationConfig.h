#ifndef POPULATIONCONFIG_H
#define POPULATIONCONFIG_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Capteur.h"

class PopulationConfig {
   private:
    std::map<std::string, int> typeCounts;  // Typename to count mapping
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
    PopulationConfig(const PopulationConfig& other);  // Copy constructor
    PopulationConfig& operator=(const PopulationConfig& other);

    // Modifier methods for type counts
    void addTypeCount(const std::string& typeName, int count);
    void removeTypeCount(const std::string& typeName);

    void setTotalCount(int c);
    // Setters
    void setBirthRate(double rate) { birthRate = rate; }
    void setDeathRate(double a) { deathRate = a; }
    void setCloningRate(double a) { cloningRate = a; }
    void setAvgLifeTime(double a) { avgLifeTime = a; }
    void setLifeTimeStd(double a) { lifeTimeStd = a; }


    /**  Add fins to the configuration
     * @param speedFactor The speed factor of the fins, 1.0 is normal speed
    */
    void addNageoires(double speedFactor);

    /** Add a carapace to the configuration
     * @param resistanceFactor The resistance factor of the carapace, 1.0 is normal resistance
     * @param slownessFactor The slowness factor of the carapace, 1.0 is normal speed, bigger means slower
     */
    void addCarapace(double resistanceFactor, double slownessFactor);

    /** Add a stealth factor to the configuration
     * @param factor The camouflage factor, 0.0 means no camouflage, 1.0 means full camouflage
     */
    void addCamouflage(double factor);

    /** Add a new eye sensor to the configuration 
     * @param champVision The field of vision of the eye sensor
     * @param distanceVision The distance the eye sensor can see
     * @param capaciteDetection The detection capacity of the eye sensor
     */
    void addYeux(double champVision, double distanceVision,
                 double capaciteDetection);
    
    /** Add a new ear sensor to the configuration
     * @param distanceAudible The distance the ear sensor can hear
     * @param capaciteDetection The detection capacity of the ear sensor
    */
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
    const std::map<std::string, int>& getTypeCounts() const {
        return typeCounts;
    }
    std::vector<std::unique_ptr<Capteur>>& getCapteurs() { return capteurs; }
    double getSpeedFactor() const { return nageoiresSpeedFactor; }
    double getProtectionFactor() const { return carapaceResistanceFactor; }
    double getSlownessFactor() const { return carapaceSlownessFactor; }
    double getCamouflageFactor() const { return camouflageFactor; }
};

#endif  // POPULATIONCONFIG_H
