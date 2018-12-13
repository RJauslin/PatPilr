#' call.D_simple_tag
#'
#' Function that call the simple tag demultiplexing program of the tool PatPil.
#'
#' @param fastqPath A character string containing the path to the fastq file. The extenstion must be .fastq
#' @param outputFolder A character string containing the path to the output folder.
#' @param barcode_path A character string containing the path to the barcode file. The extension must be a .txt
#' @param mismatch A boolean value, if you allow one mismatch or not.
#'
#'
#' @details
#'
#' call the tools D_simple_tag of the program PatPil.
#' For each sequence the program check teh begining of the sequence to see at which file it belongs to.
#' Only the begining of the sequence is checked and hence no primer is needed.
#'
#'
#' @return Nothing for now (but work on the file)
#' @export
#'
#' @examples
#' \dontrun{
#'   fastqPath<-".../test/R1.fastq"
#'   outputFolder <- ".../test_D_simple_tag/R1.fastq"
#'   barcode_path <- ".../test/barcodesV9test.txt"
#'   call.D_simple_tag(fastqPath,outputFolder,barcode_path)
#' }
call.D_simple_tag <- function(fastqPath,
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

  if(mismatch == TRUE){
    system2(path,args = c('D_simple_tag','-f',fastqPath,'-o',outputFolder,'-b',barcode_path,'-mismatch'))
  }else{
    system2(path,args = c('D_simple_tag','-f',fastqPath,'-o',outputFolder,'-b',barcode_path))
  }

}
