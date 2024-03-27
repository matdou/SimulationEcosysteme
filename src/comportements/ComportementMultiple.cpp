
#include "Capteur.h"

#include "ComportementMultiple.h"

static bool dummy = []() {
    BestioleFactory::registerType("ComportementMultiple",
                                  []() -> Bestiole* { return new ComportementMultiple(); });
    return true;
}();

ComportementMultiple::ComportementMultiple() {
    comportementActuel = GREGAIRE;
}

// Destructor
ComportementMultiple::~ComportementMultiple() {}

// Update the Orientation of the Bestiole based on the average orientation of
// its neighbors
void ComportementMultiple::update(
    const std::vector<std::reference_wrapper<Bestiole>>& voisins) {
    switch(comportementActuel) {
        case GREGAIRE:
            Comportement::gregaireUpdate(voisins);
            break;
        case PEUREUSE:
            Comportement::peureuseUpdate(voisins);
            break;
        case PREVOYANTE:
            Comportement::prevoyanteUpdate(voisins);
            break;
        case KAMIKAZE:
            Comportement::kamikazeUpdate(voisins);
            break;
    }

}
void ComportementMultiple::UpdateComportementForComportementMultiple(){
    comportementActuel = static_cast<ComportementActif>(rand() % 4);
}

std::unique_ptr<Bestiole> ComportementMultiple::clone() const {
    return std::make_unique<ComportementMultiple>(*this);
}
