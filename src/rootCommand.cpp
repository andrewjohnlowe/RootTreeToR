// Code to process a Root command
#include "TROOT.h"
#include "TSystem.h"

extern "C" {
#include <R.h>
#include <Rdefines.h>
}

#include <string>


extern "C" {
  SEXP initRoot();
  SEXP loadRootLibrary(SEXP libName);
  SEXP rootCommand(SEXP comm);
}

SEXP initRoot()
{
  // Initialize root
  // Don't actually do anything
  return R_NilValue;
}

SEXP rootCommand(SEXP theComm)
{
  std::string comm = CHAR(STRING_ELT(theComm, 0));
  gROOT->ProcessLine(comm.c_str());
  
  return R_NilValue;
}


SEXP loadRootLibrary(SEXP libName)
{
  std::string lib = CHAR(STRING_ELT(libName, 0));
  int results;
  
  results = gSystem->Load(lib.c_str());
  
  SEXP r = NEW_INTEGER(1);
  INTEGER(r)[0] = results;
	
  return r;
}
