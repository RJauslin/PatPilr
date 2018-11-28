/*
 * derep.cpp: core algorithm of the dereplication tools
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


#include <set>
#include <map>
#include <sstream>
#include <cmath>



#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#include "Fastq.h"

using namespace std;

int derep(int argc,const char **argv){


  	//./PatPil	derep	-folder	dossier	-good	nameoffasta.fasta	-bad	nameoffasta.fasta	-s seuil
  	//0			1		2		3		4		5					6		7					8	9

  	string arg1 = argv[1]; //derep


  	string arg2 = argv[2]; // -folder
  	string pathDosFaIn = argv[3];


  	string arg4 = argv[4]; // -good
  	string pathFaOut = argv[5];


  	string arg6 = argv[6]; // -bad
  	string pathFaNoPassedOut = argv[7];


  	string arg8 = argv[8];// -s
  	int seuilNbRep = atoi(argv[9]);




  	ofstream outPathFH(pathFaOut);
  	ofstream outPathNotPassed(pathFaNoPassedOut);


  	DIR *DH( 0 );
  	DH = opendir( pathDosFaIn.c_str() );
	  struct dirent *nomFichier( 0 );
  	struct stat filestat;
	  set<string> Sechs;



  	while( (nomFichier = readdir(DH)) ) {
    	string pathFaIn( pathDosFaIn + "/" + nomFichier->d_name );
    	if ( stat( pathFaIn.c_str(), &filestat )) continue;
    	if ( S_ISDIR( filestat.st_mode )) continue;
    	string nomFa( nomFichier->d_name );
    	Sechs.insert( nomFa.c_str() );
  	}


  	/*
	Le programme fonctionne comme suit :
	1) On va parcourir l'ensemble des fichiers présent dans le dossier
	2) On sélectionne le premier fasta
	3) On parcourt le fasta (mainFasta) et on regarde quand chaque séquences est observé dans les fasta suivants
	4) On écrit la ligne dans le ofstream en mettant toutes les infos importantes :
		(> id seq_total - nomfichier _abondance du fichier - ...-  )
	5) On stock la sequence dans une map < seq_id, abondance total >
	6) On supprime au fur et a mesure les sequences deja observé de tous les fichiers.
	7) Dans l'étape 4) on vérifie que l'on a jamais observé cette séquence précédemment

	EDIT:

  	*/


  	map<string,int> alreadyCheck;

  	set<string>::iterator it = Sechs.begin();

  	int counter(1); // COMPTE LE NOMBRE DE SEQ SELECTIONNE
  	int counter2(1); // COMPTE LE NOMBRE DE SEQ REFUSE


  	//PARCOURT LE MAIN FILE
  	while(it != Sechs.end()) {



    	string pathFaIn( pathDosFaIn  + *it );
    	cout << "Work in progress in the file : " <<pathFaIn << endl << endl;
    	string nameFilemain( (*it).substr(0,(*it).find('.')));


    	bool fastaFile = true; // POUR QUE LE CONSTRUCTEUR DE CLASSE FASTQ CREER UN FASTA


    	//RECUPERE LA map< ID_SEQ ; SEQ >
    	map<string,string> mainFiles = Fastq(pathFaIn,fastaFile).getSeq();
    	map<string,string>::iterator s = mainFiles.begin();

    	//PARCOUR LES SEQUENCES DU MAIN FILES
 		while(s != mainFiles.end()){


 			//RECUPERE LE NOMBRE DE FOIS QUE
    		//string scoremain = s->second;
    		//scoremain.erase(0,1);

    		//string valueMainseqString = scoremain.substr(scoremain.find('_')+1,scoremain.length());
	    	//std::stringstream convert(valueMainseqString);
            //int valueMainseq(0);
            //if (!(convert >> valueMainseq)){
            //    valueMainseq = 0;
            // }

            // ID_SEQ DE LA SEQUENCES FINAL ET TOTAL D'ABONDANCE DE LA SEQUENCE
 			int total(0);
	    	string IdSeq;

	    	// COMPTEUR POUR LE NOMBRE DE PRESENCE DE LA SEQUENCE DANS LES FICHIERS
	    	int obsEch(0);

	    	set<string>::iterator k = Sechs.begin();

	    	//PARCOURS LES AUTRES FILES POUR VERIFIER LA PRESENCE DE LA SEQUENCE DANS LES AUTRES FICHIERS
	    	while(k != Sechs.end()){

	    		//NOM DU FICHIER
	    		string pathFaInTmp(pathDosFaIn  + *k);


	    		//FASTQ FILE TEMPORAIRE
	    		Fastq FastaTmp(pathFaInTmp,fastaFile);
	    		map< string, string > fastaTmp = FastaTmp.getSeq();


	    		string nameFile( (*k).substr(0,(*k).find('.')));



	    		if(fastaTmp.count(s->first) >0){ //SI ON TROUVE LA SEQ DANS LE FICHIER FASTATMP
	    			string nameSeq = fastaTmp[s->first];
	    			nameSeq.erase(0,1);
	    			string valueString = nameSeq.substr(nameSeq.find('_')+1,nameSeq.length());


	    			std::stringstream convert(valueString);
                    int value(0);
                    if (!(convert >> value)){ // do the conversion
                        value = 0;
                    }


	    			total += value;
	    			IdSeq +=  (nameFile+"_"+ valueString+'-');


					obsEch++;


					//ERASE THE SEQUENCE AND REWRITE THE FILE
					fastaTmp.erase(s->first);
					FastaTmp.setSeq(fastaTmp);
					//cout << "update du fichier :" << pathFaInTmp<< endl;

					FastaTmp.writeFastaDerep(pathFaInTmp);

	    		}else{ //SI ON TROUVE PAS LA SEQ DANS LE FICHER FASTATMP
	    			IdSeq +=  (nameFile+"_"+ "0"+'-');

	    		}


	    		k++;
	    	}

	    	if(alreadyCheck.count(s->first) == 0){
 				alreadyCheck.insert(pair<string, int>(s->first, total));
 				//cout << '<' << total <<'-' << IdSeq << endl << endl;
 				if(obsEch >=seuilNbRep){
 					outPathFH << '>' << counter<<"_" << total << '-' << IdSeq << endl << s->first << endl;
 					counter++;
 				}else{
 					outPathNotPassed << '>' << counter2 <<"_" << total << '-' << IdSeq << endl << s->first << endl;
 					counter2++;
 				}
 			}
	    s++;
	    }
    	it++;
	}


  	return 0;
}
