#ifndef _MILIEU_H_
#define _MILIEU_H_

#include <iostream>
#include <vector>

#include "Bestiole.h"
#include "PopulationConfig.h"
#include "UImg.h"
#include "LifeCycleManager.h"

class Milieu : public UImg {
private:
    static const T white[];

    int width, height;
    std::vector<std::unique_ptr<Bestiole>> listeBestioles;
    std::vector<PopulationConfig> populationConfigs;

    int delay;

    int calculateTotalPopulationSize() const;
    // void createAndAddBestiole(const PopulationConfig& config, const const std::pair<const std::string, int>& typeCount);

    void clearEnvironment();
    void processBestiolesActionsAndDrawings();
    LifeCycleManager lifeCycleManager;


public:
    Milieu(int _width, int _height, int _delay);
    ~Milieu();

    int getWidth(void) const { return width; };
    int getHeight(void) const { return height; };
    PopulationConfig& getPopulationConfig(int index) { return populationConfigs[index]; }; // NON CONST because it shuffles through the bestioles
    std::vector<PopulationConfig>& getPopulationConfigs() { return populationConfigs; }; 
    std::vector<std::unique_ptr<Bestiole>>& getBestioles() { return listeBestioles; };
    int getDelay() const { return delay; };

    void step(void);
    void addMember(std::unique_ptr<Bestiole> b);
    int nbVoisins(const Bestiole& b);
    void addPopulationConfig(PopulationConfig& config);
    void initFromConfigs(void);
    void killMember(int identite);

    void updateBestiolesFromCapteurs();
    std::vector<std::reference_wrapper<Bestiole>> visibleNeighbors(std::unique_ptr<Bestiole>& b);
    
    void handleCollisions();
};

#endif
