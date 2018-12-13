#' call.RemoveNfasta
#'
#' call RemoveNfasta function of the PatPil program.
#'
#' @param fastaPath path to the fasta file
#' @param outputFasta path to the output fasta file
#'
#' @details
#'
#' This function applies the RemoveNfasta tools of the PatPil program.
#' It simply removes the sequences that contains at least one nucleotide 'N' .
#'
#' @return Nothing
#' @export
#'
#' @examples
#' \dontrun{
#' fastaPath <- ".../fastaTest.fa"
#' outputFasta <- ".../fastaTest_N.fa"
#' call.RemoveNfasta(path,outputFolder)
#' }
call.RemoveNfasta <- function(fastaPath,
                              outputFasta){
  info <- Sys.info()
  path <- system.file("PatPil", package = "PatPilr")
  if(info[1] == "Linux"){
    path <- paste(path,"/PatPil",sep = "")
  }else if(info[1] == "Windows"){
    path <- paste(path,"/PatPil.exe",sep = "")
  }

  system2(path,args = c('RemoveNfasta',
                        '-f',fastaPath,
                        '-o',outputFasta))

}
