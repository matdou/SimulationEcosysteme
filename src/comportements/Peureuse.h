#ifndef PEUREUSE_H
#define PEUREUSE_H

#include "BestioleFactory.h"

class Peureuse : public Bestiole {
   public:
    Peureuse();
    virtual ~Peureuse() override;
    static std::string getTypeName() { return "Peureuse"; }
    static bool dummy;
    void update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) override;
    std::unique_ptr<Bestiole> clone() const override;
};

#endif  // PEUREUSE_H
