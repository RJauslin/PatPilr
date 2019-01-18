#' Update the package version
#'
#' onyl useful for github update, but if you find another application tell me. :-)
#'
#' @param packageLocation location of the main folder of the package
#'
#' @examples
#' \dontrun{
#'  updatePackageVersion()
#' }
#'
updatePackageVersion <- function(packageLocation ="/home/raphael/Documents/PatPilr-source/PatPilr"){

  ## Read DESCRIPTION file
  desc <- readLines(file.path(packageLocation, "DESCRIPTION"))
  readme <-  readLines(file.path(packageLocation, "README.md"))
  ## Find the line where the version is defined
  vLine <- grep("^Version\\:", desc)
  vLineReadme <- grep("* Current version : ", readme)
  vLineDate <- grep("* Last update : ", readme)

  ## Extract version number
  vNumber <- gsub("^Version\\:\\s*", "", desc[vLine])
  vNumberReadme <- gsub("[*] Current version : ", "", readme[vLineReadme])

  ## Split the version number into two; a piece to keep, a piece to increment
  versionNumber <- strsplit(vNumber, "\\.")[[1]]
  versionParts <- length(versionNumber)
  vNumberKeep <- paste(versionNumber[1:(versionParts-1)], sep= "", collapse= ".")
  vNumberUpdate <- versionNumber[versionParts]

  ## Replace old version number with new one (increment by 1)
  oldVersion <- as.numeric(vNumberUpdate)
  newVersion <- oldVersion + 1

  ## Build final version number
  vFinal <- paste(vNumberKeep, newVersion, sep = ".")

  ## Update DESCRIPTION file (in R)
  desc[vLine] <- paste0("Version: ", vFinal )
  readme[vLineReadme] <- paste0("* Current version : ", vFinal)
  readme[vLineDate] <- paste0("* Last update : ", Sys.Date())



  ## Update the actual DESCRIPTION file
  writeLines(desc, file.path(packageLocation, "DESCRIPTION"))
  writeLines(readme, file.path(packageLocation, "README.md"))

  ## Return the updated version number to screen
  return(vFinal)
}
