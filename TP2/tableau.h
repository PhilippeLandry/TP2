/*  INF3105 | Structures de données et algorithmes
 *  UQAM | Département d'informatique
 *  Automne 2016 | TP1
 *  http://ericbeaudry.ca/INF3105/
 *  AUTEUR(S): PHILIPPE LANDRY LANP28096606
 */
#if !defined(__TABLEAU__H__)
#define __TABLEAU__H__
#include <assert.h>
#include <iostream>


template <class T>
class Tableau
{
public:
    Tableau(int capacite_initiale=4);
    Tableau(const Tableau&);
    ~Tableau();
    
    // Ajouter un element à la fin
    void           ajouter(const T& element);
    
    
    // Vider le tableau
    void           vider();
    // Retourne le nombre d'éléments dans le tableau
    int            taille() const;
    
    // Insère element à position index. Les éléments à partir de index sont décalés d'une position au préalable.
    void           inserer(const T& element, int index=0);
    // Enlève l'element à position index. Les éléments après index sont décalés d'une position après.
    void           enlever(int index=0);
    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    // Voir la méthode "trouver" dans les notes de cours. Il suffit de l'adapter pour retourner la position au lieu d'un booléen
    int            trouver(const T& element);
    
    const T&       operator[] (int index) const;
    T&             operator[] (int index);
    
    bool           operator == (const Tableau<T>& autre) const;
    Tableau<T>&    operator = (const Tableau<T>& autre);
    
    // Imprimer le tableau sur stdout
    void montrer();
    
private:
    void redimensionner(int nouvCapacite);
    T*             elements;
    int            nbElements;
    int            capacite;
};

template <class T>
Tableau<T>::Tableau(int capacite)
{
    this->capacite = capacite;
    nbElements = 0;
    elements = new T[capacite];
    
}

template <class T>
Tableau<T>::Tableau(const Tableau& autre)
{
    
    nbElements = autre.nbElements;
    
    if(capacite<autre.nbElements){
        delete[] elements;
        capacite = autre.nbElements; //ou autre.capacite
        elements = new T[capacite];
    }
    for(int i=0;i<nbElements;i++)
        elements[i] = autre.elements[i];
    
}

template <class T>
Tableau<T>::~Tableau()
{
    delete[] elements;
    
}

template <class T>
int Tableau<T>::taille() const
{
    
    return nbElements;
}

template <class T>
void Tableau<T>::ajouter(const T& item )
{
    
    if(nbElements >= capacite) redimensionner(capacite * 2);
    elements[nbElements++] = item;
}

template <class T>
void Tableau<T>::redimensionner(int nouvCapacite) {
    capacite = nouvCapacite;
    T* temp = new T[capacite];
    for(int i=0;i<nbElements;i++)
        temp[i] = elements[i];
    delete [] elements;
    elements = temp;
}

template <class T>
void Tableau<T>::inserer(const T& element, int index)
{
    // redimensionner
    nbElements++;
    if(nbElements >= capacite) redimensionner(capacite * 2);
    for( int i = nbElements - 1 ; i > index; i--){
        elements[i] = elements[i-1];
    }
    elements[index] = element;
}

template <class T>
void Tableau<T>::enlever(int index)
{
    for( int i = index; i < nbElements; i++){
        elements[i] = elements[i+1];
    }
    nbElements--;
}

template <class T>
int Tableau<T>::trouver(const T& element)
{
    for( int i = 0 ; i < nbElements; i++){
        if( element == elements[i]){
            return i;
        }
    }
    return -1;
}

template <class T>
void Tableau<T>::vider()
{
    nbElements = 0;
    delete[] elements;
    elements = new T[capacite];
    
}

template <class T>
const T& Tableau<T>::operator[] (int index) const
{
    assert(index<nbElements);
    return elements[index];
}

template <class T>
T& Tableau<T>::operator[] (int index)
{
    assert(index<nbElements);
    return elements[index];
}

template <class T>
Tableau<T>& Tableau<T>::operator = (const Tableau<T>& autre)
{
    if(this==&autre)
        return *this;//cas special lorsqu’on affecte un objet a lui−meme
    
    nbElements = autre.nbElements;
    
    if(capacite<autre.nbElements){
        delete[] elements;
        capacite = autre.nbElements; //ou autre.capacite
        elements = new T[capacite];
    }
    for(int i=0;i<nbElements;i++)
        elements[i] = autre.elements[i];
    
    return *this;
}



template <class T>
bool Tableau<T>::operator == (const Tableau<T>& autre) const
{
    if( nbElements != autre.nbElements){ return false; }
    for( int i = 0 ; i < nbElements; i++ ){
        if( this->elements[i] != autre.elements[i]){
            return false;
        }
    }
    return true;
}
template <class T>
void
Tableau<T>::montrer() {
    for( int i = 0 ; i < nbElements; i++ ){
        
        std::cout << elements[i] << " " ;
        
    }
    std::cout << std::endl;
}
#endif
