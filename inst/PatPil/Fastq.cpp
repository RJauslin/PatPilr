/*
 * Fastq.cpp: core class of the tools PatPil, it is here that the all methods are implemented
 *
 * Please see main.cpp if you are looking for the core algorithm of the different tools.
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


#include "Fastq.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>
#include <math.h>


using namespace std;


/*
#####################################################################################
#####################################################################################
#####################################################################################


                                    CONSTRUCTOR


#####################################################################################
#####################################################################################
#####################################################################################
*/

/*
Default constructor
*/
Fastq::Fastq()
{}


/*
Fastq constructor :
  it takes the path in string to the file and a boolean value
  to specify that we work on a fasta file
  (the map of phred score is not initialized)
 IT IS USED ONLY IN derep.cpp
*/
Fastq::Fastq(string nameFile,bool fasta) : nameFile(nameFile)
{
    if(fasta == true){
      ifstream path(nameFile.c_str());
      string ligne;
      string titre;
      int indexLigne(0);

      if(path){
        while(getline(path,ligne)){
            if(indexLigne % 2 == 0){
              titre = ligne;
            }else{
              seq.insert(pair<string, string>(ligne, titre));// un FASTA a titre et seq inverser (cela devrait etre modifier mais on en a besoin pour le derep ...)
            }
            indexLigne++;
        }
      }else{
        cout << "ERROR cannot open fastq the file TRY TO GIVE THE ABSOLUTE PATH" << endl;
      }
    }
}


/*
 Fasta constructor :
 it takes a stringstream by reference to construct the map of string
 It is used to work on chunk of the file and do not dump the ram in trying to load
 a bif file in the RAM.
 */
Fastq::Fastq(string nameFile,stringstream& ss,bool fasta) : nameFile(nameFile)
{
  string ligne;
  string titre;
  int indexLigne(0);
  if(fasta == true){
    while(std::getline(ss,ligne,'\n')){
      if(indexLigne % 2 == 0){
        titre = ligne;
      }else{
        seq.insert(pair<string, string>(titre, ligne));
      }
      indexLigne++;
    }
  }
}




/*
Fastq constructor :
  it takes the path in string to the file
  This is the most usual Fastq contructor
*/
Fastq::Fastq(string nameFile) : nameFile(nameFile)
{
    cout << "--- FASTQ FILE LOADED ---" << endl;
    cout << nameFile.c_str() << endl;
    ifstream path(nameFile.c_str());
    string ligne;
    string titre;
    int indexLigne(0);
    if(path){
        while(getline(path,ligne)){
            // titre
            if(indexLigne % 4 == 0){
               titre = ligne;
            }
            // seq
            if(indexLigne % 4 == 1){
               seq.insert(pair<string, string>(titre, ligne));
            }
            // score
            if(indexLigne % 4 == 3){
              phredScore.insert(pair<string, string>(titre, ligne));
           }
           indexLigne++;
        }
        if(seq.size() != phredScore.size()){
          cout << "ERROR the file is corrupt : the number of phredScore is not equal to number of sequences" << endl;
        }
    }else{
        cout << "ERROR cannot open fastq the file TRY TO GIVE THE ABSOLUTE PATH" << endl;
    }
}



/*
Fastq constructor :
  it takes a stringstream by reference to construct the map of string
  It is used to work on chunk of the file and do not dump the ram in trying to load
  a bif file in the RAM.
*/
Fastq::Fastq(string nameFile,stringstream& ss) : nameFile(nameFile)
{
    string ligne;
    string titre;
    int indexLigne(0);
    while(std::getline(ss,ligne,'\n')){
      if(indexLigne % 4 == 0){
        titre = ligne;
      }
      // seq
      if(indexLigne % 4 == 1){
        seq.insert(pair<string, string>(titre, ligne));
      }
      // score
      if(indexLigne % 4 == 3){
        phredScore.insert(pair<string, string>(titre, ligne));
      }
      indexLigne++;
    }
    if(seq.size() != phredScore.size()){
      cout << "ERROR the file is corrupt : the number of phredScore is not equal to number of sequences" << endl;
    }
}

/*
#####################################################################################
#####################################################################################
#####################################################################################


                              GET and SET functions


#####################################################################################
#####################################################################################
#####################################################################################
*/


map<std::string,std::string> Fastq::getSeq()
{
  return seq;
}

// A function to set the sequence of a Fastq (used in derep)
void Fastq::setSeq(map<string,string> newseq)
{
  seq = newseq;
}


/*
This method is only used to see if the fastq is well loaded in the Fastq class
*/
void Fastq::afficher()
{
	cout << nameFile << endl << endl;
	cout << "The fastq file contains : " << seq.size() << " sequences" << endl;
}


