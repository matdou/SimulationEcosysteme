#ifndef COMPORTEMENT_H
#define COMPORTEMENT_H

#include "Bestiole.h"

class Comportement { // Strategy pattern
public:
    virtual void appliquer(Bestiole& bestiole) = 0;
};

class ComportementPeureux : public Comportement {
public:
    void appliquer(Bestiole& bestiole) override;
};

class ComportementKamikaze : public Comportement {
public:
    void appliquer(Bestiole& bestiole) override;
};

class ComportementGregaire : public Comportement {
public:
    void appliquer(Bestiole& bestiole) override;
};

#endif // COMPORTEMENT_H
