/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#if !defined(__DATE_H__)
#define __DATE_H__

#include <iostream>

class Date{
  public:

	Date();
	Date(int annee, int mois, int jour);
    bool operator <(const Date& date) const;
    Date& operator = (const Date& autre);

  private:
  	int annee;
  	int mois;
  	int jour;
    
  friend std::ostream& operator << (std::ostream&, const Date& date);
  friend std::istream& operator >> (std::istream&, Date& date);
};

#endif
