#ifndef GREGAIRE_H
#define GREGAIRE_H

#include "BestioleFactory.h"

class Gregaire : public Bestiole {
   public:
    Gregaire();
    static std::string getTypeName() { return "Gregaire"; }
    static bool dummy;
};

#endif  // GREGAIRE
