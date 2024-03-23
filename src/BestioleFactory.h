#ifndef BESTIOLEFACTORY_H
#define BESTIOLEFACTORY_H

#include <functional>
#include <map>
#include <string>
#include "Bestiole.h"

/**
 * The BestioleFactory class is responsible for the creation of Bestiole objects.
 * It uses a registry pattern to associate string type names with creator functions.
 * This allows for the dynamic creation of Bestiole instances based on type names,
 * facilitating the addition of new Bestiole types without modifying the factory.
 */
class BestioleFactory {
public:
    /**
     * Registers a new Bestiole type and its associated creator function.
     * @param typeName The name of the Bestiole type.
     * @param creator A function pointer to the creator function for the Bestiole type.
     */
    static void registerType(const std::string& typeName, std::function<Bestiole*()> creator);

    /**
     * Creates a Bestiole instance based on the provided type name.
     * @param typeName The name of the Bestiole type to create.
     * @return A pointer to the created Bestiole instance.
     */
    static Bestiole* createBestiole(const std::string& typeName);

private:
    /**
     * Provides access to the internal map associating type names with creator functions.
     * @return A reference to the factory map.
     */
    static std::map<std::string, std::function<Bestiole*()>>& getFactoryMap();
};

#endif  // BESTIOLEFACTORY_H
