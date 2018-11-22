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
