#ifndef PEUREUSE_H
#define PEUREUSE_H

#include "BestioleFactory.h"

class Peureuse : public Bestiole {
   public:
    Peureuse();
    static std::string getTypeName() { return "Peureuse"; }
    static bool dummy;
    // Other methods
};

#endif  // PEUREUSE_H
