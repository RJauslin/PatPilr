#' install pr2
#'
#' @param force force argument of install_github
#'
#' @return Nothing
#' @export
#'
#' @examples
#' \dontrun{
#' # install.packages(devtools)
#' }
#'
install.pr2 <- function(force = FALSE){
  devtools::install_github("pr2database/pr2database",force)
}

