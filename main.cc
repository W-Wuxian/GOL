#include "GOL.h"
#include <bits/stdc++.h>
#include <cstdio>
// g++ -std=c++17 -pg -g -O0 -Wall ex6v3.cpp -o run
// valgrind --leak-check=yes ./run
// gprof -l run *.out > analysis.txt
using namespace std;
int main(){
  int iterationNB = 110;
  int r = 9;
  GOL game(50, 50);
  game.initialisation();
  game.saveSolution(0);
  for(int ite = 1; ite<iterationNB+1; ite++){
    game.play();
    game.saveSolution(ite);
    }
  return 0;
}
