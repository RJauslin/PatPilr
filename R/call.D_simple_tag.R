#' call D_simple_tag
#'
#' This function calls the simple tag demultiplexing program of the tool PatPil.
#'
#' @param fastqPath A character string containing the path to the fastq file. The extenstion must be .fastq
#' @param outputFolder A character string containing the path to the output folder.
#' @param barcodePath A character string containing the path to the barcode file. The extension must be a .txt
#' @param mismatch A boolean value, if you allow one mismatch or not.
#'
#'
#' @details
#' The demultiplexing simple tag program will check that we are in the configuration :
#' \itemize{
#' \item forwardTag - Seq
#' }
#'
#' Hence you might have some primer in your sequences but the program will only cares about the tags.
#' If you would like to trim your primer see ...
#'
#'
#' IMPORTANT : if this function is called in an other manners than by the function \link{preTreatment},
#' then the function append the files.
#' Hence you should erase your files if your would like to recall the function.
#'
#'
#'
#' @return Nothing, but work on the files
#' @export
#'
#' @examples
#' \dontrun{
#'   fastqPath<-".../test/R1.fastq"
#'   outputFolder <- ".../test_D_simple_tag/R1.fastq"
#'   barcodePath <- ".../test/barcodesV9test.txt"
#'
#' fastqPath <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testDemux/D_simple_tag/extendedFrags.fastq"
#' outputFolder <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testDemux/D_simple_tag/demultiplex/"
#' barcodePath <- "/home/raphael/Documents/PatPilr_source/
#' testPipeline/testpreTreatment/testDemux/D_simple_tag/barcodes.txt"
#'
#'   call.D_simple_tag(fastqPath,outputFolder,barcodePath)
#' }
call.D_simple_tag <- function(fastqPath,
                             outputFolder,
                             barcodePath,
                             mismatch = TRUE){
  if(file.exists(fastqPath)){ #check if fastq files exists
    info <- Sys.info()
    path <- system.file("PatPil", package = "PatPilr")
    if(info[1] == "Linux"){
      path <- paste(path,"/PatPil",sep = "")
    }else if(info[1] == "Windows"){
      path <- paste(path,"/PatPil.exe",sep = "")
    }

    if(mismatch == TRUE){
      system2(path,args = c('D_simple_tag','-f',fastqPath,'-o',outputFolder,'-b',barcodePath,'-mismatch'))
    }else{
      system2(path,args = c('D_simple_tag','-f',fastqPath,'-o',outputFolder,'-b',barcodePath))
    }
  }else{
    stop("call.D_simple_tag : the file of the argument fastqPath does not exist...")
  }
}