/*
#####################################################################################
#####################################################################################
#####################################################################################


                              WRITE functions


#####################################################################################
#####################################################################################
#####################################################################################
*/


/*
This method is used to write a Fastq in a .fastq file
  the argument app is used to know if the file is recreate at every time of append to the rest of the file
*/
void Fastq::writeFastq(std::string path, bool app)
{
  if(seq.size() == phredScore.size()){
    map<string,string>::iterator i;
    map<string,string>::iterator j = phredScore.begin();

    if(app == true){
      ofstream outpath(path,std::ios_base::app);
      for(i = seq.begin(); i != seq.end();++i){
        if( i->first == j->first){
          outpath << i -> first << endl << i -> second << endl << '+' << endl << j->second << endl;
          ++j;
        }
      }
    }else{
      ofstream outpath(path);
      for(i = seq.begin(); i != seq.end();++i){
        if( i->first == j->first){
          outpath << i -> first << endl << i -> second << endl << '+' << endl << j->second << endl;
          ++j;
        }
      }
    }
  }else{
    cout << "ERROR in fastq file lenght is different between seq containers and nameSeq containers" << endl;
  }
}




/*
This method is used to write a Fastq in a .fasta file
  it is used in
*/
void Fastq::writeFasta(std::string path, bool app)
{

  map<string,string>::iterator i;

  if(app == true){
    ofstream outpath(path,std::ios_base::app);
    if(outpath){
      for(i = seq.begin(); i != seq.end();++i){
        string newtitle = (i -> first); //ICI ON SUPPOSE QUE LE TITRE EST EN FIRST
        newtitle.replace(0,1,">");
        outpath << newtitle << endl << i -> second << endl;
      }
    }
  }else{
    ofstream outpath(path);
    if(outpath){
      for(i = seq.begin(); i != seq.end();++i){
        string newtitle = (i -> first);
        newtitle.replace(0,1,">");
        outpath << newtitle << endl << i -> second << endl;
      }
    }
  }
}

/*
  THIS FUNCTION IS ESSENTIAL TO derep program (see derep.h).

  In order to compare quickly the map in the derep program,
   we inverse the first and the second argument in the map paradigm.

  By this way we can quickly find informations about a sequence.

  So when we have to write the fasta file we need to use this function
   because the sequence is contains in the first argument and not the second
   as it is in the classical argument.

  EDIT : THIS TRICK SHOULD BE CHANGE IN ORDER TO HAVE ONLY ONE COMPUTATION OF THE WRITE METHOD

*/
void Fastq::writeFastaDerep(std::string path)
{
  map<string,string>::iterator i;
  ofstream outpath(path);
    if(outpath){
      for(i = seq.begin(); i != seq.end();++i){
        string newtitle = i->second; // ICI LE TITRE EST EN SECOND...
        newtitle.replace(0,1,">");
        outpath << newtitle << endl << i -> first << endl;
        }
    }
}



/*
#####################################################################################
#####################################################################################
#####################################################################################


                                      METHODS


#####################################################################################
#####################################################################################
#####################################################################################
*/


/*
This method is used to remove the N in a .fastq file
*/
void Fastq::removeN()
{
  map<string,string>::iterator i = seq.begin();
  map<string,string>::iterator j = phredScore.begin();
  unsigned int count(0);
  cout << "Total number of sequences : " << seq.size() << endl;
  while(i != seq.end()){
    string tmp = i -> second;
    if(tmp.find('N') != std::string::npos){
      if(i->first == j->first){
        i = seq.erase(i);
        j = phredScore.erase(j);
        ++count;
      }
    }else{
        ++i;
        ++j;
    }
  }
  cout << "Sequences with 'N' removed : " << count << endl << endl;
}


/*
 This method is used to remove the N in a .fastq file
 */
void Fastq::removeNfasta()
{
  map<string,string>::iterator i = seq.begin();
  unsigned int count(0);
  cout << "Total number of sequences : " << seq.size() << endl;
  while(i != seq.end()){
    string tmp = i -> second;
    if(tmp.find('N') != std::string::npos){
      i = seq.erase(i);
      ++count;
    }else{
      ++i;
    }
  }
  cout << "Sequences with 'N' removed : " << count << endl << endl;
}



/*
 This method is used to remove the sequences that have less than
 a fixed number of nucleotide in the fastq file
 */
void Fastq::rmSmallSeqfasta(unsigned int minLen)
{
  map<string,string>::iterator i=seq.begin();
  unsigned int count(0);
  cout << "Total number of sequences : " << seq.size() << endl;
  while(i != seq.end()){
    string tmp = i -> second;
    if(tmp.size() <= minLen){
        i = seq.erase(i);
        ++count;
    }else{
      ++i;
    }
    // cout << tmp << endl;
  }
  cout << "Sequences smaller than "<< minLen << ": " << count << endl << endl;
}



