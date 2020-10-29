#include <vector>
#include <string>
class GOL{ //Definition de la classe
  
 public: //Methodes et operateurs de la classe
  //Constructeur qui permet de construire un objet de la classe. Il peut y
  //avoir differents constructeurs.
  //Il doit porter le meme nom que la classe.
  GOL();
  GOL(int dimi, int dimj);
  GOL(int dimij);
  GOL(int dimi, int dimj, std::string UserChoice);
  GOL(int dimij, std::string UserChoice);
  GOL(int dimi, int dimj, std::string UserChoice, std::string InitFile);
  GOL(std::string UserChoice, std::string InitFile);

  void initialisation(); //Initialisation du jeu
  void play(); //Mise a jour du statut des cellules lors d'une iteration
  int nbAliveNeighbours(int i, int j); //Nombre de voisins vivants pour (i,j)
  void saveSolution(int it); //Ecrit un fichier solution

 private: //Les attributs de la classe
  int _dimi; //Nombre de ligne de la grille
  int _dimj; //Nombre de colonnes de la grille
  std::string _results; // nom du repertoire où la solution
  std::string _initfile; // nom du fichier pour init le jeu
  // lorque on utilise GOL(std::string UserChoice) i.e custom init
  // sera sauvegerdée.
  //La grille qui contient le statut des cellules 1 si cellule vivante,
  //0 si elle est morte. Elle est definie comme un vecteur de vecteur de int.
  std::vector<std::vector<int> > _grid;
};
