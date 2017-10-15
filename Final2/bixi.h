/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  Automne 2017 / TP1                                   *
 *  http://ericbeaudry.uqam.ca/INF3105/tp1/              */

#if !defined(_BIXI__H_)
#define _BIXI__H_

#include <iostream>
#include <string>
#include "pointst.h"
#include "tableau.h"

using namespace std;

class Reseau;

// La classe Station encapsule toutes les propriétés d'une station BIXI
class Station{
  public:
    
    // Interface publique ici. ========================================
    
    Station();					// Constructeur par défaut
    Station(const Station&);	// Constructeur par copie
    
  private:
    // Représentation ici. ============================================
    
	// Attributs de Station (enregistrés à partir du fichier texte de stations)
    int id;
    string nomStation;
    PointST coordonnee;
    int nbVelosDisponibles;
    int nbPointsAncrage;
	
	// Attributs de Station (ajoutés)
	int indice;				// Indice de la station dans le tableau tableauStations de la classe Réseau
	double tempsMarche1;	// Enregistrement du temps de marche entre le point de départ et la station
	double tempsMarche2;	// Enregistrement du temps de marche entre la station et le point d'arrivée
    
 
 	// Relations d'amitié
 	
  	friend ostream& operator << (ostream& os, const Station& station);
  	friend istream& operator >> (istream& is, Station& station);
  	friend istream& operator >> (istream& is, Reseau& reseau);
  
  	friend class Reseau;
  	template <class T>
  	friend class Tableau;
};


// La classe station encapsule toutes les propriétés d'un réseau de stations
class Reseau {

  // Méthodes publiques ========================================
  public:
  
    Reseau();					// Constructeur par défaut
    Reseau(int capacite_);		// Constructeur avec paramètre
    Reseau(const Reseau&);		// Constructeur par copie
    
    // Cette méthode est utilisée pour créer un tableau générique de deux dimensions servant
    // à stocker le temps requis pour voyager en vélo entre chaque combinaison de deux stations.
    void traiterReseau();
    
	// Cette méthode effectue les calculs pour déterminer le trajet optimal en BIXI entre un 
    // point d'origine et un point d'arrivée.
	void traiterRequete(const PointST& p1, const PointST& p2);


  // Méthodes privées ========================================
  private:	

	// Cette méthode calcule les temps de marche entre les points d'origine/arrivée et chacune des stations
	void calculTempsMarche(const PointST& pointOrigine, const PointST& pointDestination);
	
	// Traitement du résultat pour chaque requête
	void traitementResultat(int temps, bool marche, int indiceStationDepart, int indiceStationArrivee);
    
    // Mise à jour de l'état des stations si un vélo est utilisé
    void miseAJourEtatStations(int indiceStationDepart, int indiceStationArrivee);
    
    
  // Attributs ========================================
  private:

	Tableau<Tableau<double> > tableauReseau;	// Tableau stockant les temps en velo entre chaque combinaison de stations			
	Tableau<Station> tableauStations;			// Tableau de stations
	
	
	// Le tableau tableauPointeursTemps1 est un tableau de pointeurs vers les objets de type Station
	// contenus dans le tableau tableauStations. Les pointeurs de tableauPointeursTemps1 seront triés 
    // en fonction du temps de marche requis entre le point de départ et la station pointée. Le but 
    // est d'optimiser le temps d'exécution du programme.
	Tableau<Station*> tableauPointeursTemps1;
	
  
    friend istream& operator >> (istream& is, Reseau& reseau);
    friend ostream& operator << (ostream& os, const Reseau& reseau);
};


#endif
