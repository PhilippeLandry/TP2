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
#include "arbremap.h"
#include "date.h"
#include "tableau.h"

using namespace std;
#include "testdate.cpp"




int tp2(istream& entree){
    
    
    ArbreMap<string, Succursale> succursales;
    
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
            bool ok = Succursale::reserver(succursales[origine], succursales[destination], debut, fin);
            cout << (ok ? "Acceptee" : "NonDispo") << endl;

        
        }else if(commande=="suggerer"){
            Point origine, destination;
            Date debut, fin;
            entree >> origine >> debut >> destination >> fin;
            bool ok = false;
            
            
            // À compléter...
            
            // cout << "A heure1 B heure2" << endl;
            cout << "Impossible" << endl;
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

