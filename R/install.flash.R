#' Install the program FLASH
#'
#' call the command "make" to compile the program in Linux environement.
#'
#' @details
#' FLASH (Fast Length Adjustment of SHort reads) is a very fast
#' and accurate software tool to merge paired-end reads
#' from next-generation sequencing experiments.
#'
#' source : http://ccb.jhu.edu/software/FLASH/
#'
#' @return Nothing
#' @export
install.flash <- function(){
  info <- Sys.info()
  if(info[1] == "Linux"){
    filIni <- getwd()
    path <- system.file("flash", package = "pipelineR")
    setwd(path)
    system2("make")
    setwd(filIni)
  }else if(info[1] == "Windows"){
    print("Already installed in the package for the Windows OS")
  }
}
