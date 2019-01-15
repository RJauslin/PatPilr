# PatPilr
Implementation of the tools PatPil in R. This package is a tool to facilitate the pre-treatment and some part of the treatment of Next-Generation Sequencing data.

## Current version
* Current version : 1.1.12
* Last update : 2019-01-15


## Installation

### Linux

Before installing the package PatPilr in R or Rstudio, you need to be sure that the package devtools is right installed on your machine. 

``` r
install.packages("devtools")
```

If you have any error messages when you try to install the package devtools then try to copy/paste the following dependencies on a Linux terminal.

``` r
sudo apt-get install build-essential libcurl4-gnutls-dev libxml2-dev libssl-dev
```

Finally install the PatPilr package from the github repository by copy/paste the following command in Rstudio or R :

``` r
devtools::install_github("Rjauslin/PatPilr@master")
library(PatPilr) # load R package 
install.PatPil() # install the program PatPil in the package
```

### Windows

In order to be able to install the program PatPil from R or Rstudio, you need to install Rtools. Go to the URL https://cran.r-project.org/bin/windows/Rtools/ and choose Rtools35.exe. Follow the setup instructions, select the folder *C:\Rtools* and when given the option to edit your PATH, take it. To check that you have right install Rtools you can copy/paste the following command in R.

``` r
Sys.getenv('PATH')
```
If you correctly take the option to edit your PATH, you should see something like,

``` r
....c:\Rtools\bin;c:\Rtools\MinGW\bin;...
```
Then you can install the pacakge *devtools*.

``` r
install.packages("devtools")
```
Finally install the package PatPilr. 

``` r
devtools::install_github("Rjauslin/PatPilr")
library(PatPilr)  # load R package 
install.PatPil() # install the program PatPil in the package
```


## preTreatment

This function merges, demultiplex, and clean your fastq files. You are supposed to put only the fastq files specified by the xxx_R1.fastq, xxx_R2.fastq and the informations needed for the demultiplexing part. See **simple tag** and **double tag** sections.  


``` r
#Linux
pathFolder <- "/home/raphael/Documents/......./working_directory/"
#Windows
pathFolderWindows <- "C:/Users/raphael/......./working_directory/"

preTreatment(pathFolder, # path to the working directory
  m = 10, # min overlap
  M = 100, # max overlap
  x = 0.25, # max mismatch density
  t = 4, # number of threads
  mismatch = FALSE, # allows 1 mismatch in tag if TRUE
  err = 0.01, # expected error
  slide = 50, # sliding window
  minlength = 60) # minimum length of sequences considered

```

### simple tag
You have to put in your working directory a file called **barcode.txt**. It is really important that the barcode file have the following configuration.

* **barcode.txt**

``` r
ACGAGTGCGT	name1.fastq
ACGCTCGACA	name2.fastq
AGACGCACTC	name3.fastq
AGCACTGTAG	name4.fastq
ATCAGACACG	name5.fastq
ATATCGCGAG	name6.fastq
CGTGTCTCTA	name7.fastq
CTCGCGTGTC	name8.fastq
...

```

### double tag
You have to put in your working directory three files called **forwardtag.txt**, **reversetag.txt**, and **primer.txt**. It is really important that the files have the following configuration.

* **forwardtag.txt**

Notice that there is no extension file such as .fastq
``` r
ACACACAC	ForwardTag1
ACGACTCT	ForwardTag2
ACGCTAGT	ForwardTag3
ACTATCAT	ForwardTag4
...
```

* **reversetag.txt**

Notice that there is no extension file such as .fastq
``` r
ACACACAC	ReverseTag1
ACGACTCT	ReverseTag2
ACGCTAGT	ReverseTag3
ACTATCAT	ReverseTag4
...
```

* **primer.txt**

``` r
CAAAATCATAAAGATATTGGDAC	GAAATTTCCDGGDTATMGAATGG
```

wobble nucleotide allowed :

``` r
R = AG
Y = CT
S = GC
W = AT
K = GT
M = AC
B = CGT
D = AGT
H = ACT
V = ACG
```


## Dereplication

This function dereplicate your fasta files. You are supposed to put only the fasta files inside the working directory. The function will create two folders for temporary work. The first one is called *derep_ech* and the second one *derep*. At the end of the program inside of the *derep* folder you will find two fasta files. **RC.fa** contains your passed sequences and the **RCNotpassed.fa** the sequences that have failed the selection based on the option *within* and *between*.

``` r
Dereplicate(pathFolder, # path to the working directory
  within = 3, # threshold for the number of occurence of the sequence within a file
  between = 2) # threshold for the number of occurence of the sequence between files
```
If you would like to apply a dechimering step on your dereplicated fasta files, you can do the two steps of the dereplication by hand with the functions *call.derep_ech* and *call.derep*.

``` r
call.derep_ech(pathFolder, # path to the working directory (non-dereplicated files)
  within = 3)  # threshold for the number of occurence of the sequence within a file
```


``` r
call.derep(pathFolder, # path to the working directory (already dereplicated files)
  between = 2) # threshold for the number of occurence of the sequence between files
```



## trimBase

The package PatPilr allows you to trim primers on a reference database. In order to get some 100% of match when you assign your sequences, you have to compare with sequences that have the same "configuration". Hence, you possibly need to trim your reference base with some primers.

