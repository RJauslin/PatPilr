#' install the program PatPil
#'
#' source : \url{https://github.com/Rjauslin/PatPil}
#'
#' @export
install.PatPil <- function(){
  info <- Sys.info()
  if(info[1] == "Linux"){
    filIni <- getwd()
    path <- system.file("PatPil", package = "PatPilr")
    setwd(path)
    system2("make")
    setwd(filIni)
  }else if(info[1] == "Windows"){
    filIni <- getwd()
    path <- system.file("PatPil", package = "PatPilr")
    setwd(path)
    system2("make",args = c('-f','makefile.win'))
    setwd(filIni)
  }
}
