
/*  INF3105 - Structures de données et algorithmes
 UQAM | Faculté des sciences | Département d'informatique
 Automne 2016 | TP2
 http://ericbeaudry.ca/INF3105/tp2/
 */
#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include "succ.h"
#include "point.h"

#include <map>
#include "date.h"

using namespace std;





int tp2(istream& entree){
    
    
    std::map<string, Succursale> succursales;
    
    int id=1;
    while(entree){
        std::string commande;
        entree >> commande >> ws;
        if(!entree) break;
        cout << id << " : ";
        
        if(commande=="creer"){
            string nom;
            Point p;
            int nbVoitures=0, nbPlacesLibres=0;
            entree >> nom >> p >> nbVoitures >> nbPlacesLibres;
            succursales[nom]  = Succursale(nom, p, nbVoitures, nbPlacesLibres);
            cout << "Creee"  << endl;
        }else if(commande=="reserver"){
            string origine, destination;
            Date debut, fin;
            entree >> origine >> debut >> destination >> fin;
            
            if( id == -32 ){
                succursales[origine].trace();
                succursales[destination].trace();
            }
            
            bool ok = Succursale::reserver(succursales[origine], succursales[destination], debut, fin);
            cout << (ok ? "Acceptee" : "NonDispo") << endl;
            
            if( id == -32 ){
                succursales[origine].trace();
                succursales[destination].trace();
            }


        
        }else if(commande=="suggerer"){
            Point origine, destination;
            Date debut, fin;
            entree >> origine >> debut >> destination >> fin;
            
            
            
            
            // CLASSER LES SUCCURSALES PAR DISTANCE
            map<double, Succursale> distancesOrigine;
            map<double, Succursale> distancesDestination;
            map<string, Succursale>::iterator itr = succursales.begin();
            while( itr != succursales.end()){
                double distanceOrigine = itr->second.position.distance(origine);
                distancesOrigine[distanceOrigine] = itr->second;
                double distanceDestination = itr->second.position.distance(destination);
                distancesDestination[distanceDestination] = itr->second;
                ++itr;
            }
            
            // TROUVER UNE SUCCURSALE DE DÉPART
            string depart("");
            map<double, Succursale>::iterator itr2 = distancesOrigine.begin();
            while( itr2 != distancesOrigine.end() ){
                if( itr2->second.accepteSortie(debut)){
                    depart = itr2->second.nom;
                    break;
                }
                ++itr2;
            }

            // TROUVER UNE SUCCURSALE D'ARRIVER
            string arrivee("");
            map<double, Succursale>::iterator itr3 = distancesDestination.begin();
            while( itr3 != distancesDestination.end() ){
                if( itr3->second.accepteEntree(debut)){
                    arrivee = itr3->second.nom;
                    break;
                }
                ++itr3;
            }

            
            
            if( arrivee == "" && depart == "" ){
                cout << "Impossible" << endl;
                continue;
            }
            
            cout << depart << " " <<  arrivee  << endl;
            
        }else{
            cout << "Commande '" << commande << "' invalide!" << endl;
            return 2;
        }
        char pointvigule=0;
        entree >> pointvigule >> ws;
        if(pointvigule!=';'){
            cout << "Fichier d'entrée invalide!" << endl;
            return 3;
        }
        id++;
    }
    return 0;
}
// syntaxe d'appel : ./tp2 [nomfichier.txt]
int main(int argc, const char** argv){
    // Gestion de l'entrée :
    //  - lecture depuis un fichier si un argument est spécifié;
    //  - sinon, lecture depuis std::cin.
    if(argc>1){
        std::ifstream entree_fichier(argv[1]);
        if(entree_fichier.fail()){
            std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
            return 1;
        }
        return tp2(entree_fichier);
    }else
        return tp2(std::cin);
    
    return 0;
}

