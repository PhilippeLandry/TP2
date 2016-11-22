/*  INF3105 | Structures de données et algorithmes
 *  UQAM | Département d'informatique | Automne 2016
 *  Arbre AVL pour Lab6 + TP2
 *  http://ericbeaudry.ca/INF3105/
 */
#if !defined(__ARBREAVL__H__)
#define __ARBREAVL__H__
#include <assert.h>
#include <stdio.h>
#include "pile.h"
#include "tableau.h"

using namespace std;
template <class T>
class ArbreAVL
{
public:
    //Constructeurs et destructeur.
    ArbreAVL();
    ArbreAVL(const ArbreAVL&);
    ~ArbreAVL();
    
    //Fonction pour manipuler l'arbre.
    bool contient(const T&) const;
    int  hauteur() const;
    void inserer(const T&);
    bool vide() const;
    void vider();
    void enlever(const T&); // non requis pour le TP2.
    void montrer();
    // Annonce l'existance d'une classe Iterateur.
    class Iterateur;
    
    // Fonction pour obtenir un itérateur (position dans l'arbre)
    Iterateur debut() const;
    Iterateur fin() const;
    Iterateur rechercher(const T&) const;
    Iterateur rechercherEgalOuSuivant(const T&) const;
    Iterateur rechercherEgalOuPrecedent(const T&) const;
    
    // Accès aux éléments de l'arbre via un intérateur.
    const T& operator[](const Iterateur&) const;
    T& operator[](const Iterateur&);
    
    // Copie d'un arbre AVL.
    ArbreAVL& operator = (const ArbreAVL&);
    bool operator==(const Iterateur&) const;
    
private:
    struct Noeud{
        Noeud(const T&);
        T contenu;
        int equilibre;
        Noeud *gauche;
        Noeud *droite;
    };
    Noeud* racine;
    
    // Fonctions internes.
    bool inserer(Noeud*&, const T&);
    void rotationGaucheDroite(Noeud*&);
    void rotationDroiteGauche(Noeud*&);
    void vider(Noeud*&);
    void copier(const Noeud*, Noeud*&) const;
    const T& max(Noeud*) const;
    bool enlever(Noeud*&, const T& e);
    void inordre(Noeud*& , Tableau<T>&, int depth);
    int hauteur(Noeud*) const;
    
public:

    class Iterateur{
    public:
        Iterateur(const ArbreAVL& a);
        Iterateur(const Iterateur& a);
        Iterateur(const ArbreAVL& a, Noeud* c);
        
        operator bool() const;
        bool operator!() const;
        bool operator==(const Iterateur&) const;
        bool operator!=(const Iterateur&) const;
        
        const T& operator*() const;
        
        Iterateur& operator++();
        Iterateur operator++(int);
        Iterateur& operator = (const Iterateur&);
    private:
        const ArbreAVL& arbre_associe;
        Noeud* courant;
        Pile<Noeud*> chemin;
        
        friend class ArbreAVL;
    };
};


//-----------------------------------------------------------------------------

template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c):
gauche(NULL), droite(NULL), equilibre(0), contenu(c)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL() : racine(NULL)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre) : racine(NULL)
{
    copier(autre.racine, racine);
}

template <class T>
ArbreAVL<T>::~ArbreAVL()
{
    vider(racine);
}

template <class T>
bool ArbreAVL<T>::contient(const T& element) const
{
    
    return rechercher(element) !=0 ;
}

template <class T>
void ArbreAVL<T>::inserer(const T& element)
{
    inserer(racine, element);
}

template <class T>
bool ArbreAVL<T>::inserer(Noeud*& noeud, const T& element)
{
    if(noeud==NULL)
    {
        noeud = new Noeud(element);
        return true;
    }
    if(element < noeud->contenu){
        if(inserer(noeud->gauche, element))
        {
            noeud->equilibre++;
            if(noeud->equilibre == 0) return false;
            if(noeud->equilibre == 1) return true;
            assert(noeud->equilibre==2);
            if(noeud->gauche->equilibre == -1){
                rotationDroiteGauche(noeud->gauche);
            }
            rotationGaucheDroite(noeud);
        }
        return false;
    }
    else if(noeud->contenu < element){
        if(inserer(noeud->droite, element))
        {
            noeud->equilibre--;
            if(noeud->equilibre == 0) return false;
            if(noeud->equilibre == -1) return true;
            assert(noeud->equilibre==-2);
            if(noeud->droite->equilibre == 1){
                rotationGaucheDroite(noeud->droite);
                
            }
            rotationDroiteGauche(noeud);
            
        }
        return false;
    }
    
    // element == noeud->contenu
    noeud->contenu = element;  // Mise à jour
    return false;
}

template <class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->gauche;
    int  ea = temp->equilibre;
    int  eb = racinesousarbre->equilibre;
    int  neb = -(ea>0 ? ea : 0) - 1 + eb;
    int  nea = ea + (neb < 0 ? neb : 0) - 1;
    
    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->gauche = temp->droite;
    temp->droite = racinesousarbre;
    racinesousarbre = temp;
}

template <class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->droite;
    int  eb = temp->equilibre;
    int  ea = racinesousarbre->equilibre;
    int  nea = -(eb>0 ? eb : 0) + 1 + ea;
    int  neb = (nea > 0 ? nea : 0) + 1 +eb;
    
    temp->equilibre = neb;
    racinesousarbre->equilibre = nea;
    racinesousarbre->droite = temp->gauche;
    temp->gauche = racinesousarbre;
    racinesousarbre = temp;
    
}

template <class T>
bool ArbreAVL<T>::vide() const
{
    // À compléter.
    return racine == NULL;
}

