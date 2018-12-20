#' pr2Tofasta
#'
#' Function that install and load the PR2 database \url{https://github.com/pr2database/pr2database}
#'
#' Check \code{\link{trimBasePR2}} if you would like trimmed database PR2.
#'
#' @param file optional path to an output file to write the PR2 as a fasta file.
#'  If ommited the database is only loaded in the working environment.
#'
#' @return a \code{\link{list}} that contains the pr2 full
#'
#' @export
#'
#' @importFrom seqinr write.fasta
#' @importFrom devtools install_github
#' @examples
#' \dontrun{
#' pr2full <-
#' pr2Tofasta("/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testPR2/PR2.fasta")
#' }
#
 pr2Tofasta <- function(file){
   devtools::install_github("pr2database/pr2database")
   if (requireNamespace("pr2database", quietly = TRUE)) {
     pr2 <- as.data.frame(pr2database::pr2)
   }

   name <- paste(pr2$pr2_accession,
                paste(pr2$kingdom,pr2$supergroup,pr2$division,pr2$class,pr2$order,pr2$family,pr2$genus,pr2$species,sep ="|"),
                sep ="|")
   seqPR2 <- as.list(pr2$sequence)
   names(seqPR2) <- name

   if(missing(file)){
     cat("PR2 full not saved")
   }else{
      seqinr::write.fasta(sequences = seqPR2,names = name,file.out = file,nbchar = 100000)
   }
   return(seqPR2)

}

