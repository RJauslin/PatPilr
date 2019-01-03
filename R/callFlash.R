#' call the program FLASH
#'
#' Function that call the FLASH program. \url{https://ccb.jhu.edu/software/FLASH/}.
#'
#' @param outputFolder A character string containing the path to the output folder.
#' @param fastq1 A character string containing the path to the R1 file.
#' @param fastq2 A character string containing the path to the R2 file.
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
#' \dontrun{
#'   outputFolder <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testFlash/"
#'   fastq1 <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testFlash/PlateVI_R1.fastq"
#'   fastq2 <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testFlash/PlateVI_R2.fastq"
#'   callFlash(outputFolder,fastq1,fastq2)
#' }
callFlash <- function(outputFolder,
                      fastq1,
                      fastq2,
                      m = 10,
                      M = 100,
                      x = 0.25,
                      t = 4){
  install.flash()
  info <- Sys.info()
  pathFlash <- system.file("flash", package = "PatPilr")

  if(info[1] == "Linux"){
    pathFlash <- paste(pathFlash,"/flash",sep = "")
  }else if(info[1] == "Windows"){
    pathFlash <- paste(pathFlash,"/flash.exe",sep = "")
  }

  if(file.exists(fastq1) || file.exists(fastq2)){

    system2(pathFlash,args = c('-m',m,
                               '-M',M,
                               '-x',x,
                               '-t',t,
                               '-d',outputFolder,
                               fastq1,
                               fastq2))
  }else{
    stop("callFlash : the file of the argument fastq1 or fastq2 does not exist...")
  }

}
