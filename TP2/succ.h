/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    Auteur(s): PHILIPPE LANDRY LANP28096606
 
*/
#if !defined(__SUCC_H__)
#define __SUCC_H__
#include <string>
#include "date.h"
#include "point.h"
#include "arbremap.h"
using namespace std;

class Succursale{
  public:
    Succursale();
    Succursale( string nom, Point position, int nbvoitures, int nbplaceslibres);
    string nom;
    static bool reserver( Succursale& origine, Succursale& destination, const Date& debut, const Date& fin );
    Point position;
    bool accepteSortie( const Date& date , const Date& retour = Date() );
    bool accepteEntree( const Date& date , const Date& retour = Date() );
    
    void trace();
 
  private:
    
    
    int nbPlaces; // nbvoitures + nbplaceslibres
    ArbreMap<Date, int> planning;
    
    void entrer( const Date& date );
    void sortir( const Date& date );
    

};



#endif

