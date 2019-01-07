/*
 * RemoveNfasta.cpp: call the removeNfasta tools on a particular chunk
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

#include "RemoveNfasta.h"

#include "Fastq.h"
#include <string>

using namespace std;

void RemoveNfasta(Fastq fastqChunk, string pathFqFolder){
  fastqChunk.removeNfasta();
  fastqChunk.writeFasta(pathFqFolder,true);
}