/*
This method is used to remove the sequences that have less than
 a fixed number of nucleotide in the fastq file
*/
void Fastq::rmSmallSeq(unsigned int minLen)
{
  map<string,string>::iterator i=seq.begin();
  map<string,string>::iterator j = phredScore.begin();
  unsigned int count(0);
  cout << "Total number of sequences : " << seq.size() << endl;
  while(i != seq.end()){
    string tmp = i -> second;
    if(tmp.size() <= minLen){
      if(i->first == j->first){
        i = seq.erase(i);
        j = phredScore.erase(j);
        ++count;
      }
    }else{
        ++i;
        ++j;
    }
  }

  cout << "Sequences smaller than "<< minLen << ": " << count << endl << endl;
}


/*
This function reverse and complement the sequence
*/
void Fastq::reverseComplement()
{
  map<string,string>::iterator i;
  map<string,string>::iterator j = phredScore.begin();
  for(i = seq.begin(); i != seq.end(); i++){
    if(i->first == j->first){
      int n = (i -> second).size();

      string tmpSeq = i -> second;
      string tmpPhred = j -> second;

      //REVERSE THE SEQ AND THE PHRED
      for (int i = 0; i < n / 2; i++){
        swap(tmpSeq[i],tmpSeq[n - i - 1]);
        swap(tmpPhred[i],tmpPhred[n - i - 1]);
      }

      //COMPLEMENT THE SEQ
      for(int i = 0; i < n; i++){
        if(tmpSeq[i] == 'A'){
          tmpSeq[i] = 'T';
        }else if(tmpSeq[i] == 'T'){
          tmpSeq[i] = 'A';
        }else if(tmpSeq[i] == 'C'){
          tmpSeq[i] = 'G';
        }else if(tmpSeq[i] == 'G'){
          tmpSeq[i] = 'C';
        }
      }

      //CHANGE THE FASTQ ATTRIBUTES
      i -> second = tmpSeq;
      j -> second = tmpPhred;
    }
    j++;
  }
}



