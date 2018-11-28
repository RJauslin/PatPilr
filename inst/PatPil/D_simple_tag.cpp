/*
 * D_simple_tag.cpp: call the simple tag demultiplexing on a particular chunk
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

#include <string>
#include "Fastq.h"

using namespace std;

int D_simple_tag(Fastq fastqChunk,string pathFqFolder,int argc,const char **argv){
	string arg6 = argv[6]; // -b
    if(arg6 == "-b"){
      	string barcode = argv[7];
       	if(argv[8] == NULL){
			cout << "\n\nNo mismatch is allowed in the demultiplexing process\n\n";
            fastqChunk.demultiplex(barcode,pathFqFolder,false);
            return 0;
        }else{
            string arg8 = argv[8];

            if(arg8 == "-mismatch"){
                cout << "\n\nOne mismatch is allowed in the demultiplexing process\n\n";
                fastqChunk.demultiplex(barcode,pathFqFolder,true);
                return 0;
            }else{
                cerr << "\n\nERROR : choose between -mismatch or no argument\n\n";
                return 1;
            }
        }
	}else{
        return 1;
    }
}
