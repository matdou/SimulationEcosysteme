#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Comportement.h"
#include "BestioleFactory.h"

#include <iostream>

using namespace std;


int main()
{

   Aquarium       aquarium( 640, 480, 30 );
   BestioleFactory* factory = BestioleFactory::getInstance();

   for ( int i = 1; i <= 20; ++i ){
      Bestiole* peureuse = factory->createBestiole("Peureuse");
      Bestiole* kamikaze = factory->createBestiole("Kamikaze");
      Bestiole* gregaire = factory->createBestiole("Gregaire");
      aquarium.getMilieu().addMember(*peureuse);
      aquarium.getMilieu().addMember(*kamikaze);
      aquarium.getMilieu().addMember(*gregaire);


      // TODO : Milieu is storing a copy of the Bestiole, WARNING
   }
   aquarium.run();


   return 0;

}
