/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP2
    http://ericbeaudry.ca/INF3105/tp2/
*/
#if !defined(__DATE__H__)
#define __DATE__H__
#include <iostream>

// À compléter.
class Date{
  public:
    Date();
    Date( const Date& );
    bool operator <(const Date& date) const;
    bool operator <=(const Date& date) const;
    bool operator ==(const Date& date) const;
    
    int jours() const;
    int heures() const;
    int minutes() const;
  private:
    
    time_t time;
    
  friend std::ostream& operator << (std::ostream&, const Date& date);
  friend std::istream& operator >> (std::istream&, Date& date);
};

#endif

