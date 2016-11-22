/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    Auteur(s): 
*/
#if !defined(__SUCC_H__)
#define __SUCC_H__
#include <string>
#include "arbreavl.h"
#include "arbremap.h"
#include "date.h"
#include "point.h"
using namespace std;

class Succursale{
  public:
    Succursale();
    Succursale( string nom, Point position, int nbvoitures, int nbplaceslibres);
    string nom;
    static bool reserver( Succursale& origine, Succursale& destination, const Date& debut, const Date& fin );

    
    
 
  private:
    
    Point position;
    int nbPlaces; // nbvoitures + nbplaceslibres
    ArbreMap<Date, int> planning;
    
    bool accepteSortie( const Date& date );
    bool accepteEntree( const Date& date );
    void entrer( const Date& date );
    void sortir( const Date& date );
    

};



#endif

