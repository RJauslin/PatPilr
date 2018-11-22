#' preTreatment
#'
#' Function that apply a pre-treatment on the fasq file R1 and R2.
#'
#' @param pathFolder A character string containing the path where the program will work.  It should contains the two *.fastq file with R1 and R2 inside the name.
#' @param m A scalar value that represent the minimum required overlap length between two reads to provide a confident overlap.  Default 10.
#' @param M A scalar value that represent the maximum overlap length expected in approximately 90% of read pairs. Default 100.
#' @param x A scalar value that represent the maximum allowed ratio between the number of mismatched base pairs and the overlap length. Default 0.25.
#' @param t A scalar value that represent the number of worker threads. Default t = 4.
#' @param mismatch A boolean value if one mismatch is allowed inside the barcode. Default = FALSE
#' @param err A scalar that represent the percentage of error allowed in the sliding window. Default = 0.01.
#' @param slide A scalar that represent the size of the sliding window. Default = 50.
#' @param minlength A scalar that represent the minimum size of the sequence to be keep. Default = 60.
#'
#' @details
#'
#' The pathFolder argument should contain : namefile_R1.fastq namefile_r2.fastq barcode.txt. The function create the different folder by its own.
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
#' pathFolder <- "/home/raphael/Documents/Rpackage/pipelineR/inst/PatPil/test/testRpackage/"
#' pathFolder <- "M:/R/PatPil-master/Rpackage/pipeline2R/inst/PatPil/test/"
#' preTreatment(pathFolder)
#' }
preTreatment <- function(pathFolder,
                         m = 10,
                         M = 100,
                         x = 0.25,
                         t = 4,
                         mismatch = FALSE,
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

  namefile <- do.call(rbind,strsplit(filesPAIREND,"_R"))[1,1]
  R1 <- file.path(pathFolder,filesPAIREND[which(grepl("R1",filesPAIREND))],fsep = "")
  R2 <- file.path(pathFolder,filesPAIREND[which(grepl("R2",filesPAIREND))],fsep = "")

  if(!dir.exists(file.path(pathFolder,"merged",fsep ="" ))){
    dir.create(file.path(pathFolder,"merged",fsep ="" ))
  }





  system2(pathFlash,args = c('-m',m,
                             '-M',M,
                             '-x',x,
                             '-t',t,
                             '-d',file.path(pathFolder,"merged",fsep ="" ),
                             '-o',namefile,
                             R1,
                             R2))


  #############################
  #   DEMULTIPLEXING
  #############################

  fileBarcode <- file.path(pathFolder,files[which(grepl("barcode",files))],fsep = "")

  ## CREATE DEMULTIPLEX FOLDER

  pathDemulti <- file.path(pathFolder,"demultiplex/",fsep ="" )

  if(!dir.exists(pathDemulti)){
    dir.create(pathDemulti)
  }




  pathPatPil <- system.file("PatPil", package = "PatPilr")
  pathPatPil <- paste(pathPatPil,"/PatPil",sep = "")



 call.D_simple_tag(fastq_path = file.path(pathFolder,"merged/",namefile,".extendedFrags.fastq",fsep= ""),
                    outputFolder = pathDemulti,
                    barcode_path = fileBarcode,
                    mismatch = TRUE)

  #############################
  #   CLEANING
  #############################

  pathClean <- file.path(pathFolder,"clean/",fsep ="" )
  if(!dir.exists(pathClean)){
    dir.create(pathClean)
  }



  filesDemultiplexed <- list.files(file.path(pathFolder,"/demultiplex"))
  filesDemultiplexed <- filesDemultiplexed[-which(filesDemultiplexed == "unknown.fastq")]
  prefixfile <- do.call(rbind,strsplit(filesDemultiplexed,split = "[.]"))[,1]
  ext <- unique(do.call(rbind,strsplit(filesDemultiplexed,split = "[.]"))[,2])

  for(i in 1:length(prefixfile)){
    call.qualCheck(fastq_path = file.path(pathFolder,"demultiplex/",prefixfile[i],".",ext,fsep = ""),
                   outputFolder = file.path(pathFolder,"clean/",prefixfile[i],".fa",fsep = ""),
                   t = 0.01,
                   s = slide,
                   m = minlength)
  }


}

