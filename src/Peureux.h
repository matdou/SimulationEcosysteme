#ifndef PEUREUX_H
#define PEUREUX_H

#include "Bestiole.h"
#include "BestioleFactory.h"

class Peureux : public Bestiole {
   public:
    Peureux();
    static std::string getTypeName() { return "Peureux"; }
    static bool dummy;
    // Other methods
};

#endif  // PEUREUX_H
