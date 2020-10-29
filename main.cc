#include "GOL.h"
#include <bits/stdc++.h>
#include <cstdio>
// g++ -std=c++17 -pg -g -O0 -Wall ex6v3.cpp -o run
// valgrind --leak-check=yes ./run
// gprof -l run *.out > analysis.txt
using namespace std;

#ifdef CASE
#define GENREP() ((CASE==0)?("Random"):((CASE==1)?("Clown"):((CASE==2)?("Canon"):("Custom"))))
#endif

int main(int argc, char *argv[], char *envp[]){
  
  // Display each command-line argument.
  cout << "\nCommand-line arguments:\n";
  for( int count = 0; count < argc; count++ ){
    cout << "  argv[" << count << "]   " << argv[count] << "\n";
  }
  /*for( int i = 0; envp[i]!=NULL; i++ ){
    cout << "  envp[" << i << "]   " << envp[i] << "\n";
    }*/

  string UserChoice;
  string InitFile;
  int dimi=100, dimj=90;
  if(CASE>2){
    UserChoice = argv[1];
    if(argv[2] != NULL){InitFile = argv[2];}else{InitFile = "mat.txt";}
  }else{UserChoice = GENREP();}
  cout<<" CASE "<<GENREP()<<" UserChoice "<<UserChoice<<"\n";
  int iterationNB = 160;
  GOL game(dimi, dimj, UserChoice, InitFile);
  //GOL* game(0);
  //game = new GOL(dimi, dimj, UserChoice, InitFile);
  game.initialisation();
  game.saveSolution(0);
  for(int ite = 1; ite<iterationNB+1; ite++){
    game.play();
    game.saveSolution(ite);
    }
  //delete game;
  //game = 0;
  return 0;
}
