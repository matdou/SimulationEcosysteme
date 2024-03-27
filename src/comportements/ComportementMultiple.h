#ifndef COMPORTEMENTMULTIPLE_H
#define COMPORTEMENTMULTIPLE_H


#include "BestioleFactory.h"
#include "Comportement.h"

#include <memory>
#include <string>
#include <vector>
#include <functional>

class ComportementMultiple : public Comportement {
private:
    enum ComportementActif { GREGAIRE, PEUREUSE, PREVOYANTE, KAMIKAZE } comportementActuel;
public:
    // Constructors & Destructor
    ComportementMultiple();
    virtual ~ComportementMultiple() override;

    // Overridden methods from Bestiole
    void update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) override;
    std::unique_ptr<Bestiole> clone() const override;

    // Static methods
    static std::string getTypeName();

    // Static variables
    static bool dummy; // Dummy variable to force the linker to include the class in the factory

    void changeComportementRandom();
    virtual void UpdateComportementForComportementMultiple() override;
};


#endif  // COMPORTEMENTMULTIPLE_H