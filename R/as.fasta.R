#' as.fasta
#'
#' Transform output from CheckPrimer to a list that can be write with write.fasta
#'
#' @param pr2full
#' @param pr2clean
#'
#' @return
#' @export
as.fasta <- function(pr2full,pr2clean){
  pr2 <- list()
  name <- names(pr2full)[pr2clean$Fasta$index]
  pr2 <- as.list(as.character(pr2clean$Fasta$seq))
  names(pr2) <- name
  return(pr2)
}
