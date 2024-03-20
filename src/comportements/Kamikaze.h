#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "BestioleFactory.h"

class Kamikaze : public Bestiole {
   public:
    Kamikaze();
    static std::string getTypeName() { return "Kamikaze"; };
    static bool dummy;
    // Other methods
};

#endif  // KAMIKAZE_H