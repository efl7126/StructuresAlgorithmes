/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  Automne 2017 / TP1                                   *
 *  http://ericbeaudry.uqam.ca/INF3105/tp1/              */

#include "bixi.h"
#include <string>
#include <limits>
#include <math.h> 

#define MARCHE_VITESSE  1.0
#define BIXI_VITESSE    4.0
#define TAILLE_DECLARATION_TABLEAUX    500

// ======== Definitions des surchages d'opérateurs de flux d'entrée et de sortie ============


// Surcharge de l'opérateur d'insertion de flux pour la classe Station
ostream& operator << (ostream& os, const Station& station)
{
    
    os 	<< station.id 					// ID
       	<< "\t"
       	<< station.nomStation    		// nom
       	<< "\t"
       	<< station.coordonnee      		// point de coordonnée
       	<< "\t"
       	<< station.nbVelosDisponibles 	// nb vélos disponibles
       	<< "\t"
       	<< station.nbPointsAncrage;     // nb points d'ancrage disponibles
    
    return os;
}


// Surcharge de l'opérateur d'extraction de flux pour la classe Station
istream& operator >> (istream& is, Station& station)
{
       
    is >> station.id 					// ID
       >> station.nomStation    		// nom
       >> station.coordonnee      		// point de coordonnée
       >> station.nbVelosDisponibles 	// nb vélos disponibles
       >> station.nbPointsAncrage;		// nb points d'ancrage disponibles
    return is;
}


// Surcharge de l'opérateur d'insertion de flux pour la classe Reseau
ostream& operator << (ostream& os, const Reseau& reseau)
{
    
    for(int i = 0; i < reseau.tableauStations.taille(); i++)
    {
    	os << reseau.tableauStations[i] << endl;
    }
    
    return os;
}


// Surcharge de l'opérateur d'extraction de flux pour la classe Reseau
istream& operator >> (istream& is, Reseau& reseau)
{
    
    Station s;
    int indice = 0;
    while(is >> s){
      
      	s.indice = indice;	
      	
        reseau.tableauStations.ajouter(s);
        
        // L'adresse de la station ajoutée dans tableauStations est copiée
        // dans le tableau de pointeurs tableauPointeursTemps1
        reseau.tableauPointeursTemps1.ajouter(&(reseau.tableauStations[indice]));
        
        indice++;
                 
    }
   
    return is;
}



// ================= Constructeurs des classes Reseau et Station =======================

Station::Station()
{
	// Ne rien faire
}

Reseau::Reseau()
	: tableauReseau(TAILLE_DECLARATION_TABLEAUX), tableauStations(750), 
	tableauPointeursTemps1(TAILLE_DECLARATION_TABLEAUX)
{
	// Ne rien faire
}


Reseau::Reseau(int capacite_)
{
	// Ne rien faire
}


// =========== Définitions des fonctions implémentées par les étudiants ==============


// Cette fonction est utilisée pour créer un tableau générique de deux dimensions servant
// à stocker le temps requis pour voyager en vélo entre chaque combinaison de deux stations,
// peu importe les points de départ et d'arrivée. Notre hypothèse est que cela permet d'épargner
// du temps d'exécution puisque ces distances ont seulement besoin d'être calculées une fois
// (pour chaque combinaison station 1/station 2) pour chaque réseau de stations.

void Reseau::traiterReseau()
{
	for (int i = 0; i < tableauStations.taille(); i++)
	{
		Tableau<double> rangee(TAILLE_DECLARATION_TABLEAUX);
		
		for (int j = 0; j < tableauStations.taille(); j++)
		{
			rangee.ajouter(-1.0);
		}
		
		tableauReseau.ajouter(rangee);	
	}
}


// Cette fonction permet de trouver le trajet optimal en BIXI entre un point d'origine
// et un point d'arrivée