template <class T>
void ArbreAVL<T>::vider(){
    vider(racine);
}

template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud)
{
    if( noeud == NULL){ return; }
    vider(noeud->gauche);
    vider(noeud->droite);
    noeud = NULL;
    delete noeud;
}

template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const
{
    if( source == NULL ){
        return;
    }
    if( noeud == NULL){
        noeud = new Noeud( source->contenu );
    }
    noeud->contenu = source->contenu;
    noeud->equilibre = source->equilibre;
    copier( source->gauche , noeud->gauche );
    copier( source->droite, noeud->droite);
}

template <class T>
int  ArbreAVL<T>::hauteur() const{
    
    // À compléter.
    return hauteur( racine );
}
template <class T>
int ArbreAVL<T>::hauteur(Noeud* noeud) const {
    if(noeud==NULL) return 0;
    return std::max(hauteur(noeud->gauche), hauteur(noeud->droite))+1;
}

template <class T>
const T& ArbreAVL<T>::max(Noeud* n) const
{
    
}

//----------- L'enlèvement est optionnel (non requise pour le TP2) ----------//
template <class T>
void ArbreAVL<T>::enlever(const T& element)
{
    enlever(racine, element);
}

template <class T>
bool ArbreAVL<T>::enlever(Noeud*& noeud, const T& element)
{
    if(element < noeud->contenu)
    {
        if(enlever(noeud->gauche, element))
        {
            // ...
        }
    }
    else if(element > noeud->contenu)
    {
        // ...
    }
    else if(element == noeud->contenu)
    {
        if (noeud->gauche==NULL && noeud->droite==NULL)
        {
            delete noeud;
            noeud = NULL;
            return true;
        }
        else
        {
            // ...
            return true;
        }
    }
    return false;
}

//----------- L'enlèvement est optionnel (non requise pour le TP2) ----------//

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const
{
    Iterateur iter(*this);
    iter.courant = racine;
    if(iter.courant!=NULL){
        while(iter.courant->gauche!=NULL){
            iter.chemin.empiler(iter.courant);
            iter.courant = iter.courant->gauche;
        }
    }
    return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const
{
    return Iterateur(*this);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T& e) const
{
    
    Iterateur iter(*this);
    Noeud* n = racine;
    
    while(n){
        
        if(e < n->contenu){
            iter.chemin.empiler(n);
            n = n->gauche;
        }
        else if(n->contenu < e){
            iter.chemin.empiler(n);
            n = n->droite;
        }
        else{
            iter.courant = n;
            return iter;
        }
    }
    iter.chemin.vider();
    return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T& e) const
{
    Noeud* n = racine, *dernier=NULL;
    while(n){
        if(e < n->contenu){
            dernier = n;
            n = n->gauche;
        }
        else if(n->contenu < e){
            
            n = n->droite;
        }
        else{
            return rechercher(e);
        }
    }
    if(dernier!=NULL){
        return rechercher(dernier->contenu);
    }
    return Iterateur(*this);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T& e) const
{
    Noeud* n = racine, *dernier=NULL;
    while(n){
        if(e < n->contenu){
            n = n->gauche;
        }
        else if(n->contenu < e){
            dernier = n;
            n = n->droite;
        }
        else{
            return rechercher(e);
        }
    }
    if(dernier!=NULL){
        return rechercher(dernier->contenu);
    }
    return Iterateur(*this);
}

template <class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur)
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
    if(this==&autre) return *this;
    vider();
    copier(autre.racine, racine);
    return *this;
}

template <class T>
void ArbreAVL<T>::inordre( Noeud*& n , Tableau<T>& t, int depth){
    if( n == NULL ){
        return;
    }
    
    inordre( n->gauche ,t , depth + 1);
    
    for( int i = 0 ; i < depth; i++ ){
        cout << "-" ;
    }
    t.ajouter( n->contenu );
    
    cout << n->contenu << endl;;
    inordre( n->droite, t , depth + 1) ;
}
template <class T>
void ArbreAVL<T>::montrer(){
    Tableau<T> t;
    inordre(racine,t, 0);
    for( int i = 0 ; i < t.taille(); i++){
        
        //  cout << t[i] << endl;
    }
}


template <class T>
bool ArbreAVL<T>::operator==(const Iterateur& o) const{
    Iterateur itr1, itr2;
    itr1.debut();
    itr2.debut();
    while( itr1 && itr2 ){
        if( *itr1 != *itr2 ){
            return false;
        }
        itr1++; itr2++;
    }
    return !itr1 && !itr2;
}


//-----------------------
template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL& a)
: arbre_associe(a), courant(NULL)
{
}

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur& a)
: arbre_associe(a.arbre_associe)
{
    courant = a.courant;
    chemin = a.chemin;
}

// Pré-incrément
template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++()
{
    assert(courant);
    Noeud* suivant = courant->droite;
    while(suivant){
        chemin.empiler(suivant);
        suivant = suivant->gauche;
    }
    if(!chemin.vide())
        courant = chemin.depiler();
    else
        courant = NULL;
    return *this;
}

// Post-incrément
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int)
{
    Iterateur copie(*this);
    operator++();
    return copie;
}

template <class T>
ArbreAVL<T>::Iterateur::operator bool() const
{
    return courant!=NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!() const{
    return courant==NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant==o.courant;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant!=o.courant;
}

template <class T>
const T& ArbreAVL<T>::Iterateur::operator *() const
{
    assert(courant!=NULL);
    return courant->contenu;
}

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator = (const Iterateur& autre){
    assert(&arbre_associe==&autre.arbre_associe);
    courant = autre.courant;
    chemin = autre.chemin;
    return *this;
}

#endif


