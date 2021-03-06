/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    http://ericbeaudry.ca/INF3105/tp2/
*/
#include <math.h>
#include <assert.h>
#include "point.h"
#define RAYONTERRE 6371000  // en mètres
#define PI 3.14159265359

double Point::distance(const Point& point) const {
    double s1 = sin((point.latitude-latitude)/2);
    double s2 = sin((point.longitude-longitude)/2);
    return 2*RAYONTERRE * asin(sqrt(s1*s1 + cos(latitude)*cos(point.latitude)*s2*s2));
}

std::istream& operator >> (std::istream& is, Point& point) {
    char po, vir, pf;
    is >> po;
    if(is){
        is >> point.latitude >> vir >> point.longitude >> pf;
        assert(po=='(');
        assert(vir==',');
        assert(pf==')');
        point.longitude *= PI / 180.0;
        point.latitude  *= PI / 180.0;
    }
    return is;
}

std::ostream& operator << (std::ostream& os, const Point& point) {
    os << "(" 
       << (point.latitude * 180.0 / PI)
       << "," 
       << (point.longitude * 180.0 / PI)
       << ")";
    return os;
}
