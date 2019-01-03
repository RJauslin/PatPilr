#' install pr2
#'
#' install the PR2 reference database with the R package \url{https://github.com/pr2database/pr2database}.
#'
#' @importFrom devtools install_github
#'
#' @return Nothing
install.pr2 <- function(){
  devtools::install_github("pr2database/pr2database")
}
