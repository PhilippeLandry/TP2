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
    
    std::map<Date, int>::iterator itr = planning.lower_bound(date);
    if( itr == planning.end()){
        if( planning.begin()->second - 1 < 0 ){
            return false;
        }
    }
    while (itr != planning.end()) {
        
        int valeur = itr->second;
        if( valeur - 1 < 0 ){
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
    map<Date,int>::iterator itr = planning.begin();
    for( ; itr != planning.end(); itr++){
        cout << "   " << itr->first << " " << itr->second <<  "/" << nbPlaces <<endl;
    }
}
bool
Succursale::accepteEntree( const Date& date )  {
    if( nom == "C"){
        
    }

    std::map<Date, int>::iterator  itr = planning.lower_bound(date);
    if( itr == planning.end()){
        if( planning.begin()->second + 1 > nbPlaces ){
            return false;
        }
    }

    while (itr != planning.end()) {
        int valeur = itr->second;
        if( valeur + 1 > nbPlaces){
            return false;
        }
        ++itr;
    }
    return true;
}

void
Succursale::entrer( const Date& date ){
    

    std::map<Date, int>::iterator  itr = planning.lower_bound(date);
    int valeur = itr->second;
    planning[date] = valeur + 1;
     while (itr != planning.end()) {
         int valeur = itr->second;
         itr->second = valeur + 1;
         ++itr;
         
     }
    
    
}

void
Succursale::sortir( const Date& date ){
    std::map<Date, int>::iterator  itr = planning.lower_bound(date);
    int valeur = itr->second;
    planning[date] = valeur - 1;
    while (itr != planning.end()) {
        int valeur = itr->second;
        itr->second = valeur - 1;
        ++itr;
    }
}


bool
Succursale::reserver( Succursale& origine, Succursale& destination,const Date& debut, const Date& fin){
    
    //cout << "origine:" << origine.nom << " destination:" << destination.nom << " debut: " << debut << " fin:" << fin << endl;

    
    
    bool resultat =  origine.accepteSortie( Date(debut));
    if( resultat && origine.nom != destination.nom ){
            resultat &= destination.accepteEntree(fin);
    }
    if( resultat ){
        origine.sortir(debut);
        destination.entrer(fin);
    }
    

    
    return resultat;
}
