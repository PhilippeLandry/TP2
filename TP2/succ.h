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
    
    // RÉSERVER UN VÉHICULE D'UNE SUCCURSALE À L'AUTRE SUR UN INTERVALLE DE TEMPS
    static bool reserver( Succursale& origine, Succursale& destination, const Date& debut, const Date& fin );
    

    // ACCEPTE LA SORTIE D'UN VÉHICULE SUR UN INTERVALLE DE TEMPS OUVERT OU NON
    bool accepteSortie( const Date& date , const Date& retour = Date() );
    
    // ACCEPTE LE RETOUR D'UN VÉHICULE SUR UN INTERVALLE DE TEMPS OUVERT OU NON
    bool accepteEntree( const Date& date , const Date& retour = Date() );
    
    
    // ACCESSEURS
    
    const string& getNom() const;
    const Point& getPosition() const;
    
  private:
    
    
    
    int nbPlaces; // nbvoitures + nbplaceslibres
    ArbreMap<Date, int> planning;
    void entrer( const Date& date );
    void sortir( const Date& date );
    string nom;
    Point position;
    void trace();
    

};



#endif

