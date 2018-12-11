#' as.fasta
#'
#' Internal function that is used in \code{\link{trimBasePR2}}.
#'
#' Transform output from \code{\link{CheckPrimer}} to
#' a list that can be write with \code{\link[seqinr:write.fasta]{write.fasta}}
#'
#' @param pr2full the full database (as.list) pr2
#' @param pr2clean the cleaned database (as.list) pr2
#'
#' @return the cleaned database in the right format
as.fasta <- function(pr2full,pr2clean){
  pr2 <- list()
  name <- names(pr2full)[pr2clean$Fasta$index]
  pr2 <- as.list(as.character(pr2clean$Fasta$seq))
  names(pr2) <- name
  return(pr2)
}
