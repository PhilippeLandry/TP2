/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    Auteur(s): PHILIPPE LANDRY LANP28096606 
*/
#include "succ.h"

Succursale::Succursale(){
    
}
Succursale::Succursale( string nom, Point position, int nbvoitures, int nbplaceslibres)
: nom(nom), position(position),nbPlaces(nbvoitures + nbplaceslibres)
{
    
    planning[ Date() ] = nbvoitures;
}


bool
Succursale::accepteSortie( const Date& date ,const Date& retour) {
    
    
    ArbreMap<Date, int>::Iterateur itr = planning.rechercherEgalOuPrecedent(date);
    int valeur = itr.valeur();
    if( valeur - 1 < 0 ){
        return false;
    }
    while (itr != planning.fin()) {
        if( itr.cle() <= date ){ ++itr; continue; }
        if( retour.time != 0 && itr.cle().time > retour.time ){ break; }
        if( itr.valeur() - 1 < 0 ){
            return false;
        }
        ++itr;
    }
    return true;
}

void
Succursale::trace() {
    
    cout << "====================" << endl;
    cout << "Succ: " << nom << endl;
    ArbreMap<Date, int>::Iterateur itr = planning.debut();
    for( ; itr != planning.fin(); ++itr){
        cout << "   " << itr.cle() << " " << itr.valeur() <<  "/" << nbPlaces <<endl;
    }
}
bool
Succursale::accepteEntree( const Date& date , const Date& retour)  {

    ArbreMap<Date, int>::Iterateur itr = planning.rechercherEgalOuPrecedent(date);
    int valeur = itr.valeur();
    if( valeur + 1 > nbPlaces ){
        return false;
    }
    while (itr != planning.fin()) {
        if( itr.cle() <= date ){ ++itr; continue; }
        if( retour.time != 0 && itr.cle().time > retour.time ){ break; }
        int valeur = itr.valeur();
        if( valeur + 1 > nbPlaces){
            return false;
        }
        ++itr;
    }
    return true;
}

void
Succursale::entrer( const Date& date ){
    
    
    ArbreMap<Date, int>::Iterateur  itr = planning.rechercherEgalOuPrecedent(date);
    int valeur = itr.valeur();
    
    itr = planning.debut();
     while (itr != planning.fin()) {
         
         if( itr.cle() <= date ){ ++itr; continue; }
         
         itr.valeur() = itr.valeur() + 1;
         ++itr;
         
     }
    planning[date] = valeur + 1;
    
    
}

void
Succursale::sortir( const Date& date ){

    ArbreMap<Date, int>::Iterateur  itr = planning.rechercherEgalOuPrecedent(date);
    
    
    
    int valeur = itr.valeur();
    itr = planning.debut();
    while (itr != planning.fin()) {
        if( itr.cle() <= date ){ ++itr; continue; }
        
        itr.valeur() = itr.valeur() - 1;
        ++itr;
    }
    planning[date] = valeur - 1;
}


bool
Succursale::reserver( Succursale& origine, Succursale& destination,const Date& debut, const Date& fin){
    
  // cout << "origine:" << origine.nom << " destination:" << destination.nom << " debut: " << debut << " fin:" << fin << endl;

    
    bool memeSuccursale = origine.nom == destination.nom;
    bool resultat =  origine.accepteSortie( debut , memeSuccursale ? fin : Date());
    if( resultat && origine.nom != destination.nom ){
            resultat &= destination.accepteEntree(fin);
    }
    if( resultat ){
        origine.sortir(debut);
        destination.entrer(fin);
    }
    

    
    return resultat;
}
