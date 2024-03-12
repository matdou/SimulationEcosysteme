#ifndef BESTIOLECREATOR_H
#define BESTIOLECREATOR_H

#include "ICreator.h"

template <typename T>
class BestioleCreator : public ICreator {
public:
    IBestiole* createBestiole() const override {
        return new T();
    }
};

#endif // BESTIOLECREATOR_H
