#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_

#include <array>
#include <iostream>
#include <vector>

#include "UImg.h"

class Capteur;  // Forward declaration

class Milieu;

class Comportement;

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

   private:
    int identite;
    int x, y;
    double cumulX, cumulY;
    double orientation;
    double vitesse;
    double vitesseInitiale;

    std::array<int, 3> couleur;

    double lifeTime;
    std::vector<std::unique_ptr<Capteur>> capteurs;

    // Accessoires
    double multiplicateurVitesse = 1.0;
    double multiplicateurProtection = 1.0;
    double multiplicateurDiscretion = 0.0;

   private:
    void bouge(int xLim, int yLim);

   public:                        // Forme canonique :
    Bestiole(void);               // Constructeur par defaut
    Bestiole(const Bestiole& b);  // Constructeur de copies
    virtual ~Bestiole();          // Destructeur

    Bestiole(Bestiole&& b);
    void action(Milieu& monMilieu);
    void draw(UImg& support);

    bool jeTeVois(const Bestiole& b) const;

    void initCoords(int xLim, int yLim);

    int getIdentite(void) const;
    void setVitesse(double vitesse);
    double getVitesse(void) const;
    void setOrientation(double orientation);
    double getOrientation(void) const;

    friend bool operator==(const Bestiole& b1, const Bestiole& b2);

    void setCouleur(int r, int g, int b);

    void setLifeExpectancy(double lifeExpectancy);
    double getLifeExpectancy(void) const;
    void setLifeExpectancyFromAvg(double averageLifeExpectancy, double std);

    void addCapteur(std::unique_ptr<Capteur> capteur);

    void percevoirEnvironnement() const;
    virtual void update(
        const std::vector<std::reference_wrapper<Bestiole>>&
            voisins) = 0;  // permet de traiter les bestioles voisines sans
                           // modifier l'ensemble original des bestioles TODO
                           // MAKE VIRTUAL

    double getX() const;
    double getY() const;

    void addCapteursFromString(const std::string& capteurs);

    virtual std::unique_ptr<Bestiole> clone() const = 0;

    double getVitesseInitiale() const;

    bool collidesWith(const Bestiole& other) const;

    void updateCollision();

    void setMultiplicateurVitesse(double multiplicateurVitesseNageoires,
                                  double multiplicateurVitesseCarapace);
    void setMultiplicateurProtection(double multiplicateurProtection);
    void setMultiplicateurDiscretion(double multiplicateurDiscretion);

    double getInitialMultipliedVitesse() const;
};

#endif
