# PatPilr (dev branch)
Implementation of the tools PatPil in R

## Current version
* Current version : 1.1.4
* Last update : 2018-12-14


## Installation

* Linux

``` r
install.packages("devtools")
devtools::install_github("Rjauslin/PatPilr")
library(PatPilr)
```

* Windows

You need to install a C++ complier. For that you have to install Rtools go to the URL https://cran.r-project.org/bin/windows/Rtools/ and choose Rtools35.exe. When given the option to edit your PATH, take it. 


``` r
install.packages("devtools")
devtools::install_github("Rjauslin/PatPilr")
library(PatPilr)
```

## preTreatment


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
