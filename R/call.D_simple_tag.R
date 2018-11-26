#' call.D_simple_tag
#'
#' Function that call the simple tag demultiplexing program of the tool PatPil.
#'
#'
#' @param fastq_path A character string containing the path to the fastq file. The extenstion must be *.fastq
#' @param outputFolder A character string containing the path to the output folder.
#' @param barcode_path A character string containing the path to the barcode file. The extension must be a *.txt
#' @param mismatch A boolean value, if you allow one mismatch or not.
#'
#' @return Nothing for now (but work on the file)
#' @export
#'
#' @examples
#' \dontrun{
#'   fastq_path<-"./inst/PatPil_source/test/R1.fastq"
#'   outputFolder <- "./inst/PatPil_source/test/test_D_simple_tag/R1.fastq"
#'   barcode_path <- "./inst/PatPil_source/test/barcodesV9test.txt"
#'   call.D_simple_tag(fastq_path,outputFolder,barcode_path)
#' }
call.D_simple_tag <- function(fastq_path,
                             outputFolder,
                             barcode_path,
                             mismatch = TRUE){

  info <- Sys.info()
  path <- system.file("PatPil", package = "PatPilr")
  if(info[1] == "Linux"){
    path <- paste(path,"/PatPil",sep = "")
  }else if(info[1] == "Windows"){
    path <- paste(path,"/PatPil.exe",sep = "")
  }

  if(missing(fastq_path)){
    stop("You have to give the path where you put your files")
  }
  pathIni <- getwd()
  #path <- system.file("PatPil", package = "PatPilr")
  #path <- paste(path,"/PatPil",sep = "")
  if(mismatch == TRUE){
    system2(path,args = c('D_simple_tag','-f',fastq_path,'-o',outputFolder,'-b',barcode_path,'-mismatch'))
  }else{
    system2(path,args = c('D_simple_tag','-f',fastq_path,'-o',outputFolder,'-b',barcode_path))
  }

  setwd(pathIni)
}
