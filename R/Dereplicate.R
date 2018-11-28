#' Dereplicate
#'
#' @param pathFolder the path to the folder files
#' @param within the number of occurence of each sequences in a file.
#' @param between the number of occurence of each sequence between files.
#'
#' @return nothing but works on the files
#' @export
#'
#' @examples
#' \dontrun{
#'' pathFolder <- "/home/raphael/Documents/Rpackage/pipelineR/inst/PatPil/test/test_derepRaph/"
#' Dereplicate(pathFolder)
#' }
Dereplicate <- function(pathFolder,
                        within = 3,
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
  if(any(files == "derep_ech")){
    files <- files[-which(files == "derep_ech")]
  }
  if(any(files == "derep")){
    files <- files[-which(files == "derep")]
  }

  #CHANGE THE NAMEFILE IN ORDER THAT THE FUTURE PARSING IS WORKING
  newfiles <- files
  if(any(grepl("-",files))){
    newfiles <- gsub("-","+",newfiles)
  }
  if(any(grepl("_",files))){
    newfiles <- gsub("_","+",newfiles)
  }
  for(i in 1:length(files)){
    file.rename(from = file.path(pathFolder,files[i],fsep = ""),
                to = file.path(pathFolder,newfiles[i],fsep = ""))
  }
  files <- newfiles


  # CREATE DIRECTORY derep_ech
  pathDerep_ech <- file.path(pathFolder,"derep_ech/",fsep ="" )
  if(!dir.exists(pathDerep_ech)){
    dir.create(pathDerep_ech)
  }

  # CALL DEREP ECH
  for(i in 1:length(files)){
    system2(pathPatPil,args = c('derep_ech',
                               '-f', file.path(pathFolder,files[i],fsep ="" ),
                               '-o',file.path(pathDerep_ech,files[i],fsep=""),
                               '-s',within))
  }

  # CREATE DIRECTORY derep
  pathDerep <- file.path(pathFolder,"derep/",fsep ="" )
  if(!dir.exists(pathDerep)){
    dir.create(pathDerep)
  }


  #DEREP
  system2(pathPatPil,args = c('derep',
                              '-folder',pathDerep_ech,
                              '-good',file.path(pathDerep,"RC.fa",fsep=""),
                              '-bad',file.path(pathDerep,"RCNotPassed.fa",fsep=""),
                              '-s',between))


}
