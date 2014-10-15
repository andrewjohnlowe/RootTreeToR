\name{loadRootLibrary}
\alias{loadRootLibrary}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Run an arbitrary Root command }
\description{
  Run an arbitrary Root command from \R. 
}
\usage{
loadRootLibrary(libName)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{libName}{ The name of the library to load into Root }
}
\details{
This function allows you to load a shared library into Root. Note that in some cases,
especially for Root v5, \emph{RootTreeToR} needs to be linked against the shared 
libraries you plan to load. You normally do not need to specify a path as Root will find the
shared library by looking at LD_LIBRARY_PATH. 
Note that if you need to load libraries to read in a tree file, you should 
consider a .rootmap file. 
}
\value{
  Returns 0 on successful load, 1 if the library was already loaded, -1 if the library
cannot be found, and -2 if there's a version mismatch. 
}

\references{For more information on \emph{Root} see \url{http://root.cern.ch}.
Root is written by Rene Brun and Fons Rademakers. }
\author{Addm Lyon \email{lyon@fnal.gov} }
\examples{
\dontrun{
loadRootLibrary("libtmb_tree.so")
}
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ manip }
