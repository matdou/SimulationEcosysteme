#ifndef _NAGEOIRE_H_
#define _NAGEOIRE_H_

#include "Accessoire.h"

class Nageoire :public Accessoire {
private:
	static const double MULT_MAX;

private:
	double mult;

public:
	Nageoire();
    bool isNageoire();
    bool isCarapace();
    bool isCamouflage();
	double getMultplicateur();
};

#endif