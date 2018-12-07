#' Perform All combination
#'
#' This function is used to create the primer forward and reverse for the function \link{preTreatment}
#'
#' @param primer A character string with wobble nucleotide
#' @param direction A character string between "none", "forward" or "reverse"
#' @param trim_nuc A scalar value representing the number of nucleotide trimmed (in the direction forward or reverse)
#'
#' @details Arguments which should be a character string for example : "CATTGAARARTTGVAT"
#'
#' The character are then transform following the transformation :
#'
#' R = "AG",
#' Y = "CT",
#' S = "GC",
#' W = "AT",
#' K = "GT",
#' M = "AC",
#' B = "CGT",
#' D = "AGT",
#' H = "ACT",
#' V = "ACG".
#'
#' Careful about the number of wobble in the primer, the number of possible combinations can become very large.
#'
#' @return A data.frame containing all combination depending on the wobble. See Details
#'
#'
#' @examples
#' primer <- "CYGCGGTAATTCCAGCTC"
#' primer <- "CRAAGAYGATYAGATSWMBACCRT"
#' \dontrun{
#' AllPrimer(primer,direction = "forward",trim_nuc = 2)
#' }
#' @export
AllPrimer <- function(primer,direction = "none",trim_nuc = 0){


  # WOBBLE GESTION
  wobble <- list(R = c("A","G"),
                  Y = c("C","T"),
                  S = c("G","C"),
                  W = c("A","T"),
                  K = c("G","T"),
                  M = c("A","C"),
                  B = c("C","G","T"),
                  D = c("A","G","T"),
                  H = c("A","C","T"),
                  V = c("A","C","G"))
  l <- list()
  c <- 1;
  p <- strsplit(primer,"")[[1]]
  for(i in 1:length(p)){
    for(j in 1:length(wobble)){
      if(names(wobble)[j] == p[i]){

        p[[i]] <- " "
        l[[c]] <- wobble[[j]]
        c <- c+1
      }
    }
  }
  p <- paste(p,collapse = "")

  # CASE WHERE THERE IS NO WOBBLE
  if(p == primer){
    if(direction == "forward" & trim_nuc != 0){
      base <- strsplit(primer,"")[[1]]
      n <- length(base)
      primerF <- c()
      for( i in 1:(trim_nuc+1)){
        primerF <- c(primerF,
                     paste(base[i:n],collapse = ""))
      }
      return(primerF)
    }else if(direction == "reverse" & trim_nuc != 0){
      base <- strsplit(primer,"")[[1]]
      n <- length(base)
      primerR <- c()
      for( i in n:(n-trim_nuc)){
        primerR <- c(primerR,
                     paste(base[1:i],collapse = ""))
      }
      return(primerR)
    }else{
      return(p)
    }
  }else{ # CASE WHERE THERE ARE SOME WOBBLES


    comb <- do.call(expand.grid, l)
    # gsub("<[^>]+>", " ",primer)
    vec <- c()
    for(i in 1:nrow(comb)){
      tmp <- p
      for(j in 1:ncol(comb)){
        tmp <- sub(" ",comb[i,j],tmp)
      }
      vec[i] <- tmp
    }
    vec <- as.data.frame(vec)


    l_primer <- list()
    if(direction == "forward" & trim_nuc != 0){
      for(i in 1:nrow(vec)){
        tmp <-l_primer[[i]] <- as.character(vec[i,])
        for(j in 1:trim_nuc){
          n <- length(strsplit(tmp,"")[[1]])
          tmp <- paste(strsplit(tmp,"")[[1]][2:n],collapse = "")
          l_primer[[i]] <- c(l_primer[[i]],tmp)
        }
      }
      l_primer <- unique(unlist(l_primer))
      return(l_primer)
    }else if(direction == "reverse" & trim_nuc != 0){
      for(i in 1:nrow(vec)){
        tmp <-l_primer[[i]] <- as.character(vec[i,])
        for(j in 1:trim_nuc){
          n <- length(strsplit(tmp,"")[[1]])
          tmp <- paste(strsplit(tmp,"")[[1]][1:(n-1)],collapse = "")
          l_primer[[i]] <- c(l_primer[[i]],tmp)
        }
      }
      l_primer <- unique(unlist(l_primer))
      return(l_primer)

    }else{
      return(as.character(vec[,1]))
    }
  }

}

