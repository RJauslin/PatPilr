#' Create the cleaned database
#'
#' Internal function that is used in \code{\link{trimBasePR2}} and \code{\link{trimBase}}.
#' Transform output from \code{\link{CheckPrimer}} to
#' a list that can be write with \code{\link[seqinr:write.fasta]{write.fasta}}.
#'
#' @param full A list that represent the full database.
#' @param clean A list that represent the cleaned database. Output from \code{\link{CheckPrimer}}.
#'
#' @return the cleaned database in the right format
as.fasta <- function(full,clean){
  base <- list()
  name <- names(full)[clean$Fasta$index]
  base <- as.list(as.character(clean$Fasta$seq))
  names(base) <- name
  return(base)
}
