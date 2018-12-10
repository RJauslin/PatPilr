#' function used in the preTreatment for double tag
#'
#' @param pathFile the path where the folder on which there is Primer.txt
#'
#' @return Nothing
#'
#' @examples
#' \dontrun{
#'  pathFile <- "/home/raphael/Documents/PatPilr_source/testPipeline/"
#' }
#'
primerForDemux <-function(pathFile){
  Primer <- as.data.frame(read.delim(file.path(pathFile,"primer.txt",fsep ="") ,header = FALSE))
  forward <- AllPrimer(primer = as.character(Primer$V1),direction = "none",trim_nuc = 0)
  reverse <- AllPrimer(primer = as.character(Primer$V2),direction = "none",trim_nuc = 0)
  write.table(x = forward, file = file.path(pathFile,"primerforward.txt",fsep = ""),
              quote = FALSE,
              col.names = FALSE,
              row.names = FALSE)
  write.table(x = reverse, file = file.path(pathFile,"primerreverse.txt",fsep = ""),
              quote = FALSE,
              col.names = FALSE,
              row.names = FALSE)

}
