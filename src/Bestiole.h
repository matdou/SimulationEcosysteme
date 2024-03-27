#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_

#include <array>
#include <iostream>
#include <vector>
#include <memory> // For std::unique_ptr
#include "UImg.h"

class Capteur; // Forward declaration
class Milieu; // Forward declaration

/**
 * Base class representing a creature in the environment. 
 * It includes basic attributes like position, speed, and orientation, 
 * and functionalities like moving and perceiving other creatures.
 */
class Bestiole {
private:
    static const double AFF_SIZE;
    static const double MAX_VITESSE;
    static const double LIMITE_VUE;
    static const double COLLISION_DISTANCE;
    static const double EXPLOSION_PROBABILITY;

    static const double MAX_MULT_VITESSE;
    static const double MAX_MULT_SLOWNESS;
    static const double MAX_MULT_PROTECTION;
    static const double MAX_MULT_DISCRETION;
    static const double MIN_MULT_DISCRETION;

    static int next;

    int identite;
    int x, y;
    double cumulX, cumulY;
    double orientation;
    double vitesse;
    double vitesseInitiale;

    std::array<int, 3> couleur;

    double lifeTime;
    std::vector<std::unique_ptr<Capteur>> capteurs;

    double multiplicateurVitesse = 1.0;
    double multiplicateurProtection = 1.0;
    double multiplicateurDiscretion = 0.0;

    /** Moves the creature within the given limits. */
    void bouge(int xLim, int yLim);

    // Milieu::timeSim when the creature was last collided with
    int lastCollisionTime = 0;

public:
    // Constructors & Destructor
    Bestiole();
    Bestiole(const Bestiole& b);
    Bestiole(Bestiole&& b);
    virtual ~Bestiole();

    /** Checks for equality based on identity. */
    friend bool operator==(const Bestiole& b1, const Bestiole& b2);

    /** Creates a copy of this creature. */
    virtual std::unique_ptr<Bestiole> clone() const = 0;

    /** Performs actions such as moving. */
    void action(Milieu& monMilieu);
    
    /** Draws the creature on the given canvas. */
    void draw(UImg& support);

    /** Checks if this creature can see another creature. */
    bool jeTeVois(const Bestiole& b) const;
    
    /** Initializes the coordinates of the creature. */
    void initCoords(int xLim, int yLim);

    /** Set the coordinates of the creature. */
    void setCoords(int x, int y);

    /** Returns the identity of the creature. */
    int getIdentite() const;

    /** Sets the speed of the creature. */
    void setVitesse(double vitesse);
    /** Returns the speed of the creature. */
    double getVitesse() const;
    /** Returns the initial speed of the creature. */
    double getVitesseInitiale() const;
    /** Returns the initial multiplied speed of the creature. */
    double getInitialMultipliedVitesse() const;

    /** Sets the orientation of the creature. */
    void setOrientation(double orientation);
    /** Returns the orientation of the creature. */
    double getOrientation() const;

    /** Sets the color of the creature. */
    void setCouleur(int r, int g, int b);
    /** Returns the color of the creature. */
    std::array<int, 3> getCouleur() const;

    /** Sets the life expectancy of the creature. */
    void setLifeExpectancy(double lifeExpectancy);
    /** Returns the life expectancy of the creature. */
    double getLifeExpectancy() const;

    /** Sets the life expectancy of the creature from average and standard deviation. */
    void setLifeExpectancyFromAvg(double averageLifeExpectancy, double std);

    /** Sets the last collision time of the creature. */
    void setLastCollisionTime(int time) { lastCollisionTime = time; };
    /** Returns the last collision time of the creature. */
    int getLastCollisionTime() const { return lastCollisionTime; };

    /** Adds a sensor to the creature. */
    void addCapteur(std::unique_ptr<Capteur> capteur);
    /** Adds sensors to the creature based on a string description. */
    void addCapteursFromString(const std::string& capteurs);

    /** Perceives the environment around the creature. */
    void percevoirEnvironnement() const;
    /** Updates the creature's behavior based on nearby creatures. */
    virtual void update(const std::vector<std::reference_wrapper<Bestiole>>& voisins) = 0;

    /** Checks if this creature collides with another creature. */
    bool collidesWith(const Bestiole& other) const;
    /** Updates the creature upon collision. */
    void updateCollision();

    /** Returns the X coordinate of the creature. */
    double getX() const;
    int getXInt() const;
    /** Returns the Y coordinate of the creature. */
    double getY() const;
    int getYInt() const;

    /** Sets speed multipliers of the creature. */
    void setMultiplicateurVitesse(double multiplicateurVitesseNageoires, double multiplicateurVitesseCarapace);
    /** Sets the protection multiplier of the creature. */
    void setMultiplicateurProtection(double multiplicateurProtection);
    /* Sets the discretion multiplier of the creature. */
    void setMultiplicateurDiscretion(double multiplicateurDiscretion);
    /** Increments the last collision time of the creature. **/
    void IncrementLastCollisionTime() { lastCollisionTime++; };

    /** Virtual Method redefined only in ComportementMultiple, to be called by LifeCycleManager */
    virtual void updateComportementForComportementMultiple() {};
};

#endif // BESTIOLES_H
