#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "BestioleFactory.h"
#include <memory>
#include <string>
#include <vector>
#include <functional>

class Kamikaze : public Bestiole {
public:
    // Constructors & Destructor
    Kamikaze();
    virtual ~Kamikaze() override;

    // Overridden methods from Bestiole
    void update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) override;
    std::unique_ptr<Bestiole> clone() const override;

    // Static methods
    static std::string getTypeName();

    // Static variables
    static bool dummy; // Dummy variable to force the linker to include the class in the factory
};

#endif  // KAMIKAZE_H
