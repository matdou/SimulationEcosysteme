#ifndef _BESTIOLE_KAMIKAZE_H_
#define _BESTIOLE_KAMIKAZE_H_

#include "Bestiole.h" // Inclure la définition de la classe de base Bestiole

class BestioleKamikaze : public Bestiole { // Hériter de la classe de base Bestiole
private:
    virtual void bouge(Milieu & monMilieu) override; // Redéfinir la fonction bouge() de la classe de base
};

#endif // _BESTIOLE_KAMIKAZE_H_
