#ifndef ICAPTEUR_H
#define ICAPTEUR_H

#include <memory>


class Bestiole; // Forward declaration
class Milieu; // Forward declaration


class Capteur {
protected:
     //std::unique_ptr<Bestiole> decoratedBestiole;
public:
     ~Capteur() = default;
    void percevoirEnvironnement(const Milieu& milieu, const Bestiole& bestiole);
    virtual bool jeTeVois(const Bestiole& bestiole, const Bestiole& moi) = 0;
};

#endif  // ICAPTEUR_H