#' call rmSmallSeqfastq
#'
#' This function calls the rmSmallSeqfastq program of the tool PatPil.
#'
#' @param fastqPath A character string that represent the path to the fastq file.
#' @param outputFastq A character string that represent the path to the output fastq file.
#' @param sizemin A scalar integer to selected the minimum size.
#'
#' @details
#'
#' This function applies the rmSmallSeq tools of the PatPil program.
#' It simply removes the sequences that are smaller than a fixed integer.
#'
#' @return Nothing
#' @export
#'
#' @examples
#' \dontrun{
#' fastqPath <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testrmSmallSeqfastq/fastqTest.fastq"
#' outputFastq <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testrmSmallSeqfastq/fastqTest_rm.fastq"
#' call.rmSmallSeqfastq(fastqPath,outputFastq,100)
#' }
call.rmSmallSeqfastq <- function(fastqPath,
                                 outputFastq,
                                 sizemin = 80){

  if(file.exists(fastqPath)){ #check if fasta files exists
    info <- Sys.info()
    path <- system.file("PatPil", package = "PatPilr")
    if(info[1] == "Linux"){
      path <- paste(path,"/PatPil",sep = "")
    }else if(info[1] == "Windows"){
      path <- paste(path,"/PatPil.exe",sep = "")
    }

    system2(path,args = c('rmSmallSeq',
                          '-f',fastqPath,
                          '-o',outputFastq,
                          '-m',sizemin))
  }else{
    stop("call.rmSmallSeqfastq : the file of the argument fastqPath does not exist...")
  }
}
