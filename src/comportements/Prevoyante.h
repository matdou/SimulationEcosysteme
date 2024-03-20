#ifndef PREVOYANTE_H
#define PREVOYANTE_H

#include "BestioleFactory.h"

class Prevoyante : public Bestiole {
   public:
    Prevoyante();
    virtual ~Prevoyante() override;
    static std::string getTypeName() { return "Prevoyante"; };
    static bool dummy;
    void update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) override;
    std::unique_ptr<Bestiole> clone() const override;
};

#endif  // PREVOYANTE_H