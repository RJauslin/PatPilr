#' call.qualCheck
#'
#' Function that call the quality check program of the tool PatPil.
#'
#' @param fastq_path A character string containing the path to the fastq file. The extenstion must be *.fastq
#' @param outputFolder A character string containing the path to the output folder with the namefile. The extension must be *.fa
#' @param t A scalar that represent the percentage of error allowed in the sliding window. Default = 0.01.
#' @param s A scalar that represent the size of the sliding window. Default = 50.
#' @param m A scalar that represent the minimum size of the sequence to be keep. Default = 60.
#'
#' @details
#'
#' See the \url{http://taraoceans.sb-roscoff.fr/EukDiv/} for more informations on how the quality check is performed.
#'
#' @return Nothing, but it work on the called file.
#' @export
#'
#' @examples
#'
#' \dontrun{
#'   fastq_path<-"./inst/PatPil_source/test/R1.fastq"
#'   outputFolder <- "./inst/PatPil_source/test/test_D_simple_tag/R1.fastq"
#'   barcode_path <- "./inst/PatPil_source/test/barcodesV9test.txt"
#'   call.D_simple_tag(fastq_path,outputFolder,barcode_path)
#'
#' }
#'
#'
call.qualCheck <- function(fastq_path,
                           outputFolder,
                           t = 0.01,
                           s = 50,
                           m = 60){

  pathIni <- getwd()
  path <- system.file("PatPil", package = "PatPilr")
  path <- paste(path,"/PatPil",sep = "")

  system2(path,args = c('qualCheck','-f',fastq_path,'-o',outputFolder,'-t',t,'-s',s,'-m',m))


  setwd(pathIni)
}
