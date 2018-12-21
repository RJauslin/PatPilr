#' call qualCheck
#'
#' This function calls the qualCheck program of the tool PatPil.
#'
#' @param fastqPath A character string containing the path to the fastq file. The extenstion must be .fastq.
#' @param outputFasta A character string containing the path to the output folder with the namefile. The extension must be .fasta.
#' @param t A scalar that represent the percentage of error allowed in the sliding window. Default = 0.01.
#' @param s A scalar that represent the size of the sliding window. Default = 50.
#' @param m A scalar that represent the minimum size of the sequence to be kept. Default = 60.
#'
#' @details
#'
#' See the \url{http://taraoceans.sb-roscoff.fr/EukDiv/} for more informations on how the quality check is performed.
#'
#' IMPORTANT : if this function is called in an other manners than by the function \link{preTreatment},
#' then the function append the files if it is called several times.
#' Hence you should erase your files if your would like to recall the function.
#'
#' @return Nothing, but work on the files.
#' @export
#'
#' @examples
#'
#' \dontrun{
#'   fastqPath<-".../test/R1.fastq"
#'   outputFasta <- ".../test/R1.fasta"
#'
#'   fastqPath <- "/home/raphael/Documents/PatPilr_source/
#'   testPipeline/testpreTreatment/testqualCheck/unknown.fastq"
#'   outputFasta <- "/home/raphael/Documents/PatPilr_source/
#'   testPipeline/testpreTreatment/testqualCheck/unknownClean.fasta"
#'
#' }
call.qualCheck <- function(fastqPath,
                           outputFasta,
                           t = 0.01,
                           s = 50,
                           m = 60){

  if(file.exists(fastqPath)){
    info <- Sys.info()
    path <- system.file("PatPil", package = "PatPilr")
    if(info[1] == "Linux"){
      path <- paste(path,"/PatPil",sep = "")
    }else if(info[1] == "Windows"){
      path <- paste(path,"/PatPil.exe",sep = "")
    }


    system2(path,args = c('qualCheck',
                          '-f',fastqPath,
                          '-o',outputFasta,
                          '-t',t,
                          '-s',s,
                          '-m',m))
  }else{
    stop("call.qualCheck : the file of the argument fastqPath does not exist...")
  }

}
