#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_

#include <iostream>
#include <vector>

#include "UImg.h"

using namespace std;

class Milieu;

class Comportement;

class Bestiole {
   private:
    static const double AFF_SIZE;
    static const double MAX_VITESSE;
    static const double LIMITE_VUE;

    static int next;

   private:
    int identite;
    int x, y;
    double cumulX, cumulY;
    double orientation;
    double vitesse;

    std::array<int, 3> couleur;

    double lifeTime;

   private:
    void bouge(int xLim, int yLim);

   public:                        // Forme canonique :
    Bestiole(void);               // Constructeur par defaut
    Bestiole(const Bestiole& b);  // Constructeur de copies
    ~Bestiole(void);              // Destructeur
                                  // Operateur d'affectation binaire par defaut
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

    void setLifeExpectancyFromAvg(double averageLifeExpectancy);

};

#endif
