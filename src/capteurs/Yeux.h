#ifndef YEUX_H
#define YEUX_H

#include <string>

#include "Capteur.h"

class Yeux : public Capteur {
   private:
    double champVision;
    double distanceVision;
    double capaciteDetection;

    static const double MIN_ANGLE;
    static const double MAX_ANGLE;
    static const double MIN_DISTANCE;
    static const double MAX_DISTANCE;
    static const double MIN_DETECTION;
    static const double MAX_DETECTION;


   public:
    Yeux();
    Yeux(double champVision, double distanceVision, double capaciteDetection);
    ~Yeux() = default;
    static std::string getTypeName() { return "Yeux"; };

    bool jeTeVois(const Bestiole& bestiole, const Bestiole& moi) override;
    std::unique_ptr<Capteur> clone() const override;
};

#endif  // YEUX_H