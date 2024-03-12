#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"
#include "Peureux.h"


#include <iostream>

using namespace std;


int main()
{

   Aquarium       aquarium( 640, 480, 30 );

   for ( int i = 1; i <= 20; ++i ){
      Bestiole* peureux = BestioleFactory::createBestiole<Peureux>();
      aquarium.getMilieu().addMember(*peureux);


      // TODO : Milieu is storing a copy of the Bestiole, WARNING
   }
   aquarium.run();


   return 0;

}