void Reseau::traiterRequete(const PointST& pointOrigine, const PointST& pointDestination)
{

	// Déclaration de variables
	double meilleurTemps, tempsMarche1, tempsVelo, tempsMarche2, tempsParcours;
	Station* pointeurPoint1;
	Station* pointeurPoint2;
	bool marche = true;
	int indiceMeilleureStationDepart, indiceMeilleureStationArrivee;
	
	
	// Calculer le temps de marche (sans velo) du point initial vers le point final.
	// La valeur obtenue est considérée commme le meilleur temps de trajet jusqu'à maintenant.
	meilleurTemps = pointOrigine.distance(pointDestination) / MARCHE_VITESSE;
	

	calculTempsMarche(pointOrigine, pointDestination);
	
	
	for (int i = 0; i < tableauPointeursTemps1.taille(); i++)
	// Pour chaque station 1, du temps (point de départ -> station 1) le plus court au plus élevé.
	{
		pointeurPoint1 = tableauPointeursTemps1[i];
		tempsMarche1 = pointeurPoint1->tempsMarche1; 	
		
		// Si le temps de marche vers la station est supérieur au meilleur temps, ou si la station n'a
		// aucun vélo disponible, on peut tout de suite rejeter la station.
		if((tempsMarche1 > meilleurTemps) || 
		   (pointeurPoint1->nbVelosDisponibles == 0))
				continue;
	
		for (int j = tableauPointeursTemps1.taille() - 1; j >= 0; j--)	
		// Pour chaque station 2, du temps (point de départ -> station 1) le plus élevé au plus court.
		// Notre hypothèse est que statistiquement, les stations éloignées du point de départ sont plus
		// près du point d'arrivée.
		{
			pointeurPoint2 = tableauPointeursTemps1[j];			
			tempsMarche2 = pointeurPoint2->tempsMarche2; 			

			// Si les temps de marche du trajet sont supérieurs au meilleur temps, si les stations 
			// évaluées sont les mêmes, ou si aucun point d'encrage n'est disponible, on peut rejeter la station.
			if ((tempsMarche1 + tempsMarche2) > meilleurTemps ||
				(pointeurPoint1 == pointeurPoint2) ||
			   	(pointeurPoint2->nbPointsAncrage == 0))
				continue;

		
			// Obtenir le temps en vélo de la première station jusqu'à la dernière station 
			// à partir de tableauReseau 
			if(tableauReseau[(pointeurPoint1->indice)][(pointeurPoint2->indice)] == -1)
			// Si le temps entre les deux stations n'est pas encore calculé, la valeur dans la
			// matrice sera égale à -1
			{
				// Calcul du temps requis en en vélo de la première station jusqu'à la dernière station
				tempsVelo = (pointeurPoint1->coordonnee).distance((pointeurPoint2->coordonnee)) / BIXI_VITESSE;
				// Stockage du temps dans tableauReseau pour la combinaison station1/station2
				tableauReseau[(pointeurPoint1->indice)][(pointeurPoint2->indice)] = tempsVelo;
				tableauReseau[(pointeurPoint2->indice)][(pointeurPoint1->indice)] = tempsVelo;
			}
			else	// Le temps entre les deux stations a déjà été calculé
				tempsVelo = tableauReseau[(pointeurPoint1->indice)][(pointeurPoint2->indice)];
			

			// Calculer le temps total du parcours
			tempsParcours = tempsMarche1 + tempsVelo + tempsMarche2;
			
			// Déterminer si le temps total calculé est inférieur au meilleur temps
			if(tempsParcours < meilleurTemps)
			{
				meilleurTemps = tempsParcours;
				indiceMeilleureStationDepart = i;	
				indiceMeilleureStationArrivee = j;
				marche = false;	// Le meilleur trajet n'est pas de simplement marcher
			}
		}
	}
		
	// Arrondir le meilleur temps à la seconde près
	meilleurTemps = round(meilleurTemps);
	
	// Affichage et mise à jour de l'état des stations Bixi de départ et d'arrivée s'il y a lieu
	traitementResultat(meilleurTemps, marche, indiceMeilleureStationDepart, indiceMeilleureStationArrivee);
}


// Cette méthode calcule les temps de marche entre les points d'origine/arrivée et chacune des stations
void Reseau::calculTempsMarche(const PointST& pointOrigine, const PointST& pointDestination)	
{	
	for (int h = 0; h < tableauStations.taille(); h++)
	{
	
		// Calculer le temps de marche du point d'origine jusqu'à la première station, pour toutes les
		// stations de tableauStations. Le résultat est enregistré dans l'attribut tempsMarche1 de la 
		// station correspondante.
		
		(tableauStations[h]).tempsMarche1 = pointOrigine.distance(tableauStations[h].coordonnee) / MARCHE_VITESSE;
		
		// Calculer le temps de marche de la deuxième station jusqu'au point d'arrivée, pour toutes les
		// stations de tableauStations. Le résultat est enregistré dans l'attribut tempsMarche2 de la 
		// station correspondante.
		(tableauStations[h]).tempsMarche2 = tableauStations[h].coordonnee.distance(pointDestination) / MARCHE_VITESSE;
			
	}
	
	// Les pointeurs de tableauPointeursTemps1 sont triés en fonction du temps de marche requis entre le 
	// point de départ et la station pointée, du temps le plus petit jusqu'au temps le plus élevé. L'objectif
	// est ensuite d'itérer à travers les stations en commençant par celles qui sont le plus près du point de départ.
	// Notre hypothèse est que cela permettra d'identifier rapidement les temps de trajet les plus courts.
	
	tableauPointeursTemps1.trierTableauPointeurs();
}


// Cette méthode permet le traitement du résultat (affichage et mise à jour de l'état des stations)
void Reseau::traitementResultat(int temps, bool marche, int indiceStationDepart, int indiceStationArrivee) 
{
	
	// Affichage des résultats
	if(marche)
		cout << "Marche " << temps << " s" << endl;
	else
	{
		cout 	<< (tableauPointeursTemps1[indiceStationDepart])->nomStation 
				<< " --> "
				<< (tableauPointeursTemps1[indiceStationArrivee])->nomStation
				<< " "
				<< temps 
				<< " s" 
				<< endl;	
		
		// Mise à jour des stations lorsqu'un vélo est transféré		
		miseAJourEtatStations(indiceStationDepart, indiceStationArrivee);		
	}		
}


// Cette méthode met à jour l'état des stations
void Reseau::miseAJourEtatStations(int indiceStationDepart, int indiceStationArrivee)	
{	
		(tableauPointeursTemps1[indiceStationDepart])->nbVelosDisponibles -= 1;
		(tableauPointeursTemps1[indiceStationDepart])->nbPointsAncrage += 1;
		
		(tableauPointeursTemps1[indiceStationArrivee])->nbVelosDisponibles += 1;
		(tableauPointeursTemps1[indiceStationArrivee])->nbPointsAncrage -= 1;
}


