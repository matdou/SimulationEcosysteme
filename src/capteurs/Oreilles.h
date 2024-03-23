#ifndef OREILLES_H
#define OREILLES_H

#include <string>

#include "Capteur.h"

class Oreilles : public Capteur {
   private:
    double distanceAudible;
    double capaciteDetection;

   public:
    Oreilles();
    Oreilles(double distanceAudible, double capaciteDetection);
    ~Oreilles() = default;
    static std::string getTypeName() { return "Oreilles"; };

    bool jeTeVois(const Bestiole& bestiole, const Bestiole& moi) override;
    std::unique_ptr<Capteur> clone() const override;
};

#endif  // OREILLES_H