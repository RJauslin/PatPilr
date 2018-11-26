#include "RemoveNfasta.h"

#include "Fastq.h"
#include <string>

using namespace std;

void RemoveNfasta(Fastq fastqChunk, string pathFqFolder){
  fastqChunk.removeNfasta();
  fastqChunk.writeFasta(pathFqFolder,false);
}
