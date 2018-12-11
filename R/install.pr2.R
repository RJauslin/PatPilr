#' install pr2
#'
#' install the PR2 package \url{https://github.com/pr2database/pr2database}
#'
#' @param force force argument of \code{\link[devtools:install_github]{install_gitub}}
#'
#' @return Nothing
install.pr2 <- function(force = FALSE){
  devtools::install_github("pr2database/pr2database",force)
}
