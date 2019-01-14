#ifndef trimPrimer_H
#define trimPrimer_H

#include <string>
#include <vector>

#include "Fastq.h"

int trimPrimer(Fastq fastaChunk, std::string pathFqFolder, int argc, const char **argv);

#endif
