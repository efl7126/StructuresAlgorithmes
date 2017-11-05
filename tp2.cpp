/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2017 | TP2
    http://ericbeaudry.uqam.ca/INF3105/tp2/   

    AUTEUR(S):
     1) Nom + Code permanent du l'étudiant.e 1
     2) Nom + Code permanent du l'étudiant.e 2
*/
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <limits>
#include "date.h"
#include "epicerie.h"
#include "pointst.h"

using namespace std;
void traiterCommandePlacer(Carte& carte, const string& nom, const PointST& position);
void traiterCommandeApprov(Carte& carte, const string& nomEpicerie, const string& nomAliment, 
	const int& quantite, const Date& dateExpiration);
void traiterCommandeInventaire(Carte& carte, const string& nomEpicerie);
void traiterCommandeRecommander(Carte& carte, PointST& position, int nbMaxEpicerie,
double distanceMaximale, Commande cmd);
void traiterCommandeRamasser(Carte& carte, Commande cmd, Tableau<string>& tabEpiceries);


int tp2(istream& entree){
    
    Carte carte;
    
    Date maintenant;
    while(entree){
        string typecommande;
        entree >> typecommande;
        if(!entree) break; // détection fin ==> sortie
        
        if(typecommande=="RECOMMANDER"){
            PointST p;
            int nbMaxEpiceries=0;
            double maxdistance=0;
            Commande c;
            char deuxpoints=0;
            entree >> p >> nbMaxEpiceries >> maxdistance >> deuxpoints >> c;
            assert(deuxpoints==':');
            // À compléter
            
            traiterCommandeRecommander(carte, p, nbMaxEpiceries, maxdistance, c);
            
        }else if(typecommande=="RAMASSER"){
            
            Tableau<string> tabEpiceries;
            
            Commande c;
            entree >> c;
            string nomepicerie;
            entree >> nomepicerie;
            tabEpiceries.ajouter(nomepicerie);
            
            while(entree && nomepicerie!=";" && nomepicerie!=" ;" && nomepicerie!="; "){
                // À compléter
                entree >> nomepicerie;
                
                tabEpiceries.ajouter(nomepicerie);
            }
            // À compléter
            
            traiterCommandeRamasser(carte, c, tabEpiceries);
            
            //cout << "COMPLET";
        }else if(typecommande=="APPROV"){
            string nomepicerie;
            char deuxpoints=0;
            entree >> nomepicerie >> deuxpoints;
            assert(deuxpoints==':');
            string nomproduit;
            entree >> nomproduit;
            while(entree && nomproduit!=";"){
                int quantite;
                Date dateexpiration;
                entree >> quantite >> dateexpiration;
                // À compléter
                
                traiterCommandeApprov(carte, nomepicerie, nomproduit, quantite, dateexpiration);
                
                entree >> nomproduit;
            }
            // À compléter
            cout << "OK";
        }else if(typecommande=="PLACER"){
            PointST position;
            string nom;
            char pointvirgule=0;
            entree >> nom >> position >> pointvirgule;
            assert(pointvirgule==';');
            // À compléter
            traiterCommandePlacer(carte,nom,position);
            
            cout << "OK";
        }else if(typecommande=="INVENTAIRE"){
            string nomepicerie;
            char pointvirgule=0;
            entree >> nomepicerie>> pointvirgule;
            assert(pointvirgule==';');
            // À compléter
            
            traiterCommandeInventaire(carte, nomepicerie);
            
 
        }else if(typecommande=="DATE"){
            char pointvirgule=0;
            entree >> maintenant >> pointvirgule;
            assert(pointvirgule==';');
            
            // À compléter
            carte.fixerDateActuelle(maintenant);
            
            cout << "OK";
        }else{
            cout << "Commande '" << typecommande << "' invalide!" << endl;
            return 2;
        }
        cout << endl;
        entree >> ws; // force la lecture d'un espace blanc.
    }
    return 0;
}
// syntaxe d'appel : ./tp2 [nomfichier.txt]
int main(int argc, const char** argv){
    // Gestion de l'entrée :
    //  - lecture depuis un fichier si un argument est spécifié;
    //  - sinon, lecture depuis std::cin.
    if(argc>1){
         std::ifstream entree_fichier(argv[1]);
         if(entree_fichier.fail()){
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
             return 1;
         }
         return tp2(entree_fichier);
    }else
         return tp2(std::cin);        

    return 0;
}


void traiterCommandePlacer(Carte& carte, const string& nomEpicerie, const PointST& position){

	Epicerie epicerieAInserer(nomEpicerie, position);
	carte.insererEpicerie(nomEpicerie, epicerieAInserer);
	//carte.afficher();
}

void traiterCommandeApprov(Carte& carte, const string& nomEpicerie, const string& nomAliment, 
	const int& quantite, const Date& dateExpiration)
{
	
	Aliment alimentAInserer(nomAliment, quantite, dateExpiration);
	carte.insererAliment(nomEpicerie, nomAliment, alimentAInserer);
	//carte.afficherContenuEpiceries();
	
}

void traiterCommandeInventaire(Carte& carte, const string& nomEpicerie)
{
	carte.inventaire(nomEpicerie);	
}

void traiterCommandeRecommander(Carte& carte, PointST& position, int nbMaxEpicerie,
double distanceTotalMax, Commande cmd)
{
	carte.peuplerTableauEpiceries();	
	carte.genererCombinaisons(nbMaxEpicerie);
	carte.evaluerCombinaisons(cmd);
	carte.trouverCheminLePlusCourt(position, distanceTotalMax);
	carte.viderTableaux();
}

void traiterCommandeRamasser(Carte& carte, Commande cmd, Tableau<string>& tabEpiceries)
{
	carte.ramasserProduits(tabEpiceries, cmd);
}

