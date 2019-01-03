#' call RemoveN
#'
#' This function calls the RemoveN program of the tool PatPil.
#'
#' @param fastqPath path to the fastq file.
#' @param outputFastq path to the output fastq file.
#'
#' @details
#'
#' This function applies the RemoveN tools of the PatPil program.
#' It simply removes the sequences that contains at least one nucleotide 'N'.
#'
#' @return Nothing, but work on the file.
#' @export
#'
#' @examples
#' \dontrun{
#' fastqPath <- ".../fileTest.fastq"
#' fastqPath <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testRemoveNfastq/unknown.fastq"
#' outputFastq <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testRemoveNfastq/unknown_N.fastq"
#' call.RemoveNfastq(fastqPath,outputFastq)
#' }
call.RemoveNfastq <- function(fastqPath,
                              outputFastq){

  if(file.exists(fastqPath)){ #check if fasta files exists
    info <- Sys.info()
    path <- system.file("PatPil", package = "PatPilr")
    if(info[1] == "Linux"){
      path <- paste(path,"/PatPil",sep = "")
    }else if(info[1] == "Windows"){
      path <- paste(path,"/PatPil.exe",sep = "")
    }

    system2(path,args = c('RemoveN',
                          '-f',fastqPath,
                          '-o',outputFastq))
  }else{
    stop("call.RemoveNfastq : the file of the argument fastqPath does not exist...")
  }
}
