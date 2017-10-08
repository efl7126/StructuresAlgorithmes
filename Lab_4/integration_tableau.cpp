#include "tableau.h"
#include "pile.h"
#include <iostream>

using namespace std;

int main()
{
    Tableau<Pile<int> > tab1;
    for(int i=0;i<5;i++){
        Pile<int> pile;
        pile.empiler(-1);
        tab1.ajouter(pile);
        for(int j=0;j<i;j++)
        	tab1[i].empiler(j);
        	//tab1.afficher();
    }
    Tableau<Pile<int> >  tab2;
    tab2 = tab1;
    for(int i=0;i<5;i++)
    {
        tab1[i] = Pile<int>();
    }
      

    tab1.afficher();
	


}

