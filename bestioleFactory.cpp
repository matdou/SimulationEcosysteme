#include "BestioleFactory.h"

// Private static method to access the factory map
std::map<std::string, std::function<Bestiole*()>>& BestioleFactory::getFactoryMap() {
    // Local static variable instantiated on first use
    static std::map<std::string, std::function<Bestiole*()>> factoryMap;
    return factoryMap;
}

// Public static method to register a type with the factory
void BestioleFactory::registerType(const std::string& typeName, std::function<Bestiole*()> creator) {
    getFactoryMap()[typeName] = creator;
}

// Public static method to create a Bestiole instance based on type name
Bestiole* BestioleFactory::createBestiole(const std::string& typeName) {
    auto& factoryMap = getFactoryMap(); // Use getter to ensure initialization
    auto it = factoryMap.find(typeName);
    if (it != factoryMap.end()) {
        return it->second();
    }
    return nullptr;
}
