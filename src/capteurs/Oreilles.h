#ifndef OREILLES_H
#define OREILLES_H

#include "Capteur.h"
#include <string>

class Oreilles : public Capteur {
private:

    double distanceAudible;
    double capaciteDetection;
public:
    Oreilles();
    ~Oreilles() = default;
    static std::string getTypeName() { return "Oreilles"; };

    bool jeTeVois(const Bestiole& bestiole, const Bestiole& moi) override;

};

#endif  // OREILLES_H