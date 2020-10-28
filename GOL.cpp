#include "GOL.h" // Inclure le fichier .h
#include <bits/stdc++.h>

//Pour lier les fonctions de la classe, on utilise la declaration generique
//suivante: type NomClasse::nomFonction(arguments)

// Constructeur:
// default: set values by default:
GOL::GOL(){_dimi = 50; _dimj = 50; _grid.resize(_dimi,std::vector<int>(_dimj,0));}
// via input:
GOL::GOL(int dimi, int dimj){_dimi = dimi; _dimj = dimj; _grid.resize(_dimi,std::vector<int>(_dimj,0));}
GOL::GOL(int dimij){_dimi = dimij; _dimj = dimij; _grid.resize(_dimi,std::vector<int>(_dimj,0));}

// Initialisation du jeu:
// default: clown case:
void GOL::initialisation()
{
  std::cout << "_dimi " << _dimi <<std::endl;
  //_grid[3][3] = 1; _grid[3][4] = 1; _grid[3][5] = 1;
  //_grid[4][3] = 1; _grid[4][5] = 1;
  //_grid[5][3] = 1; _grid[5][5] = 1;
  _grid[19][24] = 1; _grid[19][26] = 1;
  _grid[20][24] = 1; _grid[20][26] = 1;
  _grid[21][24] = 1; _grid[21][25] = 1; _grid[21][26] = 1;
}

// Mise a jour du statut des cellules lors d'une iteration:
void GOL::play()
{
  std::vector<std::vector<int> > tmp;
  tmp = _grid;
  for(int i=0; i<_dimi; i++)
    {
      for(int j=0; j<_dimj; j++)
	{
	  if(_grid[i][j] == 0){//cellule morte
	    // Calculer le nbr de voision:
	    if(nbAliveNeighbours(i, j) == 3){tmp[i][j] = 1;}//devient vivante
	  }
	  else{//cellule vivante
	    if(nbAliveNeighbours(i, j) != 2 && nbAliveNeighbours(i, j) != 3){tmp[i][j] = 0;}//devient morte
	  }
	}
    }
  _grid = tmp;
}

// Calcule le nombre de voisins a (i,j) qui sont vivants:
int GOL::nbAliveNeighbours(int i, int j)
{
  int cpt = 0;
  int neigh_i[] = {i-1, i, i+1};
  int neigh_j[] = {j-1, j, j+1};
  for(auto vi : neigh_i)
    {
      if(vi>=0 && vi<_dimi)
	{
	  //std::cout<<"ii "<<vi<<"\n";
	  for(auto vj : neigh_j)
	    {
	      if(vj>=0 && vj<_dimj)
		{
		  //std::cout<<"jj "<<vj<<"\n";
		  if(vi != i || vj != j)
		    {
		      //std::cout<<"cccc "<<vi<<" "<<vj<<"\n";
		      //std::cout<<"cpt "<<cpt<<" vi "<<vi<<" vj "<<vj<< " "<<i<<" "<<j<<"\n";
		      if(_grid[vi][vj] == 1){cpt += 1;}
		    }
		}
	    }
	}
    }
  //std::cout<<"cpt "<<cpt<<" i "<<i<<" j "<<j<<"\n";
  //std::cout<<"cpt "<<cpt<<"\n";
  return cpt;
}

// Ecrit un fichier avec la solution:
void GOL::saveSolution(int it)
{
  FILE *mf;
  
  if(it == 0){
    mf = fopen("data", "w");
    fprintf(mf, "I,J,V,T\n");
    fclose(mf);
  }
  
  mf = fopen("data", "a");
  for( int i=0; i<_dimi; i++){
    for( int j=0; j<_dimj; j++){
      fprintf(mf, "%d,%d,%d,%d\n", i, j, _grid[i][j], it);
    }
  }
  fclose(mf);
}
