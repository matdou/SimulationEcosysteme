#ifndef _MILIEU_H_
#define _MILIEU_H_

#include <iostream>
#include <vector>

#include "Bestiole.h"
#include "PopulationConfig.h"
#include "UImg.h"

using namespace std;

class Milieu : public UImg {
private:
    static const T white[];

    int width, height;
    std::vector<std::unique_ptr<Bestiole>> listeBestioles;
    std::vector<PopulationConfig> populationConfigs;

    int delay;

    int calculateTotalPopulationSize() const;
    void createAndAddBestiole(const PopulationConfig& config, const const std::pair<const std::string, int>& typeCount);

public:
    Milieu(int _width, int _height, int _delay);
    ~Milieu(void);

    int getWidth(void) const { return width; };
    int getHeight(void) const { return height; };

    void step(void);

    void addMember(std::unique_ptr<Bestiole> b);

    int nbVoisins(const Bestiole& b);

    void addPopulationConfig(const PopulationConfig& config);
    

    void initFromConfigs(void);

    void killMember(int identite);
};

#endif
