#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"
#include "Peureux.h"


#include <iostream>


using namespace std;



int main()
{
   //BestioleFactory::registerType("Peureux", []() -> Bestiole* { return new Peureux(); });
   
   Aquarium aquarium( 640, 480, 30 );

   for ( int i = 1; i <= 1; ++i ){
      
      Bestiole* peureux = BestioleFactory::createBestiole("Peureux");
   if (peureux != nullptr) {
      aquarium.getMilieu().addMember(*peureux);
   } else {
      std::cerr << "Error: Failed to create a Bestiole of type 'Peureux'." << std::endl;
   }
      
      // aquarium.getMilieu().addMember(*peureux);


      // TODO : Milieu is storing a copy of the Bestiole, WARNING
   }
   aquarium.run();


   return 0;

}
