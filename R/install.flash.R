#' Install the program FLASH
#'
#' call the command make to compile the program in Linux environement.
#'
#' @details
#' FLASH (Fast Length Adjustment of SHort reads) is a very fast
#' and accurate software tool to merge paired-end reads
#' from next-generation sequencing experiments.
#'
#' source : \url{http://ccb.jhu.edu/software/FLASH/}
#'
#' @return Nothing
#' @export
install.flash <- function(){
  info <- Sys.info()
  if(info[1] == "Linux"){
    filIni <- getwd()
    path <- system.file("flash", package = "PatPilr")
    setwd(path)
    system2("make")
    setwd(filIni)
  }else if(info[1] == "Windows"){
    filIni <- getwd()
    path <- system.file("flash", package = "PatPilr")
    setwd(path)
    system2("make",args = c('-f','Makefile.win'))
    setwd(filIni)
  }
}
