#' Perform all primer combinations
#'
#' This function is supposed to be internal and is used to create the primerforward.txt and primerreverse.txt files
#'  for the function \code{\link{preTreatment}}.
#'  It could be used if you would like to have all possible combinations of a primer with uncertain nucleotides.
#'
#' @param primer A character string with uncertain nucleotide.
#' @param direction A character string : "none", "forward" or "reverse".
#' @param trim_nuc A scalar value representing the number of nucleotide trimmed (in the chosen direction). Ignored if "none".
#'
#' @details
#'
#' Uncertain nucleotides are transformed with the combinations :
#'
#' \itemize{
#' \item R = "AG"
#' \item Y = "CT
#' \item S = "GC",
#' \item W = "AT",
#' \item K = "GT",
#' \item M = "AC",
#' \item B = "CGT",
#' \item D = "AGT",
#' \item H = "ACT",
#' \item V = "ACG".
#' }
#'
#' Careful about the number of uncertain nucleotide in the primer,
#'  the number of possible combinations can become very large.
#'   Moreover, if you allowed a great trim number \code{trim} then the possible combinations increased as well.
#'
#'
#' @return A vector containing all unique combinations depending on the uncerain nucleotides.
#'
#' @examples
#' \dontrun{
#' primer <- "CATTGAARARTTGVAT"
#' primer <- "CRAAGAYGATYAGATSWMBACCRT"
#' AllPrimer(primer,direction = "forward",trim_nuc = 2)
#' AllPrimer(primer,direction = "reverse",trim_nuc = 10)
#' AllPrimer(primer,direction = "none",trim_nuc = 0)}
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

