/*
 * RemoveN.cpp: call the removeN tools on a particular chunk
 *
 * Please see main.cpp if you are looking for the core algorithm.
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

#include "trimPrimer.h"
#include "Fastq.h"
#include <vector>
#include <string>


using namespace std;

int trimPrimer(Fastq fastaChunk, string pathFqFolder, int argc, const char **argv)
{
  // /home/raphael/Documents/PatPilr_source/PatPilr/inst/PatPil/PatPil trimPrimer -f "/home/raphael/Documents/Cadavre/fungi_bacteria/SILVA/testbase.fasta" -o "/home/raphael/Documents/Cadavre/fungi_bacteria/SILVA/testbaseCleaned.fasta" -primer1 "/home/raphael/Documents/Cadavre/fungi_bacteria/SILVA/primer1.txt" -primer2 "/home/raphael/Documents/Cadavre/fungi_bacteria/SILVA/primer2.txt" -m 100 -M 700 -trim 0 -keepPrimer
  // arg[0] ./PatPilr
  // arg[1] trimPrimer
  // arg[2] -f
  // arg[3] file.fasta
  // arg[4] -o
  // arg[5] file.fasta
  // arg[6] -primer1
  // arg[7]  file.txt
  // arg[8] -primer2
  // arg[9] file.txt
  // arg[10] -m
  // arg[11] 100
  // arg[12] -M
  // arg[13] 2198
  // arg[14] -keeprimer


  if(argc < 13){
    cerr << "you didn't pass enough arguments. " << endl;
    return 1;
  }else{
    string primer1Path = argv[7];
    string primer2Path = argv[9];
    unsigned int l_min = atoi(argv[11]);
    unsigned int l_max = atoi(argv[13]);

    vector<string> primer1;
    vector<string> primer2;


    ifstream primer1Flux(primer1Path.c_str());
    ifstream primer2Flux(primer2Path.c_str());


    string primer1Ligne;
    if(primer1Flux){
      while(primer1Flux){
        if(getline(primer1Flux,primer1Ligne)){
          // cout << primer1Ligne << " : "<< endl;
          primer1.push_back(primer1Ligne);
        }
      }
    }
    string primer2Ligne;
    if(primer2Flux){
      while(primer2Flux){
        if(getline(primer2Flux,primer2Ligne)){
          // cout << primer2Ligne << " : "<< endl;
          primer2.push_back(primer2Ligne);
        }
      }
    }


    if(argv[14] == NULL){
      fastaChunk.trimPrimer(primer1,
                            primer2,
                            l_min,
                            l_max,
                            false);
    }else{
      string arg16 = argv[14];
      if(arg16 == "-keepPrimer"){
        fastaChunk.trimPrimer(primer1,
                              primer2,
                              l_min,
                              l_max,
                              true);
      }else{
        cerr << "You must give the argument -keepPrimer if you would like to add primer" << endl;
        return 1;
      }
    }
    fastaChunk.writeFasta(pathFqFolder,true);
    return 0;
  }

}
