#ifndef YEUX_H
#define YEUX_H

#include "Capteur.h"
#include <string>

class Yeux : public Capteur {
private:
    double champVision;
    double distanceVision;
    double capaciteDetection;
public:
    Yeux();
    ~Yeux() = default;
    static std::string getTypeName() { return "Yeux"; };

    bool jeTeVois(const Bestiole& bestiole, const Bestiole& moi) override;

};

#endif  // YEUX_H