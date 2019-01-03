#ifndef FASTQ_H
#define FASTQ_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

class Fastq
{
    public:

      //CONSTRUCTOR
    	Fastq();
    	Fastq(std::string nameFile);
      Fastq(std::string nameFile,bool fasta);
      Fastq(std::string nameFile,std::stringstream& ss);
      Fastq(std::string nameFile,std::stringstream& ss,bool fasta);
        //GET SET ..
    	void afficher();
        std::map<std::string,std::string> getSeq();
        void setSeq(std::map<std::string,std::string> newseq);

        //WRITE FUNCTIONS
    	void writeFastq(std::string path, bool app);
        void writeFasta(std::string path, bool app);
        void writeFastaDerep(std::string path);



        //METHODS (PROGRAMS)
        void removeN();
        void removeNfasta();
        void rmSmallSeq(unsigned int minLen);
        void rmSmallSeqfasta(unsigned int minLen);
        void reverseComplement();
        void demultiplex(std::string pathBarcode,
            std::string outputFolder,
            bool allowMismatch);
        void demultiplexDoubleTagPrimer(std::string pathBarcodeForward,
            std::string pathBarcodeReverse,
            std::string outputFolder,
            std::string pathPrimerForward,
            std::string pathPrimerReverse,
            bool allowMismatchDouble);
        void qualCheck(double expErrThreshold,
            unsigned int slindingWindow,
            unsigned int minsize);



    private:
    	std::string nameFile;
        std::map<std::string, std::string> seq;
        std::map<std::string, std::string> phredScore;
};

#endif // FASTQ_H