/*
This method is used to demultiplex the fastq file.
*/
void Fastq::demultiplex(string pathBarcode,
  string outputFolder,
  bool allowMismatch)
{
  // READING FILE
  ifstream path(pathBarcode.c_str());
  string ligne;


  //CHECK IF THE IFSTREAM STATES
  if(path){
    /*
     MAP OF INPUT
      map<namefile ; barcode>
    */
    map<string,string> barcode;
    while(getline(path,ligne)){
      barcode.insert(pair<string, string>(ligne.substr(ligne.find('\t')+1, ligne.length()), ligne.substr(0, ligne.find('\t'))));
    }


    /*
      UNKNOWN SEQUENCE OUTPUT OFSTREAM
    */
    string tmp = outputFolder;
    ofstream unknown(tmp.append("unknown.fastq"),std::ios_base::app);
    if(unknown){

      /*
        INITILAIZE THE MAP THAT WILL BE USED TO OUTPUT :
         map<barcode ; pointer to ofstream>
      */
      map<string,ofstream*> output;
      for(map<string,string>::iterator k = barcode.begin(); k != barcode.end(); ++k){
        string tmp = outputFolder;
        output[k->second] = new ofstream(tmp.append(k -> first),std::ios_base::app); // std::ios_base::app is creating the file if it does not exist but append in the other case
        if(!output[k->second] || !*output[k->second]){
          perror((k -> second).c_str());
        }
      }


      map<string,string>::iterator i;
      map<string,string>::iterator j = phredScore.begin();
      int count(0);
      for(i = seq.begin(); i != seq.end(); i++){
        bool checkUnknown = false;

        //reverse seq
        int n = (i -> second).size();
        string tmpSeq = i -> second;
        string tmpPhred = j -> second;
        //REVERSE THE SEQ AND THE PHRED
        for (int i = 0; i < n / 2; i++){
          swap(tmpSeq[i],tmpSeq[n - i - 1]);
          swap(tmpPhred[i],tmpPhred[n - i - 1]);
        }
        //COMPLEMENT THE SEQ
        for(int i = 0; i < n; i++){
          if(tmpSeq[i] == 'A'){
            tmpSeq[i] = 'T';
          }else if(tmpSeq[i] == 'T'){
            tmpSeq[i] = 'A';
          }else if(tmpSeq[i] == 'C'){
            tmpSeq[i] = 'G';
          }else if(tmpSeq[i] == 'G'){
            tmpSeq[i] = 'C';
          }
        }
        bool writeSeq = false;
        map<string,ofstream*>::iterator u;
        u = output.begin();
        while(u != output.end() && writeSeq == false){

            int size_barcode = (u -> first).size();
            string tag = (u -> first);

            //IMPLEMENTATION MISMATCH FOR THE SEQ
            pair<string::iterator, string::iterator> mispair;
            pair<string::iterator, string::iterator> mispairRev;

            string seqBegin = (i -> second).substr(0,size_barcode);
            string seqBeginRev = tmpSeq.substr(0,size_barcode);

          if(allowMismatch == true){

            mispair = mismatch(seqBegin.begin(),seqBegin.end(), tag.begin()); //find first mismatch
            mispairRev = mismatch(seqBeginRev.begin(),seqBeginRev.end(),tag.begin());


            int nbrOfMismatch = 0;
            int nbrOfMismatchRev = 0;

            while(mispair.first != seqBegin.end()){
              ++mispair.first;
              ++mispair.second;
              mispair = mismatch(mispair.first,seqBegin.end(), mispair.second);
              nbrOfMismatch++;
            }


            while(mispairRev.first != seqBeginRev.end()){
              ++mispairRev.first;
              ++mispairRev.second;
              mispairRev = mismatch(mispairRev.first,seqBeginRev.end(),mispairRev.second);
              nbrOfMismatchRev++;
            }



            string subTag1 = (u->first).substr(0,(u->first).length()-1);
            string subTag2 = (u->first).substr(1,(u->first).length());


            string::iterator searchSub2 = search(seqBegin.begin(),seqBegin.end(),subTag2.begin(),subTag2.end());
            string::iterator searchSub1 = search(seqBegin.begin(),seqBegin.end(),subTag1.begin(),subTag1.end());
            string::iterator searchSub2rev = search(seqBeginRev.begin(),seqBeginRev.end(),subTag2.begin(),subTag2.end());
            string::iterator searchSub1rev = search(seqBeginRev.begin(),seqBeginRev.end(),subTag1.begin(),subTag1.end());


            bool cond1 = (seqBegin == (u -> first));
            bool cond2 = (nbrOfMismatch == 1);
            bool cond3 = (searchSub1 != seqBegin.end() || searchSub2 != seqBegin.end());
            bool cond4 = (tmpSeq.substr(0,size_barcode) == (u->first));
            bool cond5 = (nbrOfMismatchRev == 1);
            bool cond6 = (searchSub1rev != seqBeginRev.end() || searchSub2rev != seqBeginRev.end());



            if(cond1 or cond2 or cond3 or cond4 or cond5 or cond6){
              if(i->first == j->first){
                string newseq  = (i->second);
                newseq.erase(0,size_barcode);
                string newphred = (j->second);
                newphred.erase(0,size_barcode);
                *(u -> second) << i -> first << endl << newseq << endl << '+' << endl << newphred << endl;
                checkUnknown = true;
                writeSeq = true;
              }
            }
            /*
            if(seqBegin == (u -> first)){
              if(i->first == j->first){
                *(u -> second) << i -> first << endl << i -> second << endl << '+' << endl << j -> second << endl;
                checkUnknown = true;
                writeSeq = true;
              }
            }else if(nbrOfMismatch == 1){
              if(i->first == j->first){
                *(u -> second) << i -> first << endl << i -> second << endl << '+' << endl << j -> second << endl;
                checkUnknown = true;
                writeSeq = true;
              }
            }else if(searchSub1 != seqBegin.end() || searchSub2 != seqBegin.end()){
              if(i->first == j->first){
                *(u -> second) << i -> first << endl << i -> second << endl << '+' << endl << j -> second << endl;
                checkUnknown = true;
                writeSeq = true;
              }
            }else if(tmpSeq.substr(0,size_barcode) == (u->first)){
              if(i->first == j -> first){
                *(u -> second) << i -> first << endl << i -> second << endl << '+' << endl << j -> second << endl;
                checkUnknown = true;
                writeSeq = true;
              }
            }else if(nbrOfMismatchRev == 1){
              if(i->first == j->first){
                *(u -> second) << i -> first << endl << i -> second << endl << '+' << endl << j -> second << endl;
                checkUnknown = true;
                writeSeq = true;
              }
            }else if(searchSub1rev != seqBeginRev.end() || searchSub2rev != seqBeginRev.end()){
              if(i->first == j->first){
                *(u -> second) << i -> first << endl << i -> second << endl << '+' << endl << j -> second << endl;
                checkUnknown = true;
                writeSeq = true;
              }
            }
            */
          }else{
            bool condForward = (i -> second).substr(0,size_barcode) == (u -> first);
            bool condReverse = tmpSeq.substr(0,size_barcode) == (u->first);
            if(condForward or condReverse){
              if(i->first == j->first){
                string newseq  = (i->second);
                newseq.erase(0,size_barcode);
                string newphred = (j->second);
                newphred.erase(0,size_barcode);
                *(u -> second) << i -> first << endl << newseq << endl << '+' << endl << newphred << endl;
                checkUnknown = true;
                writeSeq = true;
              }
            }
          }
        ++u;
        }
        if(checkUnknown == false){
          unknown << i -> first << endl << i -> second << endl << '+' << endl << j -> second << endl;
        }
        ++j;
        ++count;
      }

      /*
        DELETE POINTERS ON THE OUTPUT FILE
      */
      for(map<string,ofstream*>::iterator it = output.begin(); it != output.end(); ++it) {
        delete it->second;
        it->second = 0;
      }
    }else{
      cout << "ERROR in demultiplex function cannot open the outputFolder try to add ./ and check that you give the right name" << endl << endl;
    }
  }else{
    cout << "ERROR in demultiplex function cannot open the barcode file try to add ./ and check that you give the right name" << endl << endl;
  }
}






