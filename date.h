/*  AUTEUR(S):
    1) Ndjerandouba Jules + NDJJ15047609
    2) François-Guillaume Landry + LANF06109305
*/

#if !defined(__DATE_H__)
#define __DATE_H__

#include <iostream>

class Date{
  public:

	Date();
	Date(int annee, int mois, int jour);
    bool operator <(const Date& date) const;
    bool operator <=(const Date& d) const;
    Date& operator = (const Date& autre);

  private:
  	int annee;
  	int mois;
  	int jour;
    
  friend std::ostream& operator << (std::ostream&, const Date& date);
  friend std::istream& operator >> (std::istream&, Date& date);
};

#endif
