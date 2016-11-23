/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    http://ericbeaudry.ca/INF3105/tp2/
 *  AUTEUR(S): PHILIPPE LANDRY LANP28096606
*/
#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>
using namespace std;

#define SECONDES_PAR_MINUTE 60
#define SECONDES_PAR_HEURE 3600
#define SECONDES_PAR_JOUR 86400
#define MINUTES_PAR_HEURE 60

Date::Date() : time(0)
{

}

Date::Date( const Date& date)
{
    this->time = date.time;
}

bool
Date::operator <(const Date& d) const{
    
    return time < d.time;
}

bool
Date::operator <=(const Date& d) const{
    return time <= d.time;
}

bool
Date::operator ==(const Date& d) const{
    return time == d.time;
}

int
Date::jours() const {
        return (int) time / SECONDES_PAR_JOUR;
}

int
Date::heures() const {
    return (int)  (time / SECONDES_PAR_HEURE) % 24;
}

int
Date::minutes() const {
    return (int)(time / SECONDES_PAR_MINUTE) % SECONDES_PAR_MINUTE;
}

std::ostream& operator << (std::ostream& os, const Date& d){
    

    char chaine[40];
    sprintf(chaine, "%dj_%02dh%02dm", d.jours(), d.heures(), d.minutes());
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    
    char j, m, h, underscore;
    int jours , minutes, heures;
    is >> jours >> j >> underscore >> heures >> h >> minutes >> m;
    assert(j=='j');
    assert(underscore=='_');
    assert(h=='h' && m=='m');

    d.time = jours * SECONDES_PAR_JOUR + heures * SECONDES_PAR_HEURE + minutes * SECONDES_PAR_MINUTE;

    return is;
}

