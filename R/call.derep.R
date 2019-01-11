#' derep
#'
#' Dereplicate each of your fasta files.
#'
#' @param pathFolder A character string representing the path to the working directory.
#' @param within A scalar integer representing the threshold number of occurence of each sequences in a file.
#'
#' @details
#'
#' Dereplicate each files and the second one works one the dereplicated files.
#'
#' @return Nothing, works on the files
#' @export
#'
#' @examples
#' \dontrun{
#' pathFolder <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testderep/derep_ech/"
#' call.derep(pathFolder,5)
#' }
call.derep <- function(pathFolder,
                        between = 2){


  # INSTALL PROGRAM
  pathIni <- getwd()
  install.PatPil()
  info <- Sys.info()

  pathPatPil <- system.file("PatPil", package = "PatPilr")
  if(info[1] == "Linux"){
    pathPatPil <- paste(pathPatPil,"/PatPil",sep = "")
  }else if(info[1] == "Windows"){
    pathPatPil <- paste(pathPatPil,"/PatPil.exe",sep = "")
  }


  #GET THE NAMEFILES
  files <- list.files(pathFolder)

  # newfiles <- files
  # if(any(grepl("-",files))){
  #   newfiles <- gsub("-","+",newfiles)
  # }
  # if(any(grepl("_",files))){
  #   newfiles <- gsub("_","+",newfiles)
  # }
  # for(i in 1:length(files)){
  #   file.rename(from = file.path(pathFolder,files[i],fsep = ""),
  #               to = file.path(pathFolder,newfiles[i],fsep = ""))
  # }
  # files <- newfiles
  #

  # CREATE DIRECTORY derep
  pathDerep <- file.path(pathFolder,"derep/",fsep ="" )
  if(!dir.exists(pathDerep)){
    dir.create(pathDerep)
  }


  #DEREP
  system2(pathPatPil,args = c('derep',
                              '-folder',pathFolder,
                              '-good',file.path(pathDerep,"RC.fa",fsep=""),
                              '-bad',file.path(pathDerep,"RCNotPassed.fa",fsep=""),
                              '-s',between))


  }
