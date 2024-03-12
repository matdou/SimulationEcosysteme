#ifndef BESTIOLEFACTORY_H
#define BESTIOLEFACTORY_H

#include <functional>
#include <map>
#include <string>

#include "Bestiole.h"

class BestioleFactory {
   public:
    static void registerType(const std::string& typeName,
                             std::function<Bestiole*()> creator);
    static Bestiole* createBestiole(const std::string& typeName);

   private:
    static std::map<std::string, std::function<Bestiole*()>>& getFactoryMap();
};

#endif  // BESTIOLEFACTORY_H
