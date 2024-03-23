#ifndef GREGAIRE_H
#define GREGAIRE_H

#include "BestioleFactory.h"

class Gregaire : public Bestiole {
   public:
    Gregaire();
    virtual ~Gregaire() override;  // Destructor
    static std::string getTypeName() { return "Gregaire"; }
    static bool dummy;

    void update(
        const std::vector<std::reference_wrapper<Bestiole>>& voisins) override;
    std::unique_ptr<Bestiole> clone() const override;
};

#endif  // GREGAIRE
