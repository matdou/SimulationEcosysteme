#ifndef BESTIOLEFACTORY_H
#define BESTIOLEFACTORY_H

#include "Bestiole.h"

// Factory pattern and Singleton pattern
class BestioleFactory {
private:
    static BestioleFactory* instance;
    BestioleFactory() {} // Constructeur privé

public:
    static BestioleFactory* getInstance();
    Bestiole* createBestiole(const std::string& type);

    BestioleFactory(const BestioleFactory&) = delete;
    BestioleFactory& operator=(const BestioleFactory&) = delete;
};  


#endif // BESTIOLEFACTORY_H