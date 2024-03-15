#ifndef _OREILLES_H_
#define _OREILLES_H_

#include <cstdlib>
#include <cmath>
#include "Capteur.h"

using namespace std;


class Oreilles : public Capteur
{

private :

	static const double GAMMA_OR_MAX;
	static const double GAMMA_OR_MIN;
	static const double DELTA_OR_MAX;
	static const double DELTA_OR_MIN;
    double gamma;
	double delta;

public :
	
	Oreilles ();
	Oreilles( const Oreilles & o );
	bool isYeux();
	bool isOreilles();
    double getGamma() const;
	double getDelta() const;
    bool isCapting(const Bestiole& bestiole, int x, int y, double orientation) override;
};

#endif