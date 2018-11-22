#include "RemoveN.h"

#include "Fastq.h"
#include <string>

using namespace std;

void RemoveN(Fastq fastqChunk, string pathFqFolder){
  	
  	fastqChunk.removeN();
    fastqChunk.writeFastq(pathFqFolder,true);
}