/*
This method is used to demultiplex the .fastq file with double tag file
So it takes two .txt file and check all the combination.
*/
void Fastq::demultiplexDoubleTagPrimer(string pathBarcodeForward,
  string pathBarcodeReverse,
  string outputFolder,
  string pathPrimerForward,
  string pathPrimerReverse,
  bool allowMismatchDouble)
{


  // READING FILE
  ifstream pathForward(pathBarcodeForward.c_str());
  ifstream pathReverse(pathBarcodeReverse.c_str());
  ifstream pathPrimerF(pathPrimerForward.c_str());
  ifstream pathPrimerR(pathPrimerReverse.c_str());
  string ligneF;
  string ligneR;
  string lignePrimerF;
  string lignePrimerR;


  //CHECK IF THE IFSTREAM STATES
  if(pathForward && pathReverse && pathPrimerF && pathPrimerR){



    /*
     MAP OF INPUTS
      map<name ; barcode>
    */
    map<string,string> barcodeForward;
    map<string,string> barcodeReverse;

    while(getline(pathForward,ligneF)){
        barcodeForward.insert(pair<string, string>(ligneF.substr(ligneF.find('\t')+1, ligneF.length()), ligneF.substr(0, ligneF.find('\t'))));
    }
    while(getline(pathReverse,ligneR)){
        barcodeReverse.insert(pair<string, string>(ligneR.substr(ligneR.find('\t')+1, ligneR.length()), ligneR.substr(0, ligneR.find('\t'))));
    }

    /*
    VECTOR DE PRIMER_F AND PRIMER-R
    */
    std::vector<string> primerF;
    std::vector<string> primerR;
    //cout << "Lecture des primers" << endl;
    while(getline(pathPrimerF,lignePrimerF)){
        primerF.push_back(lignePrimerF);
    }
    while(getline(pathPrimerR,lignePrimerR)){
        primerR.push_back(lignePrimerR);
    }



    // UNKNOWN FILE INTIALIZATION
    string tmp = outputFolder;
    ofstream unknown(tmp.append("unknown.fastq"),std::ios_base::app);
    if(unknown){


      /*
      MAP OF OUTPUT (POINTER OF OSTREAM) :
        map< name_forward _ name_reverse ; ofstream* >
      */
      map<string,ofstream*> output;
      for(map<string,string>::iterator k = barcodeForward.begin(); k != barcodeForward.end(); ++k){
        for(map<string,string>::iterator l = barcodeReverse.begin(); l != barcodeReverse.end(); ++l){
          string tmp = outputFolder;
          string nameFile = (k -> first) + '_' + (l -> first) + ".fastq";
          output[(k->second+'_'+l->second)] = new ofstream(tmp.append(nameFile),std::ios_base::app);// std::ios_base::app is creating the file if it does not exist but append in the other case
        }
      }


      /*
        PRINCIPAL LOOP : DEMULTIPLEX THE FILE
          1) IT READ THE FILE AND GET THE SIZE OF EACH SIZE OF THE BARCODE
          2) COMPARE THE BEGINNING AND THE END OF EACH SEQUENCES.
          3) PUT IN EACH OFSTREAM DEPENDING ON THE RIGHT BARCODES.
          4) IF IT DOES NOT HAVE FOUND A BARCODE IT PUT IN THE UNKNOWN FILE.
      */
      map<string,string>::iterator i;
      map<string,string>::iterator j = phredScore.begin();
      int count(0);

      for(i = seq.begin(); i != seq.end(); i++){


        int n = (i -> second).size();
        bool checkUnknown = false;

        string tmpSeq = i -> second;
        string tmpPhred = j -> second;

        //REVERSE THE SEQ AND THE PHRED
        for (int i = 0; i < n / 2; i++){
          swap(tmpSeq[i],tmpSeq[n - i - 1]);
          swap(tmpPhred[i],tmpPhred[n - i - 1]);
        }
        //COMPLEMENT THE SEQ
        for(int i = 0; i < n; i++){
          if(tmpSeq[i] == 'A'){
            tmpSeq[i] = 'T';
          }else if(tmpSeq[i] == 'T'){
            tmpSeq[i] = 'A';
          }else if(tmpSeq[i] == 'C'){
            tmpSeq[i] = 'G';
          }else if(tmpSeq[i] == 'G'){
            tmpSeq[i] = 'C';
          }
        }

        /*
          Deux while pour check d'abord les primers
        */
        unsigned int s = 0;
        unsigned int l = 0;
        while(s < primerF.size() && (checkUnknown == false)){ //tant que non trouvé (false)
          l = 0; //remettre à 0 la loop suivante
          while(l < primerR.size() && (checkUnknown == false)){//tant que non trouvé (false)

            /*
            Si on trouve deux primers dans la sequence ----->
            */
            if(((i->second).find(primerF[s]) != string::npos)  && ((i->second).find(primerR[l]) != string::npos)){

              bool writeSeq = false;
              map<string,ofstream*>::iterator u;
              u = output.begin();
              while(u != output.end() && writeSeq == false){

                string barF = (u -> first).substr(0, (u -> first).find('_'));
                string barR = (u -> first).substr((u -> first).find('_')+1,(u -> first).length());
                size_t F = (i->second).find(primerF[s]);
                size_t R = (i->second).find(primerR[l]);
                string seqBegin = (i -> second).substr(0,F);
                string seqEnd = (i->second).substr(R +primerR[l].size(), (i -> second).length());


                //CHECK THAT THE BARCODE AND THE BEGIN OF THE SEQ IS THE RIGHT SIZE
                if((barF.size() - F == 0) && (barR.size() - seqEnd.size() == 0)){

                 //IMPLEMENTATION MISMATCH FOR THE SEQ BARCODE FORWARD
                  pair<string::iterator, string::iterator> mispairF;

                  if(allowMismatchDouble == true){
                    mispairF = mismatch(seqBegin.begin(),seqBegin.end(), barF.begin()); //find first mismatch
                    int nbrOfMismatchF = 0;
                    while(mispairF.first != seqBegin.end()){
                       ++mispairF.first;
                       ++mispairF.second;
                       mispairF = mismatch(mispairF.first,seqBegin.end(), mispairF.second);
                       nbrOfMismatchF++;
                    }

                    //IMPLEMENTATION MISMATCH FOR THE SEQ BARCODE REVERSE
                    pair<string::iterator, string::iterator> mispairR;
                    mispairR = mismatch(seqEnd.begin(),seqEnd.end(),barR.begin());
                    int nbrOfMismatchR = 0;
                    while(mispairR.first != seqEnd.end()){
                      ++mispairR.first;
                      ++mispairR.second;
                      mispairR = mismatch(mispairR.first,seqEnd.end(),mispairR.second);
                      nbrOfMismatchR++;
                    }

                    /*
                    si partant du début jusqu'au primer on trouve le barcode alors on selectionne
                    */

                    if(seqBegin == barF && seqEnd == barR){
                      if(i->first == j->first){
                        string newseq  = (i->second);
                        string newphred = (j -> second);

                        newseq.erase(R + primerR[l].size(), (i->second).length()); // on efface le deuxième tag
                        newphred.erase(R + primerR[l].size(), (j->second).length());

                        newseq.erase(R,primerR[l].size()); // on efface le primer reverse
                        newphred.erase(R,primerR[l].size());

                        newseq.erase(0,F);//efface premier tag
                        newphred.erase(0,F);

                        newseq.erase(0,primerF[s].size()); // on efface le primer forward
                        newphred.erase(0,primerF[s].size());


                        *(u -> second) << i -> first << endl << newseq << endl << '+' << endl << j -> second << endl;
                        checkUnknown = true;
                        writeSeq = true;
                          //goto endloop;
                          //break;
                      }
                    }else if((seqBegin == barF && nbrOfMismatchR == 1) || (seqEnd == barR && nbrOfMismatchF == 1) || (nbrOfMismatchF == 1 && nbrOfMismatchR == 1)){




                      if(i->first == j->first){
                        string newseq  = (i->second);
                        string newphred = (j -> second);

                        newseq.erase(R + primerR[l].size(), (i->second).length()); // on efface le deuxième tag
                        newphred.erase(R + primerR[l].size(), (j->second).length());

                        newseq.erase(R,primerR[l].size()); // on efface le primer reverse
                        newphred.erase(R,primerR[l].size());

                        newseq.erase(0,F);//efface premier tag
                        newphred.erase(0,F);

                        newseq.erase(0,primerF[s].size()); // on efface le primer forward
                        newphred.erase(0,primerF[s].size());


                        *(u -> second) << i -> first << endl << newseq << endl << '+' << endl << j -> second << endl;
                        checkUnknown = true;
                        writeSeq = true;
                          //goto endloop;
                          //break;
                      }
                    }
                  }else{
                    if(seqBegin == barF && seqEnd == barR){
                      if(i->first == j->first){

                        string newseq  = (i->second);
                        string newphred = (j -> second);

                        newseq.erase(R + primerR[l].size(), (i->second).length()); // on efface le deuxième tag
                        newphred.erase(R + primerR[l].size(), (j->second).length());

                        newseq.erase(R,primerR[l].size()); // on efface le primer reverse
                        newphred.erase(R,primerR[l].size());

                        newseq.erase(0,F);//efface premier tag
                        newphred.erase(0,F);

                        newseq.erase(0,primerF[s].size()); // on efface le primer forward
                        newphred.erase(0,primerF[s].size());


                        *(u -> second) << i -> first << endl << newseq << endl << '+' << endl << j -> second << endl;
                        checkUnknown = true;
                        writeSeq = true;
                          //goto endloop;
                          //break;
                      }
                    }
                  }
                }
                ++u;
              }
            /*
            Si on a pas trouvé deux primers dans la sequence on regarde la reverse
            */
            }else if(tmpSeq.find(primerF[s]) != string::npos  && tmpSeq.find(primerR[l]) != string::npos){


                bool writeSeq = false;
                map<string,ofstream*>::iterator u;
                u = output.begin();
                while(u != output.end() && writeSeq == false){
                //for(map<string,ofstream*>::iterator u = output.begin(); u != output.end(); ++u){

                  string barF = (u -> first).substr(0, (u -> first).find('_'));
                  string barR = (u -> first).substr((u -> first).find('_')+1,(u -> first).length());
                  size_t F = tmpSeq.find(primerF[s]);
                  size_t R = tmpSeq.find(primerR[l]);
                  string seqBeginRev = tmpSeq.substr(0,F);
                  string seqEndRev = tmpSeq.substr(R +primerR[l].size(), tmpSeq.length());

                  if( (barF.size() - seqBeginRev.size() == 0) && (barR.size() - seqEndRev.size() == 0)){


                    if(allowMismatchDouble == true){



                      //IMPLEMENTATION MISMATCH FOR THE REVERSE SEQ BARCODE FORWARD
                      pair<string::iterator, string::iterator> mispairRevF;
                      mispairRevF = mismatch(seqBeginRev.begin(),seqBeginRev.end(), barF.begin()); //find first mismatch
                      int nbrOfMismatchRevF = 0;
                      while(mispairRevF.first != seqBeginRev.end()){
                        ++mispairRevF.first;
                        ++mispairRevF.second;
                        mispairRevF = mismatch(mispairRevF.first,seqBeginRev.end(), mispairRevF.second);
                        nbrOfMismatchRevF++;
                      }

                      //IMPLEMENTATION MISMATCH FOR THE SEQ BARCODE REVERSE
                      pair<string::iterator, string::iterator> mispairRevR;
                      mispairRevR = mismatch(seqEndRev.begin(),seqEndRev.end(),barR.begin());
                      int nbrOfMismatchRevR = 0;
                      while(mispairRevR.first != seqEndRev.end()){
                        ++mispairRevR.first;
                        ++mispairRevR.second;
                        mispairRevR = mismatch(mispairRevR.first,seqEndRev.end(),mispairRevR.second);
                        nbrOfMismatchRevR++;
                      }

                      if(seqBeginRev == barF && seqEndRev == barR){
                        if(i->first == j->first){
                          string newseq  = tmpSeq;
                          string newphred = tmpPhred;

                          newseq.erase(R + primerR[l].size(), tmpSeq.length()); // on efface le deuxième tag
                          newphred.erase(R + primerR[l].size(),tmpPhred.length());

                          newseq.erase(R,primerR[l].size()); // on efface le primer reverse
                          newphred.erase(R,primerR[l].size());

                          newseq.erase(0,F);//efface premier tag
                          newphred.erase(0,F);

                          newseq.erase(0,primerF[s].size()); // on efface le primer forward
                          newphred.erase(0,primerF[s].size());

                          *(u -> second) << i -> first << endl << newseq << endl << '+' << endl << j -> second << endl;
                          checkUnknown = true;
                          writeSeq = true;
                        //break;
                        //goto endloop;
                        }
                      }else if((seqBeginRev == barF && nbrOfMismatchRevR == 1) || (seqEndRev == barR && nbrOfMismatchRevF == 1) || (nbrOfMismatchRevF == 1 && nbrOfMismatchRevR == 1)){

                        if(i->first == j->first){
                          string newseq  = tmpSeq;
                          string newphred = tmpPhred;

                          newseq.erase(R + primerR[l].size(), tmpSeq.length()); // on efface le deuxième tag
                          newphred.erase(R + primerR[l].size(),tmpPhred.length());

                          newseq.erase(R,primerR[l].size()); // on efface le primer reverse
                          newphred.erase(R,primerR[l].size());

                          newseq.erase(0,F);//efface premier tag
                          newphred.erase(0,F);

                          newseq.erase(0,primerF[s].size()); // on efface le primer forward
                          newphred.erase(0,primerF[s].size());

                          *(u -> second) << i -> first << endl << newseq << endl << '+' << endl << j -> second << endl;
                          checkUnknown = true;
                          writeSeq = true;
                          //goto endloop;
                          //break;
                        }
                      }
                    }else{



                      if(seqBeginRev == barF && seqEndRev == barR){
                        if(i->first == j->first){
                          string newseq  = tmpSeq;
                          string newphred = tmpPhred;

                          newseq.erase(R + primerR[l].size(), tmpSeq.length()); // on efface le deuxième tag
                          newphred.erase(R + primerR[l].size(),tmpPhred.length());

                          newseq.erase(R,primerR[l].size()); // on efface le primer reverse
                          newphred.erase(R,primerR[l].size());

                          newseq.erase(0,F);//efface premier tag
                          newphred.erase(0,F);

                          newseq.erase(0,primerF[s].size()); // on efface le primer forward
                          newphred.erase(0,primerF[s].size());

                          *(u -> second) << i -> first << endl << newseq << endl << '+' << endl << j -> second << endl;
                          checkUnknown = true;
                          writeSeq = true;
                        //break;
                        //goto endloop;
                        }
                      }
                    }
                  }
                ++u;
                }
              }
            //} // FERME POUR LA REVERSE
          ++l;
          }//FERME PRIMER 1
        ++s;
        }//FERME PRIMER 2
        //endloop:

        // SI ON A RIEN TROUVE ALORS CA PART DANS UNKNOWN
        if(checkUnknown == false){
          unknown << i -> first << endl << i -> second << endl << '+' << endl << j -> second << endl;
        }
        ++j;
        ++count;
      }

      // DELETE POINTERS
      for(map<string,ofstream*>::iterator it = output.begin(); it != output.end(); ++it) {
        delete it->second;
        it->second = 0;
      }
    }else{
     cout << "ERROR cannot open the outputFolder check the path file" << endl;
    }
  }else{
    cout << "ERROR cannot open the barcode or the primer check the path file" << endl;
  }
}


