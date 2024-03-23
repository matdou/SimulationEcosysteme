#include "PopulationConfig.h"

#include "Oreilles.h"
#include "Yeux.h"

PopulationConfig::PopulationConfig() {
    birthRate = 0.0;
    deathRate = 0.0;
    avgLifeTime = -1;
    lifeTimeStd = 0.5;
    currentTypeCount = 0;
    nageoiresSpeedFactor = 1.0;
    carapaceResistanceFactor = 1.0;
    carapaceSlownessFactor = 1.0;
    camouflageFactor = 1.0;
}

PopulationConfig::PopulationConfig(const PopulationConfig& other) {
    typeCounts = other.typeCounts;
    birthRate = other.birthRate;
    deathRate = other.deathRate;
    cloningRate = other.cloningRate;
    avgLifeTime = other.avgLifeTime;
    lifeTimeStd = other.lifeTimeStd;
    currentTypeCount = other.currentTypeCount;
    currentTypeName = other.currentTypeName;
    nageoiresSpeedFactor = other.nageoiresSpeedFactor;
    carapaceResistanceFactor = other.carapaceResistanceFactor;
    carapaceSlownessFactor = other.carapaceSlownessFactor;
    camouflageFactor = other.camouflageFactor;

    for (const auto& capteur : other.capteurs) {
        auto clonedCapteur = capteur->clone();
        if (!clonedCapteur) {
            std::cerr << "Failed to clone capteur\n";
        } else {
            capteurs.push_back(std::move(clonedCapteur));
            std::cout << "PopulationConfig : Cloned capteur\n";

        }
    }
}

PopulationConfig& PopulationConfig::operator=(const PopulationConfig& other) {
    if (this != &other) {
        typeCounts = other.typeCounts;
        birthRate = other.birthRate;
        deathRate = other.deathRate;
        cloningRate = other.cloningRate;
        avgLifeTime = other.avgLifeTime;
        lifeTimeStd = other.lifeTimeStd;
        currentTypeCount = other.currentTypeCount;
        currentTypeName = other.currentTypeName;
        nageoiresSpeedFactor = other.nageoiresSpeedFactor;
        carapaceResistanceFactor = other.carapaceResistanceFactor;
        carapaceSlownessFactor = other.carapaceSlownessFactor;
        camouflageFactor = other.camouflageFactor;

        capteurs.clear();
        for (const auto& capteur : other.capteurs) {
            capteurs.push_back(capteur->clone());
        }
    }
    return *this;
}

void PopulationConfig::addTypeCount(const std::string& typeName, int count) {
    typeCounts[typeName] = count;
    if (typeCounts.size() == 1) {
        setCurrentType(typeName);
    }
}

void PopulationConfig::removeTypeCount(const std::string& typeName) {
    typeCounts.erase(typeName);
    if (currentTypeName == typeName) {
        if (!typeCounts.empty()) {
            setCurrentType(typeCounts.begin()->first);
        } else {
            resetCurrentType();
        }
    }
}

void PopulationConfig::setCurrentType(const std::string& typeName) {
    currentTypeName = typeName;
    currentTypeCount = 0;  // Always reset count when setting a new type
}

void PopulationConfig::resetCurrentType() {
    currentTypeName = "";
    currentTypeCount = 0;
}

std::string PopulationConfig::getNextBirthType() {
    if (typeCounts.empty()) {
        return "";  // Return an empty string if no types are configured
    }

    if (++currentTypeCount >= typeCounts[currentTypeName]) {
        auto it = typeCounts.find(currentTypeName);
        if (++it == typeCounts.end()) {
            it = typeCounts.begin();
        }
        setCurrentType(it->first);
    }

    return currentTypeName;
}

int PopulationConfig::getTotalPopulationSize() const {
    int total = 0;
    for (const auto& pair : typeCounts) {
        total += pair.second;
    }
    return total;
}

void PopulationConfig::addYeux(double champVision, double distanceVision,
                               double capaciteDetection) {
    std::unique_ptr<Capteur> capteur =
        std::make_unique<Yeux>(champVision, distanceVision, capaciteDetection);
    if (!capteur) {
        std::cout << "PopulationConfig : Null pointer in capteurs" << std::endl;
    }
    capteurs.push_back(std::move(capteur));
}

void PopulationConfig::addOreilles(double distanceAudible,
                                   double capaciteDetection) {
    std::unique_ptr<Capteur> capteur =
        std::make_unique<Oreilles>(distanceAudible, capaciteDetection);
    capteurs.push_back(std::move(capteur));
}

void PopulationConfig::addNageoires(double speedFactor) {
    PopulationConfig::nageoiresSpeedFactor = speedFactor;
}

void PopulationConfig::addCarapace(double resistanceFactor,
                                   double slownessFactor) {
    carapaceResistanceFactor = resistanceFactor;
    carapaceSlownessFactor = slownessFactor;
}

void PopulationConfig::addCamouflage(double factor) {
    camouflageFactor = factor;
}


void PopulationConfig::setTotalCount(int count) {
    int total = getTotalPopulationSize();
    if (total == 0) {
        return;
    }

    double factor = static_cast<double>(count) / total;
    for (auto& pair : typeCounts) {
        pair.second = static_cast<int>(pair.second * factor);
    }
}
