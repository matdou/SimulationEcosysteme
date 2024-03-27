#ifndef COMPORTEMENT_H
#define COMPORTEMENT_H

#include "Bestiole.h"

class Comportement : public Bestiole {
    private:
        // Class-specific variables
        int turnCooldown = 0; // Cooldown for turning 180 degrees for Peureuse
        static const int TURN_COOLDOWN = 20;
    public:
        void gregaireUpdate(const std::vector<std::reference_wrapper<Bestiole>>& voisins);
        void peureuseUpdate(const std::vector<std::reference_wrapper<Bestiole>>& voisins);
        void kamikazeUpdate(const std::vector<std::reference_wrapper<Bestiole>>& voisins);
        void prevoyanteUpdate(const std::vector<std::reference_wrapper<Bestiole>>& voisins);
};




#endif  // COMPORTEMENT_H