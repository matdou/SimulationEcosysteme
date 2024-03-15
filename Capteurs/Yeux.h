#ifndef _YEUX_H_
#define _YEUX_H_

#include <cstdlib>
#include <cmath>
#include "Capteur.h"

using namespace std;


class Yeux : public Capteur
{

private :

	static const double ALPHA_YE_MIN;
    static const double ALPHA_YE_MAX;
	static const double DELTA_YE_MAX;
	static const double DELTA_YE_MIN;
    static const double GAMMA_YE_MAX;
	static const double GAMMA_YE_MIN;
    double gamma;
	double delta;
    double alpha;

public :
	
	Yeux ();
	Yeux( const Yeux & y );
	bool isYeux();
	bool isOreilles();
    double getGamma() const;
	double getDelta() const;
    double getAlpha() const;
};

#endif