#######
## rootCommand

loadRootLibrary <- function(libName) {
  if ( ! is.character(libName) ) stop("libName must be a character")
  
  .Call("loadRootLibrary", libName, PACKAGE="RootTreeToR")
}

rootCommand <- function(comm) {
  if ( ! is.character(comm) ) stop("comm must be a character")
  
  .Call("rootCommand", comm, PACKAGE="RootTreeToR")
}
