#ifndef BESTIOLEFACTORY_H
#define BESTIOLEFACTORY_H

#include "Bestiole.h"
#include <type_traits>

class BestioleFactory {
public:
    template <typename BestioleType>
    static Bestiole* createBestiole() {
        static_assert(std::is_base_of<Bestiole, BestioleType>::value, "BestioleType must derive from Bestiole");
        return new BestioleType();
    }

    // Example of a non-template method declaration
    static void someUtilityFunction();
};

#endif // BESTIOLEFACTORY_H
