#' call derep_ech
#'
#' This function call the function derep_ech of the tools PatPil.
#'
#' @param pathFolder A character string representing the path to the working directory.
#' @param within A scalar integer representing the threshold number of occurence of each sequences in a file.
#'
#' @details
#'
#' It dereplicate each files of the directory 'pathFolder'. See Dereplicate for more infos.
#'
#' @return Nothing, works on the files
#' @export
#'
#' @examples
#' \dontrun{
#' pathFolder <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testderep/"
#' call.derep_ech(pathFolder,3)
#'
#'
#' call.derep_ech(pathFolder = "/home/raphael/Documents/Cadavre/eukaryote/Pilonel_P6_18S/removedNtmp/",
#' within = 1)
#'
#'
#' }
call.derep_ech <- function(pathFolder,
                        within = 3){

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
}
