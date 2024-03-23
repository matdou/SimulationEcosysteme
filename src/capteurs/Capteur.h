#ifndef ICAPTEUR_H
#define ICAPTEUR_H

#include <memory>

class Bestiole;  // Forward declaration
class Milieu;    // Forward declaration

class Capteur {
   public:
    virtual ~Capteur() = default;  // Virtual destructor
    virtual bool jeTeVois(const Bestiole& bestiole, const Bestiole& moi) = 0;
    virtual std::unique_ptr<Capteur> clone() const = 0;
};

#endif  // ICAPTEUR_H