
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


#include "Fastq.h"
#include "RemoveN.h"
#include "RemoveNfasta.h"
#include "rmSmallSeq.h"
#include "D_simple_tag.h"
#include "D_double_tag.h"
#include "derep.h"
#include "derep_ech.h"



using namespace std;


void Help(int argc, const char **argv) {
    // std::cout is capable of quasi-multi-line statements, like so:

    cout << "Usage: " << argv[0] << endl << endl;
    cout << "The program PatPil has four functions implemented : " << endl << endl;

    cout << "************ RemoveN ************" << endl
      << "Remove the N nucleotide in the sequence\n"
      << "\nOptions :\n"
      << "-f\t filepath to the fastq\n"
      << "-o\t filepath to the output folder with name file\n\n";


    cout << "************ rmSmallSeq ************" << endl
      << "Remove the sequence that have less than a fixed number of nucleotide in the sequence " << endl
      << "\nOptions :\n"
      << "-f\t filepath to the fastq\n"
      << "-o\t filepath to the output folder with name file\n"
      << "-m\t length minimum to keep the sequence\n\n";

    cout << "************ derep ************" << endl
      << "Dereplicate a folder of file already dereplicated " << endl
      << "\nOptions :\n"
      << "-folder\t filepath to the folder that contains the fastq files\n"
      << "-good\t filepath to the output name file (accept sequence)\n"
      << "-bad\t filepath to the output name file (reject sequence) \n"
      << "-s\t number of occurence of each sequence in each file \n\n";

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
  f.qualCheck(err,sl,m);
  f.writeFasta(path,true);
  mtx.unlock();
}



int main(int argc,const char **argv){

  using namespace std::chrono;
  high_resolution_clock::time_point t1 = high_resolution_clock::now();

    if(argc <= 1){
     Help(argc,argv);
     return 1;
    }
    if (argc > 1) {
        string arg1 = argv[1];

        if(arg1 == "-h"){
          Help(argc,argv);
          return 0;
        }else if((arg1 == "RemoveN" or arg1 == "RemoveNfasta" or arg1 == "qualCheck" or arg1 == "rmSmallSeq" or arg1 == "D_simple_tag" or arg1 == "D_double_tag") && argc > 3){
          string f_opt = argv[2];

          if(f_opt == "-f" && argc > 5){

            string pathFqIn = argv[3];
            ifstream flux(pathFqIn.c_str());

            string o = argv[4];

            if(o == "-o"){

              string pathFqFolder = argv[5];


              cout << "\n------- " << arg1 <<" -------\n";
              if(flux){
                while(flux){
                  int count(0);
                  string ligne;
                  stringstream tmp;

                  //for the multi-threading

                  stringstream tmp2;
                  stringstream tmp3;
                  stringstream tmp4;


                  //IT CONSIDER 10^6 SEQUENCES (POSSIBLY THIS COULD BE CHANGED DEPENDING ON THE AVAILABLE RAM)
                  while(count < 500000*4){
                    if(getline(flux,ligne)){
                      if(arg1 == "qualCheck"){
                        if(ligne.find('\n') == std::string::npos){

                          if(count < 500000){
                            tmp << ligne << '\n';
                          }else if(count >= 500000 && count <500000*2) {
                            tmp2 << ligne << '\n';
                          } else if( count >= 500000*2 && count <500000*3){
                            tmp3 << ligne << '\n';
                          } else if( count >= 500000*3 && count < 500000*4){
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


                      high_resolution_clock::time_point t2 = high_resolution_clock::now();
                      duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
                      std::cout << "It took me " << time_span.count() << " seconds."<<endl;

                      cout << "------- finished -------" << endl;
                      break;
                      /*
                      IF THE END OF THE FILE IS REACH INSIDE THE CURRENT CHUNKS
                      (THIS WILL ALWAYS HAPPENS)
                      */
                    }
                  }//END WHILE CHUNK


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
                      cout << "ERROR in rmSmallSeq function" << endl;
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

                  }

                }//END WHILE FLUX
              }else{
                cerr << "ERROR cannot open the fastq file try to add ./ and check that it is the right name" << endl << endl;
                return 1;
              }
            }else{
              Help(argc,argv);
              return 1;
            }//END IF ( -o )
          }else{
            Help(argc,argv);
            return 1;
          }//END IF ( -f )
        }else if(arg1 == "derep"){

          int f_state = derep(argc,argv);
          if(f_state == 1){
            cerr << "Error in derep function" << endl;
            return 1;
          }
        }else if (arg1 == "derep_ech"){
          int f_state = derep_ech(argc,argv);
          if(f_state == 1){
            cerr << "Error in derep_ech function" << endl;
            return 1;
          }
        }else{
          Help(argc,argv);
          return 1;
        }// END IF ( -h )
    }// END IF ( argc > 1 )

   return 0;
}
