#include "GOL.h" // Inclure le fichier .h
#include <bits/stdc++.h>

//Pour lier les fonctions de la classe, on utilise la declaration generique
//suivante: type NomClasse::nomFonction(arguments)

// Constructeur:
// default: set values by default:
GOL::GOL(){_dimi = 50; _dimj = 50; _grid.resize(_dimi,std::vector<int>(_dimj,0)); _results="Random";}
// via dimension input, directory for output set by default to "Clown":
GOL::GOL(int dimi, int dimj){_dimi = dimi; _dimj = dimj; _grid.resize(_dimi,std::vector<int>(_dimj,0)); _results="Random";}
GOL::GOL(int dimij){_dimi = dimij; _dimj = dimij; _grid.resize(_dimi,std::vector<int>(_dimj,0)); _results="Random";}
// via dimension and directory for output by name:
GOL::GOL(int dimi, int dimj, std::string UserChoice){_dimi = dimi; _dimj = dimj; _grid.resize(_dimi,std::vector<int>(_dimj,0)); _results=UserChoice;}
GOL::GOL(int dimij, std::string UserChoice){_dimi = dimij; _dimj = dimij; _grid.resize(_dimi,std::vector<int>(_dimj,0)); _results=UserChoice;}
// via name:
GOL::GOL(int dimi, int dimj, std::string UserChoice, std::string InitFile){_dimi = dimi; _dimj = dimj; _grid.resize(_dimi,std::vector<int>(_dimj,0))
			       ; _results=UserChoice; _initfile=InitFile;}
GOL::GOL(std::string UserChoice, std::string InitFile){_dimi = 50; _dimj=50; _grid.resize(_dimi,std::vector<int>(_dimj,0))
									       ; _results=UserChoice; _initfile=InitFile;}

// Initialisation du jeu:
// default: clown case:
void GOL::initialisation()
{
  // Dossier pour mettre les résultats (dont le nom dépend du choix)
  system(("mkdir -p ./" + _results).c_str());
  if(_results ==  "Clown") // Clown
    {
      if(_dimi < 50 || _dimj < 50){_dimi=50; _dimj=50; _grid.resize(_dimi,std::vector<int>(_dimj,0));}
      std::cout << "_dimi " << _dimi << " _dimj " << _dimj << " _grid.size() " << _grid.size()  <<std::endl;
      _grid[19][24] = 1; _grid[19][26] = 1;
      _grid[20][24] = 1; _grid[20][26] = 1;
      _grid[21][24] = 1; _grid[21][25] = 1; _grid[21][26] = 1;
    }
  else if(_results == "Canon") // Canon
    {
      if(_dimi < 50 || _dimj < 50){_dimi=50; _dimj=50; _grid.resize(_dimi,std::vector<int>(_dimj,0));}
      std::cout << "_dimi " << _dimi << " _dimj " << _dimj << " _grid.size() " << _grid.size()  <<std::endl;
      _grid[20][ 6]=1; _grid[23][21]=1; _grid[21][30]=1; _grid[37][43]=1;
      _grid[21][ 6]=1; _grid[20][22]=1; _grid[22][30]=1; _grid[38][43]=1;
      _grid[20][ 7]=1; _grid[21][22]=1; _grid[18][40]=1; _grid[40][43]=1;
      _grid[21][ 7]=1; _grid[22][22]=1; _grid[19][40]=1; _grid[41][43]=1;
      _grid[20][16]=1; _grid[21][23]=1; _grid[18][41]=1; _grid[42][43]=1;
      _grid[21][16]=1; _grid[18][26]=1; _grid[19][41]=1; _grid[38][44]=1;
      _grid[22][16]=1; _grid[19][26]=1; _grid[37][40]=1; _grid[40][44]=1;
      _grid[19][17]=1; _grid[20][26]=1; _grid[38][40]=1; _grid[38][45]=1;
      _grid[23][17]=1; _grid[18][27]=1; _grid[40][40]=1; _grid[40][45]=1;
      _grid[18][18]=1; _grid[19][27]=1; _grid[37][41]=1; _grid[39][46]=1;
      _grid[24][18]=1; _grid[20][27]=1; _grid[38][41]=1; _grid[19][21]=1;
      _grid[18][19]=1; _grid[17][28]=1; _grid[40][41]=1; _grid[17][30]=1;
      _grid[24][19]=1; _grid[21][28]=1; _grid[41][41]=1; _grid[43][42]=1;
      _grid[21][20]=1; _grid[16][30]=1; _grid[42][41]=1;
    }
  else if(_results == "Random") // Random (default)
    {
      std::cout << "_dimi " << _dimi << " _dimj " << _dimj << " _grid.size() " << _grid.size()  <<std::endl;
      srand(3000);
      for(int i=0; i<_dimi; i++){
	for(int j=0; j<_dimj; j++){
	  _grid[i][j] = (rand() % 2);
	}
      }
    }
  else
    {
      FILE* mf;
      int iv=0, jv=0, vv=0;
      int a=0, b=0;
      mf = fopen((_results+"/"+_initfile).c_str(), "r");
      std::cout<<(_initfile).c_str()<<"\n";
      std::cout<<(_results+"/"+_initfile).c_str()<<"\n";
      fscanf(mf, "%d %d\n", &a, &b);
      _dimi = a; _dimj = b;
      std::cout<<"dimi dimj "<<a<<" "<<b<<"\n";
      _grid.resize(_dimi,std::vector<int>(_dimj,0));
      for(int i=0; i<_dimi; i++){
	for(int j=0; j<_dimj; j++){
	  fscanf(mf, "%d %d %d\n", &iv, &jv, &vv);
	  //std::cout<<"i j v"<<iv<<" "<<jv<<" "<<vv<<"\n";
	  _grid[iv][jv] = vv;
	}
      }
      fclose(mf);
    }
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
    mf = fopen((_results+"/data").c_str(), "w");
    fprintf(mf, "I,J,V,T\n");
    fclose(mf);
  }
  
  mf = fopen((_results+"/data").c_str(), "a");
  for( int i=0; i<_dimi; i++){
    for( int j=0; j<_dimj; j++){
      fprintf(mf, "%d,%d,%d,%d\n", i, j, _grid[i][j], it);
    }
  }
  fclose(mf);
}
