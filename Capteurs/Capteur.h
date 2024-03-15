#ifndef _CAPTEUR_H_
#define _CAPTEUR_H_

#include "Bestiole.h"

using namespace std;


class Capteur :
{

private :

public :
	
	bool isCapting(const Bestiole& bestiole, int x, int y, double orientation) = 0;

};

#endif