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
#' fastaPath <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testRemoveNfasta/fastaTest.fasta"
#' outputFasta <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testRemoveNfasta/fastaTest_N.fasta"
#' call.RemoveNfasta(fastaPath,outputFasta)
#' }
call.RemoveNfasta <- function(fastaPath,
                              outputFasta){

  if(file.exists(fastaPath)){ #check if fasta files exists
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
  }else{
    stop("call.RemoveNfasta : the file of the argument fastaPath does not exist...")
  }
}
