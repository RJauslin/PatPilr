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


int derep_ech( int argc,const char **argv) {
    

  //./PatPil  derep_ech -f dossier -o nameoffasta.fasta -s seuil
  //0           1        2   3     4          5           6  7

  cout << "patate" << endl;
  
  // établissement du flux pour l'ouverture des fichiers fastq

  string arg1 = argv[1]; //derep 


  string arg2 = argv[2]; // -f
  string pathFaIn = argv[3];


  string arg4 = argv[4]; // -o
  string pathFaOut = argv[5];


  string arg6 = argv[6]; // -s
  int seuil = atoi(argv[7]);
  cout << pathFaIn << endl;
  cout << pathFaOut << endl;

  //string pathFaIn = argv[1],
  //       pathFaOut = argv[2];
  //int seuil = atoi(argv[3]);

  ifstream inPathFH( pathFaIn );
  ofstream outPathFH( pathFaOut );

  // parcourt du faIn
  
  string ligneFaIn;
  int indLigne( 1 );
  map<string, int> MseqCnt;

  if(inPathFH && outPathFH){
    while( getline( inPathFH, ligneFaIn ) ) {

      if( ligneFaIn.find( '>' ) != 0 ) {
        
        if( MseqCnt.count( ligneFaIn ) == 0 ) {
          int cnt( 1 );
          MseqCnt.insert( pair<string, int>( ligneFaIn, cnt ) );
        }
        else {
          int cnt( MseqCnt.find( ligneFaIn )->second );
          cnt++;
          MseqCnt.erase( ligneFaIn );
          MseqCnt.insert( pair<string, int>( ligneFaIn, cnt ) );
        }
      
      }

      if( indLigne % 100000 == 0 ) {
        cout << "parcourt fa " <<  indLigne << endl;
      }
      indLigne++;

    }

    // swap cnt et seq
    
    int indSeq( 1 );
    multimap<int, string> MMcntSeq;

    for( map<string, int>::iterator it = MseqCnt.begin(); it != MseqCnt.end(); it++ ) {
      string seq( it->first );
      int cnt( it->second );

      MMcntSeq.insert( pair<int, string>( cnt, seq ) );
      
      //if( indSeq % 10000 == 0 ) {
      //  cout << "swap " << indSeq << " / " << MseqCnt.size() << endl;
      //}
      indSeq++;

    }

    // écriture des séquences

    indSeq = 1;

    for( multimap<int, string>::reverse_iterator rit = MMcntSeq.rbegin(); rit != MMcntSeq.rend(); rit++ ){
      
      //cout << rit->first << endl;
      if(rit ->first >= seuil){
        outPathFH << '>' << indSeq << '_' << rit->first << endl << rit->second << endl;
        indSeq++;
      }
    }

    inPathFH.close();
    outPathFH.close();

    //

    cout << "burp!" << endl;
    return 0;
  }else{
    return 1;
  }
}
