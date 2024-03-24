#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include "CImgWrapper.h"
#include <iostream>

// using namespace std;
// using namespace cimg_library;

class Milieu;

class Aquarium : public cimg_library::CImgDisplay {
private:
    Milieu* flotte;
    int delay;

public:
    // Constructor & Destructor
    Aquarium(int width, int height, int _delay);
    ~Aquarium(void);

    // Accessor
    Milieu& getMilieu(void);

    void run(void);
};

#endif // _AQUARIUM_H_
