#' Trim the PR2 reference database
#'
#' This function load, trim and write the PR2 database on a selected directory. See \url{https://github.com/pr2database/pr2database}.
#'
#' @param pathFile A character string that represent the path to file (absolute path needed)
#' @param trim A value that represent the number of nucleotide that you want trim in the primer
#' @param l_min A value that represent the mininum length of the kept sequences.
#' @param l_max A value that represent the maximum length of the kept sequences.
#' @param primerForward A character string that represent the forward primer (uncertain nucleotide allowed)
#' @param primerReverse A character string that represent the reverse primer (uncertain nucleotide allowed)
#' @param keepPrimer A boolean value, if you want to keep the primer?
#'
#' @details
#' This function will extract from the PR2 the portion of interested of the sequences. Schematically we have :
#' \itemize{
#' \item SeqPart1 - primerForward - Seq - primerReverse - SeqPart2
#' }
#'
#' @return Nothing, but the file is created in pathFile.
#' @export
#'
#' @importFrom seqinr write.fasta read.fasta
#' @importFrom devtools install_github
#'
#' @examples
#' \dontrun{
#' pathfile <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testPR2/PR2CleanKept.fasta"
#' pathfile <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testPR2/PR2Clean.fasta"
#' trimBasePR2(pathfile,keepPrimer = FALSE)
#' }
trimBasePR2 <- function(pathFile,
                  primerForward = "CYGCGGTAATTCCAGCTC",
                  primerReverse =  "CRAAGAYGATYAGATACCRT",
                  trim = 0,
                  l_min = 100,
                  l_max = 500,
                  keepPrimer = TRUE){

  #GET LAST VERSION OF pr2database
  devtools::install_github("pr2database/pr2database")

  #LOAD THE DATA BASE
  pr2full <- pr2Tofasta()

  #TRIM PRIMER
  comb1 <- AllPrimer(primerForward,direction="forward",trim)
  comb2 <- AllPrimer(primerReverse,direction="reverse",trim)
  pr2tmp <- CheckPrimer(pr2 = pr2full,
                        comb1,
                        comb2,
                        l_min,
                        l_max,
                        keepPrimer = keepPrimer)

  #TRANSFORM DATABASE
  pr2Rstudio <- as.fasta(pr2full,pr2tmp)

  #WRITE THE DATABASE
  seqinr::write.fasta(sequences = pr2Rstudio,
              names = names(pr2Rstudio),
              file.out = pathFile,
              nbchar = 100000)

}
