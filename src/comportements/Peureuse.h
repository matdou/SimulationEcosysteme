#ifndef PEUREUSE_H
#define PEUREUSE_H

#include "BestioleFactory.h"
#include "Comportement.h"

#include <memory>
#include <string>
#include <vector>
#include <functional>

class Peureuse : public Comportement {
public:
    // Constructors & Destructor
    Peureuse();
    virtual ~Peureuse() override;

    // Overridden methods from Bestiole
    void update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) override;
    std::unique_ptr<Bestiole> clone() const override;

    // Static variables
    static bool dummy; // Dummy variable to force the linker to include the class in the factory
};

#endif  // PEUREUSE_H
