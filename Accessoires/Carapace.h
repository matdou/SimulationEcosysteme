#ifndef _CARAPACE_H_
#define _CARAPACE_H_

#include "Accessoire.h"

class Carapace : public Accessoire {
private:
    static const double OMEGA_MAX;
    static const double MU_MAX;

private:
    double omega;
    double mu;

public:
    Carapace();
    bool isNageoire();
    bool isCarapace();
    bool isCamouflage();
    double getOmega();
    double getMu();
};

#endif