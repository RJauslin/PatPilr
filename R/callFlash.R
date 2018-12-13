#' callFlash
#'
#' Function that call the FLASH program. \url{https://ccb.jhu.edu/software/FLASH/}.
#'
#' @param file_path A character string containing the path to the fastq file. The extenstion must be .fastq
#' @param fastq1 A character string containing the path to the output folder with the namefile.
#'  The extenstion must be .fastq and contains R1.
#' @param fastq2 A character string containing the path to the output folder with the namefile.
#'  The extenstion must be .fastq and contains R2.
#' @param m A scalar value that represent the minimum required overlap length between two reads to provide a confident overlap.
#'   Default 10.
#' @param M A scalar value that represent the maximum overlap length expected in approximately ninety percent of read pairs.
#'  Default 100.
#' @param x A scalar value that represent the maximum allowed ratio between the number of mismatched base pairs and the overlap length. Default 0.25.
#' @param t A scalar value that represent the number of worker threads. Default t = 4.
#'
#' @return Nothing.
#' @export
#'
#' @examples
#'
#' \dontrun{
#'   file_path<-"/home/raphael/Documents/David_Singer_pipeline/Pipeline2/"
#'   fastq1 <- "16.02.22_David_Singer_PlateVI_V9_R1.fastq"
#'   fastq2 <- "16.02.22_David_Singer_PlateVI_V9_R2.fastq"
#'   callFlash(file_path,fastq1,fastq2)
#' }
callFlash <- function(file_path,
                      fastq1,
                      fastq2,
                      m = 10,
                      M = 100,
                      x = 0.25,
                      t = 4){

  if(missing(file_path)){
    stop("You have to give the path where you put your files")
  }
  if(missing(fastq1) || missing(fastq2)){
    stop("You have to give the two FASTQ file name with the extension .fastq")
  }
  fastq1 <- paste(file_path,fastq1,sep = "")
  fastq2 <- paste(file_path,fastq2,sep = "")
  pathIni <- getwd()
  setwd(file_path)
  path <- system.file("flash", package = "pipelineR")
  path <- paste(path,"/flash",sep = "")
  arg1 <- paste("-m",m)
  arg2 <- paste("-M",M)
  arg3 <- paste("-x",x)
  arg4 <- paste("-t",t)
  command <- paste(path,arg1,arg2,arg3,arg4,fastq1,fastq2)
  system(command)
  setwd(pathIni)
}
