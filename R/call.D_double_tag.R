#' call.D_double_tag
#'
#' Function that call the double tag demultiplexing program of the tool PatPil.
#'
#' @param fastq_path A character string containing the path to the fastq file. The extenstion must be .fastq
#' @param outputFolder A character string containing the path to the output folder.
#' @param bF A character string containing the path to the barcode forward file. The extension must be a .txt
#' @param bR A character string containing the path to the barcode reverse file. The extension must be a .txt
#' @param pF A character string containing the path to the primer forward file. The extension must be a .txt
#' @param pR A character string containing the path to the primer reverse file. The extension must be a .txt
#' @param mismatch A boolean value, if you allow one mismatch or not.
#'
#' @return Nothing for now (but work on the file)
#' @export
call.D_double_tag <- function(fastq_path,
                              outputFolder,
                              bF,
                              bR,
                              pF,
                              pR,
                              mismatch = FALSE){

  info <- Sys.info()
  path <- system.file("PatPil", package = "PatPilr")
  if(info[1] == "Linux"){
    path <- paste(path,"/PatPil",sep = "")
  }else if(info[1] == "Windows"){
    path <- paste(path,"/PatPil.exe",sep = "")
  }

  pathIni <- getwd()
  #path <- system.file("PatPil", package = "PatPilr")
  #path <- paste(path,"/PatPil",sep = "")
  if(mismatch == TRUE){
    system2(path,args = c('D_double_tag',
                          '-f',fastq_path,
                          '-o',outputFolder,
                          '-bF',bF,
                          '-bR',bR,
                          '-pF',pF,
                          '-pR',pR,
                          '-mismatch'))
  }else{
    system2(path,args = c('D_double_tag','-f',fastq_path,'-o',outputFolder,
                          '-bF',bF,
                          '-bR',bR,
                          '-pF',pF,
                          '-pR',pR))
  }

  setwd(pathIni)

}
