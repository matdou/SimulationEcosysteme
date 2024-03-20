#ifndef PREVOYANTE_H
#define PREVOYANTE_H

#include "BestioleFactory.h"

class Prevoyante : public Bestiole {
   public:
    Prevoyante();
    static std::string getTypeName() { return "Prevoyante"; };
    static bool dummy;
    // Other methods
};

#endif  // PREVOYANTE_H