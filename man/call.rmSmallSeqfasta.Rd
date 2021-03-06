% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/call.rmSmallSeqfasta.R
\name{call.rmSmallSeqfasta}
\alias{call.rmSmallSeqfasta}
\title{call rmSmallSeqfasta}
\usage{
call.rmSmallSeqfasta(fastaPath, outputFasta, sizemin = 80)
}
\arguments{
\item{fastaPath}{A character string that represent the path to the fasta file.}

\item{outputFasta}{A character string that represent the path to the output fasta file.}

\item{sizemin}{A scalar integer to selected the minimum size.}
}
\value{
Nothing
}
\description{
This function calls the rmSmallSeqfasta program of the tool PatPil.
}
\details{
This function applies the rmSmallSeqfasta tools of the PatPil program.
It simply removes the sequences that are smaller than a fixed integer.
}
\examples{
\dontrun{
fastaPath <- ".../fastaTest.fa"
fastaPath <- "/home/raphael/Documents/PatPilr_source/
testPipeline/testpreTreatment/testrmSmallSeqfasta/fastaTest.fasta"
outputFasta <- "/home/raphael/Documents/PatPilr_source/
testPipeline/testpreTreatment/testrmSmallSeqfasta/fastaTest_rm.fasta"
call.rmSmallSeqfasta(fastaPath,outputFasta,100)
}
}
