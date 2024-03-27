#ifndef GREGAIRE_H
#define GREGAIRE_H

#include "BestioleFactory.h"
#include "Comportement.h"

#include <memory>
#include <string>
#include <vector>
#include <functional>

class Gregaire : public Comportement {
public:
    // Constructors & Destructor
    Gregaire();
    virtual ~Gregaire() override;

    // Overridden methods from Bestiole
    void update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) override;
    std::unique_ptr<Bestiole> clone() const override;

    // Static variables
    static bool dummy; // Dummy variable to force the linker to include the class in the factory

};

#endif  // GREGAIRE_H
