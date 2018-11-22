#' install the program PatPil
#'
#' source : https://github.com/Rjauslin/PatPil
#'
#' @export
#'
install.PatPil <- function(){
  info <- Sys.info()
  if(info[1] == "Linux"){
    filIni <- getwd()
    path <- system.file("PatPil", package = "pipelineR")
    setwd(path)
    system2("make")
    setwd(filIni)
  }else if(info[1] == "Windows"){
    filIni <- getwd()
    path <- system.file("PatPil", package = "pipelineR")
    setwd(path)
    system2("make",args = c('-f','makefile.win'))
    setwd(filIni)
  }
}