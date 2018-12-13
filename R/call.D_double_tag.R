#' call.D_double_tag
#'
#' This function calls the double tag demultiplexing program of the tool PatPil.
#'
#' @param fastqPath A character string containing the path to the fastq file. The extenstion must be .fastq
#' @param outputFolder A character string containing the path to the output folder.
#' @param bF A character string containing the path to the barcode forward file. The extension must be a .txt
#' @param bR A character string containing the path to the barcode reverse file. The extension must be a .txt
#' @param pF A character string containing the path to the primer forward file. The extension must be a .txt
#' @param pR A character string containing the path to the primer reverse file. The extension must be a .txt
#' @param mismatch A boolean value, if you allow one mismatch or not.
#'
#' @return Nothing for now (but work on the file)
#' @export
#' @examples
#' \dontrun{
#' fastqPath<-".../test/R1.fastq"
#' outputFolder <- ".../test_D_double_tag/"
#' bF <- "..../forwardtag.txt"
#' bR <- "..../reversetag.txt"
#' pR <- "..../primerreverse.txt"
#' pF <- "..../primerforward.txt"
#' call.D_double_tag(fastqPath,
#'      outputFolder,
#'      bF,
#'      bR,
#'      pF,
#'      pR)}
call.D_double_tag <- function(fastqPath,
                              outputFolder,
                              bF,
                              bR,
                              pF,
                              pR,
                              mismatch = FALSE){
  if(file.exists(fastqPath)){
    info <- Sys.info()
    path <- system.file("PatPil", package = "PatPilr")
    if(info[1] == "Linux"){
      path <- paste(path,"/PatPil",sep = "")
    }else if(info[1] == "Windows"){
      path <- paste(path,"/PatPil.exe",sep = "")
    }

    if(mismatch == TRUE){
      system2(path,args = c('D_double_tag',
                            '-f',fastqPath,
                            '-o',outputFolder,
                            '-bF',bF,
                            '-bR',bR,
                            '-pF',pF,
                            '-pR',pR,
                            '-mismatch'))
    }else{
      system2(path,args = c('D_double_tag','-f',fastqPath,'-o',outputFolder,
                            '-bF',bF,
                            '-bR',bR,
                            '-pF',pF,
                            '-pR',pR))
    }
  }else{
    stop("call.D_double_tag : the file of the argument fastqPath does not exist...")
  }
}
