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
    std::vector<Bestiole> listeBestioles;
    std::vector<PopulationConfig> populationConfigs;

    int delay;

   public:
    Milieu(int _width, int _height, int _delay);
    ~Milieu(void);

    int getWidth(void) const { return width; };
    int getHeight(void) const { return height; };

    void step(void);

    void addMember(const Bestiole& b) {
        listeBestioles.push_back(b);  // TODO 
        listeBestioles.back().initCoords(width, height);
    }
    int nbVoisins(const Bestiole& b);

    void addPopulationConfig(const PopulationConfig& config);

    void initFromConfigs(void);

    void artificialBirth(PopulationConfig);
};

#endif
