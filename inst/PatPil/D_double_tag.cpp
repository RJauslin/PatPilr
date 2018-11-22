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