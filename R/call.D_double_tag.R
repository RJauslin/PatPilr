#' call D_double_tag
#'
#' This function calls the double tag demultiplexing program of the tool PatPil.
#'
#' @param fastqPath A character string containing the path to the fastq file. The extenstion must be .fastq.
#' @param outputFolder A character string containing the path to the output folder.
#' @param bF A character string containing the path to the forward barcodes file. The extension must be a .txt.
#' @param bR A character string containing the path to the reverse barcodes file. The extension must be a .txt.
#' @param pF A character string containing the path to the forward primers file. The extension must be a .txt.
#' @param pR A character string containing the path to the reverse primers file. The extension must be a .txt.
#' @param mismatch A boolean value, if you allow one mismatch or not.
#'
#' @details
#'
#' The demultiplexing program will check that the sequences are in configuration :
#' \itemize{
#' \item forwardTag - primerForward - Seq - primerReverse - reverseTag
#' }
#'
#' Hence you should verifiy that your primerReverse and reverseTag are in the right direction
#' and so possibly you might need to reverse complement your primer sequences.
#'
#' IMPORTANT : if this function is called in an other manners than by the function \link{preTreatment},
#' then the function append the files.
#' Hence you should erase your files if your would like to recall the function.
#'
#'
#' @return Nothing, but work on the files
#' @export
#' @examples
#' \dontrun{
#'
#' fastqPath<-".../test/R1.fastq"
#' outputFolder <- ".../test_D_double_tag/"
#' bF <- "..../forwardtag.txt"
#' bR <- "..../reversetag.txt"
#' pR <- "..../primerreverse.txt"
#' pF <- "..../primerforward.txt"
#'
#' fastqPath <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testDemux/D_double_tag/extendedFrags.fastq"
#' outputFolder <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testDemux/D_double_tag/demultiplex/"
#' bF <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testDemux/D_double_tag/forwardtag.txt"
#' bR <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testDemux/D_double_tag/reversetag.txt"
#' pF <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testDemux/D_double_tag/primerforward.txt"
#' pR <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testDemux/D_double_tag/primerreverse.txt"
#'
#'
#' call.D_double_tag(fastqPath,
#'      outputFolder,
#'      bF,
#'      bR,
#'      pF,
#'      pR,
#'      TRUE)
#'
#'}
call.D_double_tag <- function(fastqPath,
                              outputFolder,
                              bF,
                              bR,
                              pF,
                              pR,
                              mismatch = FALSE){
  if(file.exists(fastqPath)){
    info <- Sys.info()
    path <- system.file("PatPil", package = "PatPilr")
    if(info[1] == "Linux"){
      path <- paste(path,"/PatPil",sep = "")
    }else if(info[1] == "Windows"){
      path <- paste(path,"/PatPil.exe",sep = "")
    }

    if(mismatch == TRUE){
      system2(path,args = c('D_double_tag',
                            '-f',fastqPath,
                            '-o',outputFolder,
                            '-bF',bF,
                            '-bR',bR,
                            '-pF',pF,
                            '-pR',pR,
                            '-mismatch'))
    }else{
      system2(path,args = c('D_double_tag','-f',fastqPath,'-o',outputFolder,
                            '-bF',bF,
                            '-bR',bR,
                            '-pF',pF,
                            '-pR',pR))
    }
  }else{
    stop("call.D_double_tag : the file of the argument fastqPath does not exist...")
  }
}
