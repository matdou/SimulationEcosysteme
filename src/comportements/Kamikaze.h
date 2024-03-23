#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "BestioleFactory.h"

class Kamikaze : public Bestiole {
   public:
    Kamikaze();
    virtual ~Kamikaze() override;  // Destructor
    static std::string getTypeName() { return "Kamikaze"; };
    static bool dummy;
    // Other methods
    void update(
        const std::vector<std::reference_wrapper<Bestiole>>& voisins) override;
    std::unique_ptr<Bestiole> clone() const override;
};

#endif  // KAMIKAZE_H