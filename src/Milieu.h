#ifndef _MILIEU_H_
#define _MILIEU_H_

#include <iostream>
#include <vector>

#include "Bestiole.h"
#include "LifeCycleManager.h"
#include "PopulationConfig.h"
#include "UImg.h"

class Milieu : public UImg {
   private:
    static const T white[];

    int width, height;
    std::vector<std::unique_ptr<Bestiole>> listeBestioles;
    std::vector<PopulationConfig> populationConfigs;

    int delay;

    int timeSim = 0;

    int calculateTotalPopulationSize() const;

    void clearEnvironment();
    void processBestiolesActionsAndDrawings();
    LifeCycleManager lifeCycleManager;

   public:
    Milieu(int _width, int _height, int _delay);
    ~Milieu();

    int getWidth(void) const { return width; };
    int getHeight(void) const { return height; };
    PopulationConfig& getPopulationConfig(int index) {
        return populationConfigs[index];
    };  // NON CONST because it shuffles through the bestioles
    std::vector<PopulationConfig>& getPopulationConfigs() {
        return populationConfigs;
    };
    std::vector<std::unique_ptr<Bestiole>>& getBestioles() {
        return listeBestioles;
    };
    int getDelay() const { return delay; };

    void step(void);
    void addMember(std::unique_ptr<Bestiole> b);
    void addPopulationConfig(PopulationConfig& config);
    void initFromConfigs(void);
    void killMember(int identite);



    int getTimeSim() const { return timeSim; };
};

#endif
