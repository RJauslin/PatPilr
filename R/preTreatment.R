#' Merge, demultiplex and clean your fastq files
#'
#' Function that apply a pre-treatment on the fasq files R1 and R2. See 'Details'.
#'
#'@param pathFolder A character string containing the path where the program will work.
#'  It should contains the two .fastq file with R1 and R2 inside the name.
#'@param sepFile A character string representing the separator to get the name of the files. Meaning that
#' the names kept are on the left hand side of the separator. Default = "_R".
#'@param m A scalar value that represent the minimum required overlap
#' length between two reads to provide a confident overlap. Default m = 10.
#'@param M A scalar value that represent the maximum overlap length expected
#' in approximately ninety percent of read pairs. Default M = 100.
#'@param x A scalar value that represent the maximum allowed ratio between the number
#' of mismatched base pairs and the overlap length. Default x = 0.25.
#'@param t A scalar value that represent the number of worker threads. Default t = 4.
#'@param mismatch A boolean value, would one mismatch is allowed inside the barcode. Default mismatch = FALSE
#'@param err A scalar value that represent the percentage of error allowed in the sliding window. Default = 0.01.
#'@param slide A scalar integer that represent the size of the sliding window. Default = 50.
#'@param minlength A scalar integer that represent the minimum size of the sequence to be keep. Default = 60.
#'
#'@details
#'
#' This function merges, demultiplex, and clean your fastq files. You are supposed to put only the fastq files
#'  specified by the ..._R1.fastq, ..._R2.fastq and the information needed for the demultiplexing.
#'
#' \enumerate{
#' \item simple tag :
#' You have to put in your working directory a file called \strong{barcode.txt}.
#'  It is really important that the barcode file have the following format.
#'  \itemize{
#'   \item ACGAGTGCGT	name1.fastq
#'   \item ACGCTCGACA	name2.fastq
#'   \item AGACGCACTC	name3.fastq
#'   \item ...
#'  }
#' \item double tag : You have to put in your working directory three files called \strong{forwardtag.txt}, \strong{reversetag.txt}, and \strong{primer.txt}.
#'  It is really important that the files have the following format.
#'
#'   \itemize{
#'   \item ACGAGTGCGT	forwardTag1
#'   \item ACGCTCGACA	forwardTag2
#'   \item AGACGCACTC	forwardTag3
#'   \item ...
#'  }
#'  \strong{reversetag.txt}
#'   \itemize{
#'   \item ACGAGTGCGT	reverseTag1
#'   \item ACGCTCGACA	reverseTag2
#'   \item AGACGCACTC	reverseTag3
#'   \item ...
#'  }
#'  \strong{primer.txt}
#'   \itemize{
#'   \item CAAAATCATAAAGATATTGGDAC	GAAATTTCCDGGDTATMGAATGG
#'  }
#' }
#'
#' If you would like to have more information on each step see :
#' \itemize{
#' \item \code{\link{callFlash}}
#' \item \code{\link{call.D_simple_tag}}
#' \item \code{\link{call.D_double_tag}}
#' \item \code{\link{call.qualCheck}}
#' }
#'
#' @return Noting, but work on the files.
#' @export
#'
#'
#' @importFrom utils menu
#'
#' @examples
#' \dontrun{
#' pathFolder <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testSimple/"
#' pathFolder <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testDouble/"
#' pathFolder <- "/home/raphael/Documents/PatPilr_source/testPipeline/testpreTreatment/testAlready/"
#' preTreatment(pathFolder,M = 250)
#' }
preTreatment <- function(pathFolder,
                         sepFile = "_R",
                         m = 10,
                         M = 100,
                         x = 0.25,
                         t = 4,
                         mismatch = FALSE,
                         err = 0.01,
                         slide = 50,
                         minlength = 60){


  pathIni <- getwd()
  install.flash()
  install.PatPil()
  info <- Sys.info()

  pathFlash <- system.file("flash", package = "PatPilr")
  pathPatPil <- system.file("PatPil", package = "PatPilr")

  if(info[1] == "Linux"){
    pathFlash <- paste(pathFlash,"/flash",sep = "")
    pathPatPil <- paste(pathPatPil,"/PatPil",sep = "")
  }else if(info[1] == "Windows"){
    pathFlash <- paste(pathFlash,"/flash.exe",sep = "")
    pathPatPil <- paste(pathPatPil,"/PatPil.exe",sep = "")
  }





  #############################
  #   MERGING
  #############################

  #-----------------
  # GET THE NAMEFILE FOR R1 AND R2 and THE BARCODE, TAG, PRIMER
  #-----------------
  files <- list.files(pathFolder) # GET THE ALL NAMEFILES
  filesPAIREND <- files[c(which(grepl("R1",files)),which(grepl("R2",files)))] # CHECK LES R1 et R2
  filesPrimerTag <- files[c(which(grepl("barcode",files)),
                            which(grepl("tag",files)),
                            which(grepl("primer",files)))] # CHECK LES primer ou tag




  #-----------------
  ###  DELETES THE FOLDER ALREADY CREATE IF THE preTreatment is rerun
  #-----------------
  mergingStep <- TRUE
  demultiStep <- TRUE
  cleanStep <- TRUE

  if(any(grepl("merged",files))){
    # cat("The program found a folder named 'merged' this potentially means that you have already merged data. Would you like to do merging step once again ?")
    mergingStep <- switch(utils::menu(c("Yes", "No"),
                               title = "\n The program find a folder named 'merged'.\n This potentially means that you have already merged data. \n Would you like to do merging step once again ?") + 1,
           cat("Nothing done\n"), TRUE, FALSE)

    #IF ANALYSIS MUST BE DONE ONCE AGAIN
    if(mergingStep == TRUE){
      unlink(file.path(pathFolder,"merged",fsep = ""),recursive = TRUE)
      if(any(grepl("demultiplex",files))){
        unlink(file.path(pathFolder,"demultiplex",fsep = ""),recursive = TRUE)
      }
      if(any(grepl("clean",files))){
        unlink(file.path(pathFolder,"clean",fsep = ""),recursive = TRUE)
      }
    }else{ # IF MERGING STEP IS OMITTED
      if(any(grepl("demultiplex",files))){ # CHECK IF DEMULTIPLEX MUST BE OMMITED
        demultiStep <- switch(utils::menu(c("Yes", "No"),
                    title = "\n The program found a folder named 'demultiplex'.\n This potentially means that you have already demultiplexed data. \n Would you like to do merging step once again ?") + 1,
               cat("Nothing done\n"), TRUE, FALSE)
        # IF DEMULTIPLEX IS DONE ONCE AGAIN
        if(demultiStep == TRUE){
          unlink(file.path(pathFolder,"demultiplex",fsep = ""),recursive = TRUE)
          if(any(grepl("clean",files))){
            unlink(file.path(pathFolder,"clean",fsep = ""),recursive = TRUE)
          }
        }
      }else{
        if(any(grepl("clean",files))){
          unlink(file.path(pathFolder,"clean",fsep = ""),recursive = TRUE)
        }
      }
    }
  }


  # if(any(grepl("demultiplex",files))){
  #   unlink(file.path(pathFolder,"demultiplex",fsep = ""),recursive = TRUE)
  # }
  if(any(grepl("clean",files))){
    unlink(file.path(pathFolder,"clean",fsep = ""),recursive = TRUE)
  }


  #-----------------
  # GET THE NAMEFILE (argument sep)
  #-----------------
  namefile <- do.call(rbind,strsplit(filesPAIREND,sepFile))[,1]
  namefile <- unique(namefile)


  if(mergingStep == TRUE){

    #-----------------
    # CREATE THE FOLDER merged
    #-----------------
    if(!dir.exists(file.path(pathFolder,"merged",fsep ="" ))){
      dir.create(file.path(pathFolder,"merged",fsep ="" ))
    }

    #-----------------
    # LOOP ON THE R1 AND R2
    #-----------------
    for( i in 1:length(namefile)){
      tmp <- filesPAIREND[which(grepl(namefile[i],filesPAIREND))]

      R1 <- tmp[which(grepl("R1",tmp))]
      R2 <- tmp[which(grepl("R2",tmp))]

      R1 <- file.path(pathFolder,R1,fsep = "")
      R2 <- file.path(pathFolder,R2,fsep = "")

      system2(pathFlash,args = c('-m',m,
                                 '-M',M,
                                 '-x',x,
                                 '-t',t,
                                 '-d',file.path(pathFolder,"merged",fsep ="" ),
                                 '-o',namefile[i],
                                 R1,
                                 R2))
    }

    #-----------------
    # ORGANIZED THE FILES IN merged
    #-----------------
    if(!dir.exists(file.path(pathFolder,"merged/extFrags",fsep ="" ))){
      dir.create(file.path(pathFolder,"merged/extFrags",fsep ="" ))
    }
    if(!dir.exists(file.path(pathFolder,"merged/hFrags",fsep ="" ))){
      dir.create(file.path(pathFolder,"merged/hFrags",fsep ="" ))
    }
    if(!dir.exists(file.path(pathFolder,"merged/notCombFrags",fsep ="" ))){
      dir.create(file.path(pathFolder,"merged/notCombFrags",fsep ="" ))
    }

    extended <- list.files(file.path(pathFolder,"merged/",fsep ="" ))
    extended <- extended[which(grepl("extendedFrags",extended))]

    histo <- list.files(file.path(pathFolder,"merged/",fsep ="" ))
    histo <- histo[which(grepl("hist",histo))]

    notComb <- list.files(file.path(pathFolder,"merged/",fsep ="" ))
    notComb <- notComb[which(grepl("notCombined",notComb))]

    for(i in 1:length(extended)){
      file.rename(from =  file.path(pathFolder,"merged/",extended[i],fsep ="" ),
                  to =  file.path(pathFolder,"merged/extFrags/",extended[i],fsep ="" ))
    }
    for(i in 1:length(histo)){
      file.rename(from =  file.path(pathFolder,"merged/",histo[i],fsep ="" ),
                  to =  file.path(pathFolder,"merged/hFrags/",histo[i],fsep ="" ))
    }
    for(i in 1:length(notComb)){
      file.rename(from =  file.path(pathFolder,"merged/",notComb[i],fsep ="" ),
                  to =  file.path(pathFolder,"merged/notCombFrags/",notComb[i],fsep ="" ))
    }
  }else{
    extended <- list.files(file.path(pathFolder,"merged/extFrags/",fsep = ""))
  }



  #############################
  #   DEMULTIPLEXING
  #############################

  if(demultiStep == TRUE){

    nfiles <- length(list.files(file.path(pathFolder,"merged/extFrags/",fsep = "")))
    ## CREATE DEMULTIPLEX FOLDER
    pathDemulti <- file.path(pathFolder,"demultiplex/",fsep ="" )
    if(!dir.exists(pathDemulti)){
      dir.create(pathDemulti)
    }


    if(nfiles == 1){


      if(any(grepl("barcode",filesPrimerTag))){
        fileBarcode <- file.path(pathFolder,files[which(grepl("barcode",files))],fsep = "")

        call.D_simple_tag(fastqPath = file.path(pathFolder,"merged/extFrags/",extended[1],fsep ="" ),
                          outputFolder = pathDemulti,
                          barcodePath = fileBarcode,
                          mismatch = mismatch)

      }else{
        filePrimer <-  file.path(pathFolder,files[which(grepl("primer",files))],fsep = "")
        fileForwardTag <- file.path(pathFolder,files[which(grepl("forwardtag",files))],fsep = "")
        fileReverseTag <- file.path(pathFolder,files[which(grepl("reversetag",files))],fsep = "")


        if(length(filePrimer) != 0 && length(fileReverseTag) != 0 && length(fileForwardTag) != 0 ){
          primerForDemux(pathFolder)
          call.D_double_tag(fastqPath = file.path(pathFolder,"merged/extFrags/",extended[1],fsep ="" ),
                            outputFolder = pathDemulti,
                            bF = file.path(pathFolder,files[which(grepl("forwardtag",files))],fsep = ""),
                            bR = file.path(pathFolder,files[which(grepl("reversetag",files))],fsep = ""),
                            pF = file.path(pathFolder,"primerforward.txt",fsep = ""),
                            pR = file.path(pathFolder,"primerreverse.txt",fsep = ""),
                            mismatch = FALSE)

        }
      }
    }else{

      prefixfile <- do.call(rbind,strsplit(extended,split = ".extendedFrags"))[,1]
      # ext <- unique(do.call(rbind,strsplit(filesDemultiplexed,split = ".extendedFrags"))[,2])

      for(i in 1:length(extended)){
        file.rename(from =  file.path(pathFolder,"merged/extFrags/",extended[i],fsep ="" ),
                    to =  file.path(pathDemulti,prefixfile[i],".fastq",fsep ="" ))
      }


    }
  }

  #############################
  #   CLEANING
  #############################


  pathClean <- file.path(pathFolder,"clean/",fsep ="" )
  if(!dir.exists(pathClean)){
    dir.create(pathClean)
  }

  filesDemultiplexed <- list.files(file.path(pathFolder,"/demultiplex"))
  if(length(which(filesDemultiplexed =="unknown.fastq")) != 0){
    filesDemultiplexed <- filesDemultiplexed[-which(filesDemultiplexed == "unknown.fastq")]
  }
  prefixfile <- do.call(rbind,strsplit(filesDemultiplexed,split = "[.]"))[,1] # GET WARNINGS IF THERE IS MORE
  ext <- ".fastq"

  for(i in 1:length(prefixfile)){
    call.qualCheck(fastqPath = file.path(pathFolder,"demultiplex/",prefixfile[i],ext,fsep = ""),
                   outputFasta = file.path(pathFolder,"clean/",prefixfile[i],".fa",fsep = ""),
                   t = err,
                   s = slide,
                   m = minlength)
  }


}