/*
  This function is the function that
   do the qualCheck explain by TARA
   see README

*/
void Fastq::qualCheck(double expErrThreshold,
            unsigned int slindingWindow,
            unsigned int minsize)
{

  map<string,string>::iterator i;
  map<string,string>::iterator j = phredScore.begin();

  int countKeepseq(0);
  int countTotalseq(0);



  for(i = seq.begin(); i != seq.end();){
    bool keepSeq = true;
    countTotalseq++;
    string tmp = (j->second);

    if(tmp.size() <= minsize){
      keepSeq = false;
    }else{
      while( (tmp.size() >= slindingWindow) && (keepSeq == true) ){
        string subSeqPhred(tmp.substr(0,slindingWindow));
        // cout << tmp << endl << endl;
        double expErrSliding(0.0);
        double proba(0.0);
        for(unsigned int k = 0; k < subSeqPhred.size(); k++){
          expErrSliding += subSeqPhred[k]-33.0;
        }
        expErrSliding /= slindingWindow;
        proba = pow(10.0, -expErrSliding/10.0);
        // cout << "proba :" << proba << endl;
        if(proba >= expErrThreshold){
          keepSeq = false;
          break;
        }
        tmp.erase(0,1);
      }
    }
    //cout << keepSeq << endl << endl;
    if(keepSeq == false){
      if(i->first == j->first){
        //cout << i->first << endl;
        //cout << j->first << endl;
        i = seq.erase(i);
        j = phredScore.erase(j);
      }
    }else{
      countKeepseq++;
      i++;
      j++;
    }
  }
  // cout << "Nombre total de sequences : " << countTotalseq << endl << endl;

  // cout << "Nombre de sequences gardées : " << countKeepseq << endl << endl;
}
