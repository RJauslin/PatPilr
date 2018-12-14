#' trimBase
#'
#' @param fastaPath A character string that represent the path to the input file (absolute path needed)
#' @param outputFasta A character string that represent the path to the output file (absolute path needed)
#' @param primerForward A character string that represent the forward primer (uncertain nucleotide allowed)
#' @param primerReverse A character string that represent the reverse primer (uncertain nucleotide allowed)
#' @param trim A value that represent the number of nucleotide that you want trim in the primer
#' @param l_min A value that represent the mininum length of the kept sequences.
#' @param l_max A value that represent the maximum length of the kept sequences.
#' @param keepPrimer A boolean value, if you want to keep the primer?
#'
#'
#' @details
#' This function will extract from the reference base the portion of interested of the sequences. Schematically we have :
#' \itemize{
#' \item SeqPart1 - primerForward - Seq - primerReverse - SeqPart2
#' }
#' @return
#' @export
#'
#' @examples
#' \dontrun{
#' fastaPath <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testPR2/utax.fasta"
#' outputFasta <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testPR2/utaxCleanKept.fasta"
#' outputFastaC <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testPR2/utaxClean.fasta"
#' primerForward <- "GTGAATCATCGAATCTTTGAA"
#' primerReverse <- "GCATATCAATAAGCGGAGGA"
#' trim <- 0
#' l_min = 60
#' l_max = 600
#' trimBase(fastaPath,outputFasta,primerForward,primerReverse,trim,l_min,l_max,TRUE)
#' trimBase(fastaPath,outputFastaC,primerForward,primerReverse,trim,l_min,l_max,FALSE)
#' }
trimBase <- function(fastaPath,
                     outputFasta,
                     primerForward = "CYGCGGTAATTCCAGCTC",
                     primerReverse =  "CRAAGAYGATYAGATACCRT",
                     trim = 0,
                     l_min = 100,
                     l_max = 500,
                     keepPrimer = TRUE){
  #LOAD database
  require(seqinr)
  database <- read.fasta(file = fastaPath,
                         as.string = TRUE,
                         forceDNAtolower = FALSE)


  #TRIM PRIMER
  comb1 <- AllPrimer(primerForward,direction="forward",trim)
  comb2 <- AllPrimer(primerReverse,direction="reverse",trim)


  databaseCleaned <- CheckPrimer(pr2 = database,
                        comb1,
                        comb2,
                        l_min,
                        l_max,
                        keepPrimer = keepPrimer)

  #TRANSFORM DATABASE
  databaseClean <- as.fasta(database,databaseCleaned)

  #WRITE THE DATABASE
  write.fasta(sequences = databaseClean,
              names = names(databaseClean),
              file.out = outputFasta,
              nbchar = 100000)


}
