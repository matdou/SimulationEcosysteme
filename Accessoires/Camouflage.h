#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_

#include "Accessoire.h"

class Camouflage : public Accessoire {
private:
    static const double PSI_MAX;
    static const double PSI_MIN;

private:
    double psi;

public:
    Camouflage();
    bool isNageoire();
    bool isCarapace();
    bool isCamouflage();
    double getPsi();
};

#endif