#ifndef ICAPTEUR_H
#define ICAPTEUR_H

#include <memory>


class Bestiole; // Forward declaration
class Milieu; // Forward declaration

/**
 * Interface for sensors (Capteurs) that can be used by Bestioles to interact with their environment.
 */
class Capteur {
public:
     virtual ~Capteur() = default; // Virtual destructor

     /**
     * Determines if the sensor perceives a given Bestiole.
     * @param bestiole The Bestiole to be detected.
     * @param moi The Bestiole owning this sensor.
     * @return true if the bestiole is detected, false otherwise.
     */
     virtual bool jeTeVois(const Bestiole& bestiole, const Bestiole& moi) = 0;
     
     /**
     * Creates a deep copy of this sensor.
     * @return A unique_ptr to the cloned sensor.
     */
     virtual std::unique_ptr<Capteur> clone() const = 0; 
};

#endif  // ICAPTEUR_H