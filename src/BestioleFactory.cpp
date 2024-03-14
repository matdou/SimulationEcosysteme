#include "BestioleFactory.h"

// Private static method to access the factory map
std::map<std::string, std::function<Bestiole*()>>&
BestioleFactory::getFactoryMap() {
    // Local static variable instantiated on first use
    static std::map<std::string, std::function<Bestiole*()>> factoryMap;
    return factoryMap;
}

// Public static method to register a type with the factory
void BestioleFactory::registerType(const std::string& typeName,
                                   std::function<Bestiole*()> creator) {
    getFactoryMap()[typeName] = creator;
}

// Public static method to create a Bestiole instance based on type name
Bestiole* BestioleFactory::createBestiole(const std::string& typeName) {
    auto& factoryMap = getFactoryMap();  // Use getter to ensure initialization
    std::cout << "Creating Bestiole of type: " << typeName << std::endl;
    auto it = factoryMap.find(typeName);
    if (it != factoryMap.end()) {
        std::cout << "Found creator function for type: " << typeName
                  << std::endl;
        std::cout << "returning it->second()" << std::endl;
        return it->second();
    }
    std::cerr << "Error: No creator function found for type: " << typeName
              << std::endl;
    return nullptr;
}
