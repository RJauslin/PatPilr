#' pr2Tofasta
#'
#' @param file chemin et nom du fichier ex: "/home/test.fasta"
#'
#' @return a file
#' @export
#'
#' @importFrom seqinr write.fasta
#' @examples
#' \dontrun{
#' pr2full <-
#' pr2Tofasta("/home/raphael/Documents/David_Singer_pipeline/Pipeline2/PR2/DB/pr2Rstudio.fa")
#' }
#
 pr2Tofasta <- function(file){
   pr2 <- as.data.frame(pr2)

  name <- paste(pr2$pr2_accession,
                paste(pr2$kingdom,pr2$supergroup,pr2$division,pr2$class,pr2$order,pr2$family,pr2$genus,pr2$species,sep ="|"),
                sep ="|")
  seqPR2 <- as.list(pr2$sequence)
  names(seqPR2) <- name

  require(seqinr)
  if(missing(file)){
    cat("No file write")
  }else{
    seqinr::write.fasta(sequences = seqPR2,names = name,file.out = file,nbchar = 100000)
  }
  return(seqPR2)
}

