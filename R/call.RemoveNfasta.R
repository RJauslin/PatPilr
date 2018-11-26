#' call RemoveNfasta
#'
#' call RemoveNfasta function of the PatPil program.
#'
#' @param fasta_path path to the fasta file
#' @param outputFolder path to the output fasta file
#'
#' @details
#'
#' This function applies the RemoveNfasta tools of the PatPil program.
#'
#' @return Nothing
#' @export
#'
#' @examples
#' \dontrun{
#' path <- "/home/raphael/Documents/PatPilr_source/fastaTest.fa"
#' outputFolder <- "/home/raphael/Documents/PatPilr_source/fastaTest_N.fa"
#' call.RemoveNfasta(path,outputFolder)
#' }
call.RemoveNfasta <- function(fasta_path,
                              outputFolder){
  pathIni <- getwd();
  path <- system.file("PatPil", package = "PatPilr")
  path <- paste(path,"/PatPil",sep = "")

  system2(path,args = c('RemoveNfasta','-f',fasta_path,'-o',outputFolder))

  setwd(pathIni)
}
