#' call rmSmallSeqfasta
#'
#' This function calls the rmSmallSeqfasta program of the tool PatPil.
#'
#' @param fastaPath A character string that represent the path to the fasta file.
#' @param outputFasta A character string that represent the path to the output fasta file.
#' @param sizemin A scalar integer to selected the minimum size.
#'
#' @details
#'
#' This function applies the rmSmallSeqfasta tools of the PatPil program.
#' It simply removes the sequences that are smaller than a fixed integer.
#'
#' @return Nothing
#' @export
#'
#' @examples
#' \dontrun{
#' fastaPath <- ".../fastaTest.fa"
#' fastaPath <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testrmSmallSeqfasta/fastaTest.fasta"
#' outputFasta <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testrmSmallSeqfasta/fastaTest_rm.fasta"
#' call.rmSmallSeqfasta(fastaPath,outputFasta,100)
#' }
call.rmSmallSeqfasta <- function(fastaPath,
                              outputFasta,
                              sizemin = 80){

  if(file.exists(fastaPath)){ #check if fasta files exists
    info <- Sys.info()
    path <- system.file("PatPil", package = "PatPilr")
    if(info[1] == "Linux"){
      path <- paste(path,"/PatPil",sep = "")
    }else if(info[1] == "Windows"){
      path <- paste(path,"/PatPil.exe",sep = "")
    }

    system2(path,args = c('rmSmallSeqfasta',
                          '-f',fastaPath,
                          '-o',outputFasta,
                          '-m',sizemin))
  }else{
    stop("call.rmSmallSeqfasta : the file of the argument fastaPath does not exist...")
  }
}
