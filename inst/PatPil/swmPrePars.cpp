/*
 * swmPrePars.cpp: transfrom swarm output
 *
 * Please see main.cpp if you are looking for the core algorithm.
 */

/*
 * Copyright (C) 2019 Raphaël Jauslin
 * Copyright (C) 2018 Christophe Seppey
 *
 * This file is part of PatPil
 *
 * PatPil is free software; you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 3 of the License, or (at your option) any later version.
 *
 * PatPil is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PatPil; if not, see http://www.gnu.org/licenses/.
 */


#include <fstream>
#include <sstream>
#include <iostream>

#include <string.h>
#include <vector>
#include <map>

#include "swmPrePars.h"
#include "DNA.h"

using namespace std;

int swmPrePars(int argc,const char **argv)
{

  //./PatPil  swmPrePars	-c corresp	-i	RC.swm -o	tmp
  //0             1		      2		3		   4		5			6	  7

  cout << "miam!" << endl;

  // établissement des flux d'entre et sortie

  // argv[0] PatPil
  // argv[1] swmPrePars
  // argv[2] -c
  string pathCorrespIn = argv[3];
  // argv[4] -i
  string pathSwmIn = argv[5];
  // argv[6] -o
  string pathSwmOut = argv[7];

  ifstream inCorrespFH( pathCorrespIn ),
  inSwmFH( pathSwmIn );
  ofstream outSwmFH( pathSwmOut );

  // parcourt du fichier de correspondance

  string ligne;
  map<string, string> Mcorresp;

  if(inCorrespFH && inSwmFH && outSwmFH){
    while( getline( inCorrespFH, ligne ) ) {

      string partLigne,
      idSeqDerep;
      istringstream iss( ligne );
      while( getline( iss, partLigne, '-' ) ) {
        idSeqDerep = partLigne;
        break;
      }

      Mcorresp.insert( pair<string, string>( idSeqDerep, ligne ) );//contient l'id seq et la corresp

    }

    inCorrespFH.close();

    // parcourt du fichier swm op

    while( getline( inSwmFH, ligne ) ) {

      string partLigne;
      istringstream iss( ligne );
      while( getline( iss, partLigne, ' ' ) ) {
        outSwmFH << Mcorresp.find( '>' + partLigne )->second << ' '; // écrit dans le new RC.swm la ligne de corresp
        Mcorresp.erase( Mcorresp.find( '>' + partLigne ) );
      }
      outSwmFH << endl;

    }

    inSwmFH.close();
    outSwmFH.close();

    cout << "burp!" << endl;
    return 0;
  }else{
    return 1;
  }
}
