#' preTreatment when the file are already demultiplexed
#'
#' Function that apply a pre-treatment on the fasq files
#'
#' @param pathFolder A character string containing the path where the program will work.  It should contains the two *.fastq file with R1 and R2 inside the name.
#' @param m A scalar value that represent the minimum required overlap length between two reads to provide a confident overlap.  Default 10.
#' @param M A scalar value that represent the maximum overlap length expected in approximately 90% of read pairs. Default 100.
#' @param x A scalar value that represent the maximum allowed ratio between the number of mismatched base pairs and the overlap length. Default 0.25.
#' @param t A scalar value that represent the number of worker threads. Default t = 4.
#' @param err A scalar that represent the percentage of error allowed in the sliding window. Default = 0.01.
#' @param slide A scalar that represent the size of the sliding window. Default = 50.
#' @param minlength A scalar that represent the minimum size of the sequence to be keep. Default = 60.
#'
#' @details
#'
#' The pathFolder argument should contain : All the namefile_R1.fastq namefile_R2.fastq
#'
#'The function create the different folder by its own.
#'
#' 1) The function will firstly apply the FLASH to merge the R1 and R2 fastq file. A folder is create named "merged" with the output of the FLASH programs
#'
#' 2) Secondly the function call the simple demultiplexing function of the tool PatPil. The main folder needs to contains a barcode.txt file such that :
#'
#' barcode TAB < nameoffile.fq >
#'
#' A folder is create named "demultiplex" which contains the demultiplexed file.
#'
#' 3) Finally, the function call the qualChek function of the tool PatPil. A folder is create named "clean" which contains the fasta files clean by the TARA quality check \url{http://taraoceans.sb-roscoff.fr/EukDiv/}.
#' @return Noting.
#' @export
#'
#' @examples
#' \dontrun{
#' pathFolder <- "/home/raphael/Documents/PatPilr_source/testPipeline/Pilonel_P6_18S/"
#' preTreatmentAlreadyDemultiplexed(pathFolder)
#' }
preTreatmentAlreadyDemultiplexed <- function(pathFolder,
                                             sep = "_R",
                                             m = 10,
                                             M = 250,
                                             x = 0.25,
                                             t = 4,
                                             err = 0.01,
                                             slide = 50,
                                             minlength = 60){


  pathIni <- getwd()
  install.flash()
  install.PatPil()
  info <- Sys.info()

  pathFlash <- system.file("flash", package = "PatPilr")
  pathPatPil <- system.file("PatPil", package = "PatPilr")

  if(info[1] == "Linux"){
    pathFlash <- paste(pathFlash,"/flash",sep = "")
    pathPatPil <- paste(pathPatPil,"/PatPil",sep = "")
  }else if(info[1] == "Windows"){
    pathFlash <- paste(pathFlash,"/flash.exe",sep = "")
    pathPatPil <- paste(pathPatPil,"/PatPil.exe",sep = "")
  }



  #############################
  #   MERGING
  #############################

  files <- list.files(pathFolder)
  filesPAIREND <- files[c(which(grepl("R1",files)),which(grepl("R2",files)))]


  namefile <- do.call(rbind,strsplit(filesPAIREND,sep))[,1]
  namefile <- unique(namefile)

  if(!dir.exists(file.path(pathFolder,"merged",fsep ="" ))){
    dir.create(file.path(pathFolder,"merged",fsep ="" ))
  }

  for( i in 1:length(namefile)){
    tmp <- filesPAIREND[which(grepl(namefile[i],filesPAIREND))]

    R1 <- tmp[which(grepl("R1",tmp))]
    R2 <- tmp[which(grepl("R2",tmp))]

    R1 <- file.path(pathFolder,R1,fsep = "")
    R2 <- file.path(pathFolder,R2,fsep = "")

    system2(pathFlash,args = c('-m',m,
                               '-M',M,
                               '-x',x,
                               '-t',t,
                               '-d',file.path(pathFolder,"merged",fsep ="" ),
                               '-o',namefile[i],
                               R1,
                               R2))
  }

  if(!dir.exists(file.path(pathFolder,"merged/extFrags",fsep ="" ))){
    dir.create(file.path(pathFolder,"merged/extFrags",fsep ="" ))
  }

  if(!dir.exists(file.path(pathFolder,"merged/histFrags",fsep ="" ))){
    dir.create(file.path(pathFolder,"merged/hFrags",fsep ="" ))
  }
  if(!dir.exists(file.path(pathFolder,"merged/notCombFrags",fsep ="" ))){
    dir.create(file.path(pathFolder,"merged/notCombFrags",fsep ="" ))
  }


 extended <- list.files(file.path(pathFolder,"merged/",fsep ="" ))
 extended <- extended[which(grepl("extendedFrags",extended))]

 histo <- list.files(file.path(pathFolder,"merged/",fsep ="" ))
 histo <- histo[which(grepl("hist",histo))]

 notComb <- list.files(file.path(pathFolder,"merged/",fsep ="" ))
 notComb <- notComb[which(grepl("notCombined",notComb))]

 for(i in 1:length(extended)){
   file.rename(from =  file.path(pathFolder,"merged/",extended[i],fsep ="" ),
               to =  file.path(pathFolder,"merged/extFrags/",extended[i],fsep ="" ))
 }

 for(i in 1:length(histo)){
   file.rename(from =  file.path(pathFolder,"merged/",histo[i],fsep ="" ),
               to =  file.path(pathFolder,"merged/hFrags/",histo[i],fsep ="" ))
 }

 for(i in 1:length(notComb)){
   file.rename(from =  file.path(pathFolder,"merged/",notComb[i],fsep ="" ),
               to =  file.path(pathFolder,"merged/notCombFrags/",notComb[i],fsep ="" ))
 }



  #############################
  #   CLEANING
  #############################

  pathClean <- file.path(pathFolder,"clean/",fsep ="" )
  if(!dir.exists(pathClean)){
    dir.create(pathClean)
  }


  filesMerged <- list.files(file.path(pathFolder,"merged/extFrags/"))

  prefixfile <- do.call(rbind,strsplit(filesMerged,split = ".extendedFrags"))[,1]
  ext <- unique(do.call(rbind,strsplit(filesMerged,split = ".extendedFrags"))[,2])

  for(i in 1:length(filesMerged)){
    call.qualCheck(fastq_path = file.path(pathFolder,"merged/extFrags/",filesMerged[i],fsep = ""),
                   outputFolder = file.path(pathFolder,"clean/",prefixfile[i],".fa",fsep = ""),
                   t = err,
                   s = slide,
                   m = minlength)
  }


}

