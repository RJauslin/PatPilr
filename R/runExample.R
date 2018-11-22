#' Shiny application
#'
#' @param example Future app shiny
#'
#' @return call the Shiny app
runExample <- function(example) {
  # appDir <- system.file("shiny_examples", "PipelineR", package = "pipelineR")
  # if (appDir == "") {
  #   stop("Could not find example directory. Try re-installing `pipelineR`.", call. = FALSE)
  # }
  # shiny::runApp(appDir, display.mode = "normal")
  # locate all the shiny app examples that exist
  validExamples <- list.files(system.file("shiny_examples", package = "pipelineR"))

  validExamplesMsg <-
    paste0(
      "Valid examples are: '",
      paste(validExamples, collapse = "', '"),
      "'")

  # if an invalid example is given, throw an error
  if (missing(example) || !nzchar(example) ||
      !example %in% validExamples) {
    stop(
      'Please run `runExample()` with a valid example app as an argument.\n',
      validExamplesMsg,
      call. = FALSE)
  }

  # find and launch the app
  appDir <- system.file("shiny_examples", example, package = "pipelineR")
  shiny::runApp(appDir, display.mode = "normal")
}
