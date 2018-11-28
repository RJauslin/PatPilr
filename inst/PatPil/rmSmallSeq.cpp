/*
 * rmSmallSeq.cpp: call the rmSmallSeq on a particular chunk
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

int rmSmallSeq(Fastq fastqChunk, string pathFqFolder, int argc, const char **argv){

	string arg6 = argv[6];// -m
    if(arg6 == "-m"){
	    stringstream convert(argv[7]);
    	int minLength(0);
        if (!(convert >> minLength)){ // do the conversion
            minLength = 0;
        }
    	fastqChunk.rmSmallSeq(minLength);
        fastqChunk.writeFastq(pathFqFolder,true);
        return 0;
    }else{
    	//Help(argc,argv);
    	return 1;
    }
}
