/*
 * main.cpp: core algorithm of the different tools.
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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <cmath>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>

#include "Fastq.h"
#include "RemoveN.h"
#include "RemoveNfasta.h"
#include "rmSmallSeq.h"
#include "rmSmallSeqfasta.h"
#include "D_simple_tag.h"
#include "D_double_tag.h"
#include "derep.h"
#include "derep_ech.h"
#include "DNA.h"
#include "swmPrePars.h"

using namespace std;

void Help(int argc, const char **argv) {
    // std::cout is capable of quasi-multi-line statements, like so:

    cout << "Usage: " << argv[0] << endl << endl;
    cout << "The tool PatPil has many functions implemented : " << endl << endl;

    cout << "************ RemoveN ************" << endl
      << "Remove the sequence that have a 'N' nucleotide in the sequence\n"
      << "\nOptions :\n"
      << "-f\t filepath to the fastq\n"
      << "-o\t filepath to the output folder with filename\n\n";

    cout << "************ RemoveNfasta ************" << endl
      << "Remove the sequence that have a 'N' nucleotide in the sequence\n"
      << "\nOptions :\n"
      << "-f\t filepath to the fasta\n"
      << "-o\t filepath to the output folder with filename\n\n";

    cout << "************ rmSmallSeq ************" << endl
      << "Remove the sequence that have less than a fixed number of nucleotide in the sequence " << endl
      << "\nOptions :\n"
      << "-f\t filepath to the fastq\n"
      << "-o\t filepath to the output folder with filename\n"
      << "-m\t length minimum to keep the sequence\n\n";

    cout << "************ rmSmallSeqfasta ************" << endl
      << "Remove the sequence that have less than a fixed number of nucleotide in the sequence " << endl
      << "\nOptions :\n"
      << "-f\t filepath to the fasta\n"
      << "-o\t filepath to the output folder with filename\n"
      << "-m\t length minimum to keep the sequence\n\n";

    cout << "************ derep ************" << endl
      << "Dereplicate a folder of file already dereplicated " << endl
      << "\nOptions :\n"
      << "-folder\t filepath to the folder that contains the fasta files\n"
      << "-good\t filepath to the output filenames (accept sequence)\n"
      << "-bad\t filepath to the output filenames (reject sequence) \n"
      << "-s\t number of occurence of each sequence in each files \n\n";

    cout << "************ derep_ech ************" << endl
      << "Dereplicate a folder of file " << endl
      << "\nOptions :\n"
      << "-f\t filepath to the folder that contains the fasta files.\n"
      << "-o\t filepath to the output fasta file.\n"
      << "-s\t threshold for the number of occurence of each sequence. \n\n";

    cout << "************ qualCheck ************" << endl
      << "Check the quality of the sequence based on the Tara's publication" << endl
      << "\nOptions :\n"
      << "-f\t filepath to the fastq\n"
      << "-o\t filepath to the output folder\n"
      << "-t\t threshold for the percentage of allowed error\n"
      << "-s\t size of the sliding window\n"
      << "-m\t length minimum to keep the sequence\n\n";

    cout << "************ D_simple_tag ************" << endl
      << "Demultiplex the fastq file (seq and reverse) from a simple barcode file" << endl
      << "\nOptions :\n"
      << "-f\t filepath to the fastq\n"
      << "-o\t filepath to the output folder\n"
      << "-b\t .txt file that contains the barcode\n\n";

    cout << "************ D_double_tag ************" << endl
      << "Demultiplex the fastq file (seq and reverse) from a double barcode file with primer" << endl
      << "\nOptions :\n"
      << "-f\t filepath to the fastq\n"
      << "-o\t filepath to the output folder\n"
      << "-bF\t .txt file that contains the barcode forward\n"
      << "-bR\t .txt file that contains the barcode reverse\n"
      << "-pF\t .txt file that contains ALL the primer forward\n"
      << "-pR\t .txt file that contains ALL the primer reverse\n";
}

std::mutex mtx;

void qualCheckCall(Fastq f, string path, double err, unsigned int sl, int m)
{
  mtx.lock();
  f.afficher();
  f.qualCheck(err,sl,m);
  f.afficher();
  f.writeFasta(path,true);
  mtx.unlock();
}

int main(int argc,const char **argv){

  // FOR CALCULATE THE TIME NEEDED TO PERFORM THE PROGRAM
  using namespace std::chrono;
  high_resolution_clock::time_point t1 = high_resolution_clock::now();


    if(argc <= 1){
     Help(argc,argv);
     return 1;
    }
    if (argc > 1) {
        string arg1 = argv[1];

        /*
         * CHECK IF YOU CALL THE HELP OR A FUNCTION OF THE PROGRAM.
         * RETURN AN ERROR IF YOU CALLED SOMETHING WRONG.
         *
         * derep, derep_ech AND swmPrePars HAVE ITS OWN SPECIFICATIONS
         *
         */
        if(arg1 == "-h"){
          Help(argc,argv);
          return 0;
        }else if((arg1 == "RemoveN" or arg1 == "RemoveNfasta" or arg1 == "qualCheck" or arg1 == "rmSmallSeq" or arg1 == "rmSmallSeqfasta" or arg1 == "D_simple_tag" or arg1 == "D_double_tag")){

          /*
           * CHECK THAT THE ARGUMENT ARE PASSED CORRECTLY
           *
           * -f ALWAYS A STRING TO THE FILEPATH
           * -o COULD BE A FILEPATH OR A FOLDERPATH
           *
           */
          if(argc < 3){
            cerr << "You only give the name of the program and no arguments... That... that..."
                 << "that would not work Sorry\n  check ./PatPil -h \n";
            return 1;
          }

          string f_opt = argv[2];
          if(f_opt == "-f" && argc > 5){

            string pathFqIn = argv[3];
            ifstream flux(pathFqIn.c_str());

            string o = argv[4];
            if(o == "-o"){

              string pathFqFolder = argv[5];

              /*
               *  MAIN LOOP :
               *
               *  THE PROGRAM CREATE CHUNK TO BUILD AN INSTANCE OF FASTQ.
               *  THIS METHOD IS USED TO BE SURE THAT THE RAM IS NOT DUMPED
               *  BY TEXT FILE THAT CAN BE HUGE.
               *
               */

              cout << "\n------- " << arg1 <<" -------\n";

              // ONLY FOR THE DNA DRAWING :-)
              vector<int> dnainfo;
              dnainfo = dna(0,5,1);

              //TEST IF THE FILE CAN BE OPEN
              if(flux){
                while(flux){
                  int count(0);
                  string ligne;
                  stringstream tmp;

                  /*
                   * FOR MULTI-THREADING
                   *  (TODO: APPARENTLY NOT SO EFFICIENT IN THIS WAY PROBABLY
                   *   BETTER TO RETHINK THE CODE TO IMPROVE PERFORMANCE...)
                   */
                  stringstream tmp2;
                  stringstream tmp3;
                  stringstream tmp4;

                  //IT CONSIDER 10^4 SEQUENCES (POSSIBLY THIS COULD BE CHANGED DEPENDING ON THE AVAILABLE RAM)
                  while(count < 10000*4){
                    if(getline(flux,ligne)){
                      //ONLY qualCheck USE MULTITHREADING
                      if(arg1 == "qualCheck"){
                        if(ligne.find('\n') == std::string::npos){
                          if(count < 10000){
                            tmp << ligne << '\n';
                          } else if(count >= 10000 && count <10000*2) {
                            tmp2 << ligne << '\n';
                          } else if( count >= 10000*2 && count <10000*3){
                            tmp3 << ligne << '\n';
                          } else if( count >= 10000*3 && count < 10000*4){
                            tmp4 << ligne << '\n';
                          }
                          ++count;
                        }
                      }else{
                        if(ligne.find('\n') == std::string::npos){
                            tmp << ligne << '\n';
                            ++count;
                        }
                      }
                    }else{

                      break;
                      /*
                      IF THE END OF THE FILE IS REACH INSIDE THE CURRENT CHUNKS
                      (THIS WILL ALWAYS HAPPENS)
                      */
                    }
                  }//END WHILE CHUNK

                  // ONLY FOR THE DNA DRAWING :-)
                  dnainfo = dna(dnainfo[0],dnainfo[1],dnainfo[2]);

                  /*
                   * DEPENDING OF THE arg1 THE RIGHT CONSTRUCTOR AND THE DESIRED
                   * FUNCTION IS CALLED SEE Fastq.h and Fastq.cpp
                   */

                  if(arg1 == "RemoveN"){
                    Fastq fastqChunk(pathFqIn,tmp);
                    RemoveN(fastqChunk, pathFqFolder);

                  }else if(arg1 == "RemoveNfasta"){
                    Fastq fastaChunk(pathFqIn,tmp,true);
                    RemoveNfasta(fastaChunk, pathFqFolder);

                  }else if(arg1 == "rmSmallSeq"){
                    Fastq fastqChunk(pathFqIn,tmp);
                    int fstate = rmSmallSeq(fastqChunk, pathFqFolder, argc, argv);
                    if(fstate == 1){
                      cerr << "ERROR in rmSmallSeq function" << endl;
                      return 1;
                    }

                  }else if(arg1 == "rmSmallSeqfasta"){
                    Fastq fastaChunk(pathFqIn,tmp,true);
                    int fstate = rmSmallSeqfasta(fastaChunk, pathFqFolder, argc, argv);
                    if(fstate == 1){
                      cerr << "ERROR in rmSmallSeqfasta function" << endl;
                      return 1;
                    }

                  }else if(arg1 == "qualCheck"){

                    Fastq fastqChunk(pathFqIn,tmp);
                    Fastq fastqChunk2(pathFqIn,tmp2);
                    Fastq fastqChunk3(pathFqIn,tmp3);
                    Fastq fastqChunk4(pathFqIn,tmp4);
                    if(argc < 12){
                      cerr << "\n ERROR : you didn't pass enough argument check the command './PatPil -h'\n\n";
                    }else{
                      string arg6 = argv[6];// -t
                      double expErrThreshold = atof(argv[7]);//
                      string arg8 = argv[8];// -s
                      unsigned int slindingWindow = atoi(argv[9]);//
                      string arg10 = argv[10];// -m
                      int minsize = atoi(argv[11]);//

                      std::thread t1(qualCheckCall,fastqChunk,pathFqFolder,expErrThreshold,slindingWindow,minsize);
                      std::thread t2(qualCheckCall,fastqChunk2,pathFqFolder,expErrThreshold,slindingWindow,minsize);
                      std::thread t3(qualCheckCall,fastqChunk3,pathFqFolder,expErrThreshold,slindingWindow,minsize);
                      std::thread t4(qualCheckCall,fastqChunk4,pathFqFolder,expErrThreshold,slindingWindow,minsize);
                      t1.join();
                      t2.join();
                      t3.join();
                      t4.join();

                    }
                  }else if(arg1 == "D_simple_tag"){
                    Fastq fastqChunk(pathFqIn,tmp);

                    int fstate = D_simple_tag(fastqChunk, pathFqFolder, argc, argv);
                    if(fstate == 1){
                      cout << "ERROR in D_simple_tag function" << endl;
                      return 1;
                    }


                  }else if(arg1 == "D_double_tag"){

                    Fastq fastqChunk(pathFqIn,tmp);

                    int fstate = D_double_tag(fastqChunk, pathFqFolder, argc, argv);
                    if(fstate == 1){
                      cout << "ERROR in D_double_tag function" << endl;
                      return 1;
                    }

                  }else{
                    cerr << "ERROR : This could not happen, contact the Help center or cry until the end of time." << endl;
                  }

                }//END WHILE FLUX
              }else{
                cerr << "ERROR : cannot open the input file from the argument -f\n"
                "try to add the ABSOLUTE PATH or check that it is the right name." << endl << endl;
                return 1;
              }
            }else{
              cerr << "ERROR : you didn't pass enough argument to any function of the tools PatPil \n"
                   << "Check that you correctly put arguments '-o'" <<endl;
              return 1;
            }//END IF ( -o )
          }else{
            cerr << "ERROR : you didn't pass enough argument to any function of the tools PatPil \n"
                 << "Check that you correctly put arguments '-f' and '-o'" <<endl;
            return 1;
          }//END IF ( -f )
        }else if(arg1 == "derep"){

          if(argc < 3){
            cerr << "You only give the name of the program and no arguments... That... that..."
                 << "that would not work Sorry\n  check ./PatPil -h \n";
            return 1;
          }
          int f_state = derep(argc,argv);
          if(f_state == 1){
            cerr << "Error in derep function" << endl;
            return 1;
          }
        }else if (arg1 == "derep_ech"){
          if(argc < 3){
            cerr << "You only give the name of the program and no arguments... That... that..."
                 << "that would not work Sorry\n  check ./PatPil -h \n";
            return 1;
          }
          int f_state = derep_ech(argc,argv);
          if(f_state == 1){
            cerr << "Error in derep_ech function" << endl;
            return 1;
          }
        }else if (arg1 == "swmPrePars"){
          if(argc < 3){
            cerr << "You only give the name of the program and no arguments... That... that..."
                 << "that would not work Sorry\n  check ./PatPil -h \n";
            return 1;
          }
          int f_state = swmPrePars(argc,argv);
          if(f_state == 1){
            cerr << "Error in swmPrePars function" << endl;
            return 1;
          }
        }else{
          cerr << "ERROR : You haven't call a program implemented by PatPil"<<endl;
          return 1;
        }// END IF ( -h )
    }// END IF ( argc > 1 )


    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "It took me " << time_span.count() << " seconds."<<endl;

    cout << "------- finished -------" << endl;
   return 0;
}
