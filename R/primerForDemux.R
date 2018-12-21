#' primer forward and reverse demultiplexing
#'
#' internal function that create forwardtag.txt and reversetag.txt for the double tag demultiplexing.
#'
#' @param pathFile A character string that represent path where to the folder on which there is primer.txt
#'
#' @return Nothing, but write the two need files.
#'
#' @importFrom utils read.delim
#' @importFrom utils write.table
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
