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

int main(){
  
  string UserChoice;
  if(GENREP()=="Custom"){
    cout << "ENTER REPOSITORY PATH FOR THE INIT FILE" <<"\n";
    cin >> UserChoice;
  }else{UserChoice = GENREP();}
  cout<<" CASE "<<GENREP()<<" UserChoice "<<UserChoice<<"\n";
  int iterationNB = 110;
  GOL game(50, 50);
  game.initialisation();
  game.saveSolution(0);
  for(int ite = 1; ite<iterationNB+1; ite++){
    game.play();
    game.saveSolution(ite);
    }
  return 0;
}
