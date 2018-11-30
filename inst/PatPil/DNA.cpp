
#include <random>
#include <chrono>
#include <vector>
#include <iostream>

#include "DNA.h"

using namespace std;

int random (int lim)
{
  default_random_engine dre (chrono::steady_clock::now().time_since_epoch().count());     // provide seed
  uniform_int_distribution<int> uid {0,lim};   // help dre to generate nos from 0 to lim (lim included);
  return uid(dre);    // pass dre as an argument to uid to generate the random no
}


vector<int> dna(int nbrEspace,int nbrEtoile,int orientation)
{
  vector<int> out;

  //RANDOM NUMBER AND NUCLEOTIDE COUPLE GENERATING
  vector<string> nuc;
  int rn = random(3);
  if(rn == 0){
    nuc.push_back("A");
    nuc.push_back("T");
  }else if(rn ==1){
    nuc.push_back("C");
    nuc.push_back("G");
  }else if(rn == 2){
    nuc.push_back("T");
    nuc.push_back("A");

  }else if(rn == 3){
    nuc.push_back("G");
    nuc.push_back("C");
  }

  if(orientation == 1){
    if(nbrEspace == 6){
      cout << string(nbrEspace/2,' ') << nuc[0] << string(nbrEspace/2,' ') << endl;
      orientation = 2;

      nbrEspace = 2;
      nbrEtoile = 3;


    }else{
      cout << string(nbrEspace/2,' ') << nuc[0] << string(nbrEtoile,'-') << nuc[1] << string(nbrEspace/2,' ') << endl;
    }

    nbrEtoile = nbrEtoile -2;
    nbrEspace = nbrEspace + 2;
  }else{

    if(nbrEspace == 0){
      cout << string(nbrEspace/2,' ') << nuc[0] << string(nbrEtoile,'-') << nuc[1] << string(nbrEspace/2,' ') << endl;
      orientation = 1;

      nbrEspace = 4;
      nbrEtoile = 1;

    }else{
      cout << string(nbrEspace/2,' ') << nuc[0] << string(nbrEtoile,'-') << nuc[1] << string(nbrEspace/2,' ') << endl;
    }

    nbrEtoile = nbrEtoile + 2;
    nbrEspace = nbrEspace - 2;
  }


  out.push_back(nbrEspace);
  out.push_back(nbrEtoile);
  out.push_back(orientation);

  return out;
}
