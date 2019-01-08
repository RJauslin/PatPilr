/*
 * uniqueFasta.cpp: core algorithm of the dereplication tools for a praticular file
 *
 */

/*
 * Copyright (C) 2019 Raphaël Jauslin
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
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include "Fastq.h"

using namespace std;

int uniqueFasta( int argc,const char **argv)
{
  //./PatPil  uniqueFasta -f dossier -o nameoffasta.fasta
  //0           1        2   3     4          5           6  7


  if(argc < 5){
    cerr << "You didn't pass enough argument check ./PatPil -h" << endl;
    return 1;
  }else{
  string arg1 = argv[1]; //uniqueFasta
  string arg2 = argv[2]; // -f
  string pathFaIn = argv[3]; // path
  string arg4 = argv[4]; // -o
  string pathFaOut = argv[5]; // path


  // ifstream flux(pathFaIn);
  // ofstream outPathFH(pathFaOut);


  Fastq fastaChunk(pathFaIn,true);
  fastaChunk.writeFastaDerep(pathFaOut);

  return 0;
  }



}
