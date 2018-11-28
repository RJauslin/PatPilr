/*
 * D_double_tag.cpp: call the double tag demultiplexing on a particular chunk
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

int D_double_tag(Fastq fastqChunk,string pathFqFolder,int argc,const char **argv){
    if(argc < 14){
        cerr << "\n ERROR : you didn't pass enough argument check the command './PatPil -h'\n\n";
        return 1;
    }else{
        string arg6 = argv[6]; // -bF
        string barcodeF = argv[7];
        string arg8 = argv[8];// -bR
        string barcodeR = argv[9];
        string arg10 = argv[10];// -pF
        string primerF = argv[11];
        string arg12 = argv[12];// -pR
        string primerR = argv[13];
        if(argv[14] == NULL){
            cout << "\n\nNo mismatch is allowed in the demultiplexing process\n\n";
            fastqChunk.demultiplexDoubleTagPrimer(barcodeF,barcodeR,pathFqFolder,primerF,primerR,false);
            return 0;
        }else{
            string arg14 = argv[14]; // -mismatch
            if(arg14 == "-mismatch"){
                cout << "\n\nOne mismatch is allowed in the demultiplexing process\n\n";
                fastqChunk.demultiplexDoubleTagPrimer(barcodeF,barcodeR,pathFqFolder,primerF,primerR,true);
                return 0;
            }else{
                cerr << "\n\nERROR : choose between -mismatch or no argument\n\n";
                return 1;
            }
        }
    }

}
