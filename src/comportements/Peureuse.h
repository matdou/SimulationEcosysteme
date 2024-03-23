#ifndef PEUREUSE_H
#define PEUREUSE_H

#include "BestioleFactory.h"
#include <memory>
#include <string>
#include <vector>
#include <functional>

class Peureuse : public Bestiole {
public:
    // Constructors & Destructor
    Peureuse();
    virtual ~Peureuse() override;

    // Overridden methods from Bestiole
    void update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) override;
    std::unique_ptr<Bestiole> clone() const override;

    // Static methods
    static std::string getTypeName();

    // Static variables
    static bool dummy; // Dummy variable to force the linker to include the class in the factory

    // Class-specific variables
    int turnCooldown = 0; // Cooldown for turning 180 degrees
};

#endif  // PEUREUSE_H