``` r
trimBase(fastaPath, # path to the reference base
  outputFasta, # path to the output
  primerForward, # The character string representing your forward primer.
  primerReverse, # The character string representing your reverse primer.
  trim = 0, # A scalar integer representing the number of nucleotide that you want allowed to be trimmed on the primers.
  l_min = 100, # A scalar integer representing the minimal length of the sequences considered.
  l_max = 500, # A scalar integer representing the maximal length of the sequences considered.
  keepPrimer = TRUE) # A boolean value, if you want to keep the primers with the sequences or not.
```
If the database is a very large file, it is possible that the function trimBase won't be able to load it without crashing. In this case you can use the function **trimBasePatPil**. You have to give the path to two more files that represent the primers. The format of the file must be *.txt* and have the following configuration. (**Wobble nucleotide is not allowed in these two files, onyl A, C, T and G**)

``` r
AAACTCAAAGAAATTGACGG
AAACTTAAAGAAATTGACGG
AAACTCAAATAAATTGACGG
AAACTTAAATAAATTGACGG
...
```

``` r
trimBasePatPil(fastaPath, # path to the reference base
  outputFasta, # path to the output
  forwardPath, # path to the forward primer
  reversePath, # path to the reverse primer
  l_min = 100, # A scalar integer representing the minimal length of the sequences considered.
  l_max = 500, # A scalar integer representing the maximal length of the sequences considered.
  keepPrimer = TRUE)  # A boolean value, if you want to keep the primers with the sequences or not.
```


The PR2 database https://github.com/pr2database/pr2database as its own function which load the last reference database.


``` r
trimBasePR2(pathFile # path to the output
  primerForward, # The character string representing your forward primer.
  primerReverse, # The character string representing your reverse primer.
  trim = 0, # A scalar integer representing the number of nucleotide that you want allowed to be trimmed on the primers.
  l_min = 100, # A scalar integer representing the minimal length of the sequences considered.
  l_max = 500, # A scalar integer representing the maximal length of the sequences considered.
  keepPrimer = TRUE) # A boolean value, if you want to keep the primers with the sequences or not.
```


## Utils

Some functions that could be useful for some treatments.

### quality check
The quality check currently implemented evaluating the expected error in a sliding window and discarding sequences with more than percentage of error in the worst quality window http://taraoceans.sb-roscoff.fr/EukDiv/.

**IMPORTANT** : sequences will be appended to the output file. Hence you should erase your file if your would like to recall the function or be sure that the output file does not exist.

``` r
call.qualCheck(fastqPath, # input fastq files
  outputFasta, # output fasta file
  t = 0.01, # expected error
  s = 50, # sligind window
  m = 60) # minimum sequence length
```

### Remove 'N'

This function simply remove sequences of a fasta or a fastq files that contains a nucleotide 'N'.

**IMPORTANT** : sequences will be appended to the output file. Hence you should erase your file if your would like to recall the function or be sure that the output file does not exist.


* **fasta**

``` r
fastaPath <- ".../file.fasta"
outputFasta <- ".../fileWithoutN.fasta"
call.RemoveNfasta(fastaPath,outputFasta)
```
* **fastq**

``` r
fastqPath <- ".../file.fastq"
outputFastq <- ".../fileWithoutN.fastq"
call.RemoveNfastq(fastaPath,outputFastq)
```

### rmSmallSeq

This function simply removes the sequences of a fasta or a fastq files that are smaller than a fixed integer.

**IMPORTANT** : sequences will be appended to the output file. Hence you should erase your file if your would like to recall the function or be sure that the output file does not exist.

* **fasta**

``` r
fastaPath <- ".../file.fasta"
outputFasta <- ".../fileWithoutN.fasta"
call.rmSmallSeqfasta(fastaPath,
	outputFasta,
	sizemin = 80) # minimum size
```

* **fastq**

``` r
fastqPath <- ".../file.fastq"
outputFastq <- ".../fileWithoutN.fastq"
call.rmSmallSeqfastq(fastqPath,
	outputFastq,
	sizemin = 80)
```

### call.D_simple_tag

**IMPORTANT** : sequences will be appended to the output files. Hence you should erase your files if your would like to recall the function or be sure that the output file does not exist.

``` r
call.D_simple_tag(fastqPath, # A character string containing the path to the fastq file. The extenstion must be .fastq
  outputFolder, # A character string containing the path to the output folder.
  barcodePath, # A character string containing the path to the barcode file. The extension must be a .txt
  mismatch = TRUE) # A boolean value, if you allow one mismatch or not.
```

### call.D_double_tag

**IMPORTANT** :  sequences will be appended to the output files. Hence you should erase your files if your would like to recall the function or be sure that the output file does not exist.

``` r
call.D_double_tag(fastqPath, # A character string containing the path to the fastq file. The extenstion must be .fastq.
  outputFolder, # A character string containing the path to the output folder.
  bF, # A character string containing the path to the forward barcodes file. The extension must be a .txt.
  bR, # A character string containing the path to the reverse barcodes file. The extension must be a .txt.
  pF, # A character string containing the path to the forward primers file. The extension must be a .txt.
  pR, # A character string containing the path to the reverse primers file. The extension must be a .txt.
  mismatch = FALSE) # A boolean value, if you allow one mismatch or not.
```
