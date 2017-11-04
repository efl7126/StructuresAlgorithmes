/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2017 | Lab8 + TP2
    http://ericbeaudry.uqam.ca/INF3105/lab8/
    http://ericbeaudry.uqam.ca/INF3105/tp2/

    AUTEUR(S):
     (1) Nom + Code permanent du l'étudiant.e 1
     (2) Nom + Code permanent du l'étudiant.e 2
*/
#if !defined(_ARBREMAP___H_)
#define _ARBREMAP___H_

#include "arbreavl.h"

template <class K, class V>
class ArbreMap
{
	private:
    // À compléter : voir la Section 8.11 (Arbres associatifs (Mapping Trees)) des notes de cours
	class Entree{
	
		public:
			Entree(const K& c): cle(c), valeur() {}
			K cle;
			V valeur;
			bool operator<(const Entree& e) const
			{
				return cle < e.cle;
			}
	};
	
 	ArbreAVL<Entree> entrees;
 	
    public:
		class Iterateur {
			public:
				Iterateur(ArbreMap& a) : iter(a.entrees.debut()) {}
				Iterateur(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {}
				
				operator bool() const {return iter.operator bool();};
				Iterateur& operator++() {++iter; return *this;}

				const K& cle() const 
				{
					return (*iter).cle;
				}
				V& valeur()  
				{
					return (V&) (*iter).valeur;
				}
			
			private:
				typename ArbreAVL<Entree>::Iterateur iter;
		};
		
	Iterateur debut() 
	{ 
		return Iterateur(*this); 
	}
	Iterateur fin() 
	{ 
		return Iterateur(entrees.fin());
	}
	Iterateur rechercher(const K& cle) 
	{ 
		return Iterateur(entrees.rechercher(cle));
	}
	Iterateur rechercherEgalOuSuivant(const K& cle) 
	{
		return Iterateur(entrees.rechercherEgalOuSuivant(cle));
	}
	Iterateur rechercherEgalOuPrecedent(const K& cle) 
	{
		return Iterateur(entrees.rechercherEgalOuPrecedent(cle));
	}

  public:
    bool contient(const K&) const;

    void enlever(const K&);
    void vider();
    bool vide() const;

    const V& operator[] (const K&) const;
    V& operator[] (const K&);
    
    void afficher() const;
};



template <class K, class V>
void ArbreMap<K,V>::vider(){
    // À compléter
    entrees.vider();
}

template <class K, class V>
bool ArbreMap<K,V>::vide() const{
    // À compléter
    return entrees.vide();
}

template <class K, class V>
void ArbreMap<K,V>::enlever(const K& c)
{
    // À compléter
}

template <class K, class V>
bool ArbreMap<K,V>::contient(const K& cle) const
{
    // À compléter
    
    Entree entree(cle);
    
    return entrees.contient(entree);
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& cle)  const
{
    // À compléter
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(cle);
    
    return entrees[iter].valeur;
}


// IMPORTANT
template <class K, class V>
V& ArbreMap<K,V>::operator[] (const K& cle) 
{
    // À compléter
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(cle);
    
    if(!iter) // Si l'element n'existe pas, on le cree
    {
    	entrees.inserer(Entree(cle));
    	iter = entrees.rechercher(cle);
    }
    
    return entrees[iter].valeur;
}

template <class K, class V>
void ArbreMap<K,V>::afficher() const {
    
    typename ArbreAVL<Entree>::Iterateur i = entrees.debut();  
    for(;i;++i)
    {
    	std::cout << (*i).valeur << std::endl;
    }
}


#endif

