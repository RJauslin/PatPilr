#' trim reference database with PatPil
#'
#' In order to get some 100% of match when you assign your sequences, you have to compare with sequences that have the same "configuration".
#' Hence, you possibly need to trim your reference base with some primers.
#'
#' @param fastaPath A character string that represent the path to the input file.
#' @param outputFasta A character string that represent the path to the output file.
#' @param l_min A value that represent the mininum length of the kept sequences.
#' @param l_max A value that represent the maximum length of the kept sequences.
#' @param keepPrimer A boolean value, if you want to keep the primer?
#' @param forwardPath A character string that represent the path to the forward primer.
#' @param reversePath A c haracter string that represent the path to the reverse primer.
#'
#' @details
#' This function will extract from the reference base the portion of interested of the sequences. Schematically we have :
#' \itemize{
#' \item SeqPart1 - primerForward - Seq - primerReverse - SeqPart2
#' }
#'
#' See \link{AllPrimer} or \link{primerForDemux} if you would like to extract all primers with some uncertain nucleotide.
#'
#' @return
#' @export
#'
#' @examples
#' \dontrun{
#'
#'
#' fastaPath <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testPR2/utax.fasta"
#' outputFasta <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testPR2/utaxCleanKeptPatPil.fasta"
#' outputFastaC <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testPR2/utaxCleanPatPil.fasta"
#'
#' forwardPath <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testPR2/forwardUTAX.txt"
#' reversePath <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testPR2/reverseUTAX.txt"
#'

#'
#'
#' fastaPath <- "/home/raphael/Documents/Cadavre/fungi_bacteria/SILVA/SILVA132SSURefNr99.fasta"
#' outputFasta <- "/home/raphael/Documents/Cadavre/fungi_bacteria/SILVA/SILVA132SSURefNr99CLEANED.fasta"
#' forwardPath <- "/home/raphael/Documents/Cadavre/fungi_bacteria/SILVA/primer1.txt"
#' reversePath <- "/home/raphael/Documents/Cadavre/fungi_bacteria/SILVA/primer2.txt"
#' l_min = 100
#' l_max = 3500
#' trimBasePatPil(fastaPath,outputFasta,forwardPath,reversePath,l_min,l_max,TRUE)
#'
#'
#'
#'
#' trimBasePatPil(fastaPath,outputFastaC,forwardPath,reversePath,l_min,l_max,FALSE)
#' }
trimBasePatPil <- function(fastaPath,
                     outputFasta,
                     forwardPath,
                     reversePath,
                     l_min = 100,
                     l_max = 500,
                     keepPrimer = TRUE){

  if(file.exists(fastaPath)){ #check if fasta files exists
    info <- Sys.info()
    path <- system.file("PatPil", package = "PatPilr")
    if(info[1] == "Linux"){
      path <- paste(path,"/PatPil",sep = "")
    }else if(info[1] == "Windows"){
      path <- paste(path,"/PatPil.exe",sep = "")
    }

    if(keepPrimer == TRUE){
      system2(path,args = c('trimPrimer',
                            '-f',fastaPath,
                            '-o',outputFasta,
                            '-primer1',forwardPath,
                            '-primer2',reversePath,
                            '-m',l_min,
                            '-M',l_max,
                            '-keepPrimer'))
    }else{
      system2(path,args = c('trimPrimer',
                            '-f',fastaPath,
                            '-o',outputFasta,
                            '-primer1',forwardPath,
                            '-primer2',reversePath,
                            '-m',l_min,
                            '-M',l_max))
    }

    system2(path,args = c('uniqueFasta',
                          '-f',outputFasta,
                          '-o',outputFasta))

  }else{
    stop("trimPrimer : the file of the argument fastaPath does not exist...")
  }
}
