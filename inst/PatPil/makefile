CC = g++
CFLAGS = -Wall -O3
LDFLAGS = -lm -pthread

all : PatPil

PatPil : main.o Fastq.o RemoveN.o rmSmallSeq.o D_simple_tag.o D_double_tag.o derep.o derep_ech.o
	$(CC) $^ -o $@ $(LDFLAGS) 

main.o  : main.cpp Fastq.h RemoveN.h rmSmallSeq.h D_simple_tag.h derep.h derep_ech.h
	$(CC) main.cpp -c $(CFLAGS)

Fastq.o : Fastq.h Fastq.cpp
	$(CC) $*.cpp -c $(CFLAGS)

RemoveN.o : RemoveN.h Fastq.h RemoveN.cpp
	$(CC) $*.cpp -c $(CFLAGS)

rmSmallSeq.o : rmSmallSeq.h Fastq.h rmSmallSeq.cpp
	$(CC) $*.cpp -c $(CFLAGS)

D_simple_tag.o : D_simple_tag.h Fastq.h D_simple_tag.cpp
	$(CC) $*.cpp -c $(CFLAGS)

D_double_tag.o : D_double_tag.h Fastq.h D_double_tag.cpp
	$(CC) $*.cpp -c $(CFLAGS)

derep.o : derep.h Fastq.h derep.cpp
	$(CC) $*.cpp -c $(CFLAGS)

derep_ech.o : derep_ech.h Fastq.h derep_ech.cpp
	$(CC) $*.cpp -c $(CFLAGS)