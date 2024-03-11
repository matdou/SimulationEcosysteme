#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Comportement.h"

#include <iostream>

using namespace std;


int main()
{

   Aquarium       ecosysteme( 640, 480, 30 );

   for ( int i = 1; i <= 2; ++i ){
      Bestiole* nouvelleBestiole = new Bestiole();
      nouvelleBestiole->setComportement(new ComportementPeureux());
      nouvelleBestiole->appliquerComportement();
      ecosysteme.getMilieu().addMember(*nouvelleBestiole); // TODO : Milieu is storing a copy of the Bestiole, WARNING
   }
   ecosysteme.run();


   return 0;

}
