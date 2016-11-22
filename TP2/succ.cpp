/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    Auteur(s): 
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
Succursale::accepteSortie( const Date& date ) {
    
    ArbreMap<Date, int>::Iterateur itr = planning.rechercherEgalOuPrecedent(date);
    while (itr != planning.fin()) {
        if( itr.valeur() - 1 < 0 ){
            return false;
        }
        ++itr;
    }
    return true;
}
bool
Succursale::accepteEntree( const Date& date )  {
    ArbreMap<Date, int>::Iterateur itr = planning.rechercherEgalOuPrecedent(date);
    while (itr != planning.fin()) {
        if( itr.valeur() + 1 > nbPlaces){
            return false;
        }
        ++itr;
    }
    return true;
}

void
Succursale::entrer( const Date& date ){
    ArbreMap<Date, int>::Iterateur itr = planning.rechercherEgalOuPrecedent(date);
    if( !(itr.cle() == date) ){
        planning[date] = itr.valeur();
        ++itr;
    }
     while (itr != planning.fin()) {
         itr.valeur()++;
         ++itr;
     }
}

void
Succursale::sortir( const Date& date ){
    ArbreMap<Date, int>::Iterateur itr = planning.rechercherEgalOuPrecedent(date);
    if( !(itr.cle() == date) ){
        planning[date] = itr.valeur();
        ++itr;
    }
    while (itr != planning.fin()) {
        itr.valeur()--;
        ++itr;
    }
}


bool
Succursale::reserver( Succursale& origine, Succursale& destination,const Date& debut, const Date& fin){
    //cout << "origine:" << origine.nom << " destination:" << destination.nom << " debut: " << debut << " fin:" << fin << endl;
    bool resultat =  origine.accepteSortie( Date(debut)) && destination.accepteEntree(fin);
    if( resultat ){
        origine.sortir(debut);
        destination.entrer(fin);
    }
    
    return resultat;
}
