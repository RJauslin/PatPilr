CC = g++ -std=c++11
CFLAGS = -Wall -O3
LDFLAGS = -lm -pthread

all : PatPil

PatPil : main.o Fastq.o RemoveN.o RemoveNfasta.o rmSmallSeq.o rmSmallSeqfasta.o D_simple_tag.o D_double_tag.o derep.o derep_ech.o swmPrePars.o DNA.o trimPrimer.o uniqueFasta.o
	$(CC) $^ -o $@ $(LDFLAGS)

main.o  : main.cpp Fastq.h RemoveN.h RemoveNfasta.h rmSmallSeq.h rmSmallSeqfasta.h D_simple_tag.h derep.h derep_ech.h swmPrePars.h DNA.h trimPrimer.h uniqueFasta.h
	$(CC) main.cpp -c $(CFLAGS)

Fastq.o : Fastq.h Fastq.cpp
	$(CC) $*.cpp -c $(CFLAGS)

uniqueFasta.o : uniqueFasta.h Fastq.h uniqueFasta.cpp
	$(CC) $*.cpp -c $(CFLAGS)

trimPrimer.o : trimPrimer.h Fastq.h trimPrimer.cpp
	$(CC) $*.cpp -c $(CFLAGS)

RemoveN.o : RemoveN.h Fastq.h RemoveN.cpp
	$(CC) $*.cpp -c $(CFLAGS)

RemoveNfasta.o : RemoveNfasta.h Fastq.h RemoveNfasta.cpp
	$(CC) $*.cpp -c $(CFLAGS)

rmSmallSeq.o : rmSmallSeq.h Fastq.h rmSmallSeq.cpp
	$(CC) $*.cpp -c $(CFLAGS)

rmSmallSeqfasta.o : rmSmallSeqfasta.h Fastq.h rmSmallSeqfasta.cpp
	$(CC) $*.cpp -c $(CFLAGS)

D_simple_tag.o : D_simple_tag.h Fastq.h D_simple_tag.cpp
	$(CC) $*.cpp -c $(CFLAGS)

D_double_tag.o : D_double_tag.h Fastq.h D_double_tag.cpp
	$(CC) $*.cpp -c $(CFLAGS)

derep.o : derep.h Fastq.h derep.cpp DNA.h
	$(CC) $*.cpp -c $(CFLAGS)

derep_ech.o : derep_ech.h Fastq.h derep_ech.cpp DNA.h
	$(CC) $*.cpp -c $(CFLAGS)

swmPrePars.o : swmPrePars.h swmPrePars.cpp DNA.h
	$(CC) $*.cpp -c $(CFLAGS)

DNA.o : DNA.h DNA.cpp
	$(CC) $*.cpp -c $(CFLAGS)
