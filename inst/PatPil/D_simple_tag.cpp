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
