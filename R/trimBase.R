#' trim the primer of a reference database
#'
#' @param pathFile path to the file
#' @param trim number of nucleotide that you want possibly trim to the primer
#' @param l_min min length of the keep sequences
#' @param l_max max lenght of the keep sequences
#' @param primerForward character string that represent the forward primer
#' @param primerReverse character string that represent the reverse primer
#'
#' @return nothing but the file is created in pathFile
#' @export
#'
#'
#' @examples
#' \dontrun{
#' pathfile <- "/home/raphael/Documents/PR2.fa"
#' PR2V4(pathfile)
#' }
trimBase <- function(pathFile,
                  primerForward = "CYGCGGTAATTCCAGCTC",
                  primerReverse =  "CRAAGAYGATYAGATACCRT",
                  trim = 0,
                  l_min = 100,
                  l_max = 500){

  #GET LAST VERSION OF pr2database
  devtools::install_github("pr2database/pr2database")
  library(pr2database)
  pr2full <- pr2Tofasta()

  comb1 <- AllPrimer(primerForward,direction="forward",trim)
  comb2 <- AllPrimer(primerReverse,direction="reverse",trim)

  pr2tmp <- CheckPrimer(pr2 = pr2full,comb1,comb2,l_min,l_max)
  pr2Rstudio <- as.fasta(pr2full,pr2tmp)

  write.fasta(sequences = pr2Rstudio,
              names = names(pr2Rstudio),
              file.out = pathFile,
              nbchar = 100000)

}
