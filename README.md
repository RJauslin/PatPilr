# PatPilr (dev branch)
Implementation of the tools PatPil in R

## Current version
* Current version : 1.1.6
* Last update : 2018-12-20


## Installation

* Linux

``` r
install.packages("devtools")
devtools::install_github("Rjauslin/PatPilr")
library(PatPilr)
```

* Windows

In order to get the program PatPil, you need to install Rtools. Go to the URL https://cran.r-project.org/bin/windows/Rtools/ and choose Rtools35.exe. Foloow the setpu instructions and when given the option to edit your PATH, take it. 


``` r
install.packages("devtools")
devtools::install_github("Rjauslin/PatPilr")
library(PatPilr)
```

## preTreatment

This function merges, demultiplex, and clean your fastq files. You are supposed to put only the fastq files specified by the ..._R1.fastq, ..._R2.fastq and the information needed for the demultiplexing.



``` r
#Linux
pathFolder <- "/home/raphael/Documents/......./working_directory/"
#Windows
pathFolderWindows <- "C:/Users/raphael/......./working_directory/"

preTreatment(pathFolder,
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
You have to put in your working directory a file called **barcode.txt**. It is really important that the barcode file have the right format.

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

## Dereplication

``` r

Dereplicate <- function(pathFolder,
  within = 3,
  between = 2)

```

