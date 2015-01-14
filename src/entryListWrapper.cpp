// Wrapper for TEntryList -- called by R

#include "TEntryList.h"
#include "TFile.h"

#include <R.h>
#include <Rdefines.h>

#include <string>

#include "entryListWrapper.h"

// Some definition of True is interfering
#undef TRUE

static SEXP entrylist_type_tag;

//////////////////////////
// Check that the external pointer is the right thing
TEntryList* checkForEntryListWrapper(SEXP ptr)
{
  if ( TYPEOF(ptr) != EXTPTRSXP || 
       R_ExternalPtrTag(ptr) != entrylist_type_tag ||
       ! R_ExternalPtrAddr(ptr) )
    error("Bad Pointer to EntryListWrapper");
  
  return (TEntryList*) R_ExternalPtrAddr(ptr);
}

/////////////////////////////////////////
// initEntryListWrapper -- initialize
SEXP initEntryListWrapper()
{
  entrylist_type_tag = install("EntryList_TAG");
  return R_NilValue;
}


//////////////////////////
// Get an entry list given a name
//
//   If R is calling it, then we don't manage the memory!
SEXP getEntryListWithName(SEXP name, SEXP mangeItsMemory)
{
  std::string daName = CHAR(STRING_ELT(name, 0));
  bool doManage = LOGICAL(mangeItsMemory)[0] == 1;
  
  return getEntryListWithNameC(daName, doManage);
}

//////////////////////////
// Get an entry list given a name
SEXP getEntryListWithNameC(std::string name, bool manageItsMemory)
{
  TEntryList* theList = (TEntryList*) gDirectory->Get( name.c_str() );
  
  if ( ! theList ) {
    REprintf("!! Could not find EntryList with name %s\n", name.c_str());
    error("Abort!");
  }
  
  // Got an entry list, wrap it in an R external pointer
  return wrapTEntryListPointer(theList, manageItsMemory);
}

//////////////////////////////
// Wrap up a TEntryList pointer and perhaps register the finalizer
SEXP wrapTEntryListPointer(TEntryList* ptr, bool manageItsMemory)
{
  SEXP val = R_MakeExternalPtr(ptr, entrylist_type_tag, R_NilValue);
  
  if ( manageItsMemory ) {
    R_RegisterCFinalizerEx(val, 
                           (R_CFinalizer_t)deleteEntryList, TRUE);
  }
  
  return val;
}

///////////////////////////////////
// Make a new entry list given a name, title, and a set of entrys to put in it
SEXP newEntryList(SEXP name, SEXP title, SEXP entryNums)
{
  std::string daName = CHAR( STRING_ELT(name, 0) );
  std::string daTitle = CHAR( STRING_ELT(title, 0) );
  
  int n = GET_LENGTH(entryNums);
  
  TEntryList* el = new TEntryList(daName.c_str(), daTitle.c_str());
  
  // Wrap it -- and I made it, so I manage it
  SEXP wrapPtr = wrapTEntryListPointer(el, true);
  
  // Now fill it
  putIntoEntryList(wrapPtr, entryNums);
  
  return wrapPtr;
}


///////////////////////////////////
// Delete the entry list
SEXP deleteEntryList(SEXP entryList)
{
  TEntryList* el = checkForEntryListWrapper(entryList);
  
  REprintf("Deleting TEntryList at ptr %p\n", el);
  
  delete el;
  
  R_ClearExternalPtr(entryList);
  
  return R_NilValue;
}


///////////////////////
// Get the name of the entry list
SEXP getNameEntryList(SEXP entryList)
{
  TEntryList* el = checkForEntryListWrapper(entryList);
  
  SEXP name = NEW_CHARACTER(1);
  SET_STRING_ELT( name, 0, mkChar(el->GetName()) );
  
  return name;
}

///////////////////////
// Get the title of the entry list
SEXP getTitleEntryList(SEXP entryList)
{
  TEntryList* el = checkForEntryListWrapper(entryList);
  
  SEXP name = NEW_CHARACTER(1);
  SET_STRING_ELT( name, 0, mkChar(el->GetTitle()) );
  
  return name;
}

///////////////////////
// Get the number of entries in the entry list
SEXP nEntriesEntryList(SEXP entryList)
{
  TEntryList* el = checkForEntryListWrapper(entryList);
  
  SEXP n = NEW_INTEGER(1);
  INTEGER(n)[0] = el->GetN();
  
  return n;
}

/*
//////////////////////////
// Return all of the entrys as a big vector
SEXP getEntries(SEXP entryList)
{
  TEntryList* el = checkForEntryListWrapper(entryList);
  
  unsigned int l = el->GetN();
  
  SEXP e;
  PROTECT( e = NEW_INTEGER(l) );
  
  for ( unsigned int i = 0; i < l; ++i) {
    INTEGER(e)[i] = el->GetEntry(i);
  }
  
  UNPROTECT(1);
  
  return e;
}

////////////////////////
// Clear the entry list
SEXP clear(SEXP entryList)
{
  TEntryList* el = checkForEntryListWrapper(entryList);
  
  el->Clear();
  
  return R_NilValue;
}

/////////////////////////
// Return a logical vector if entries are in the entry list
SEXP isInEntryList(SEXP entryList, SEXP entryNums)
{
  
  TEntryList* el = checkForEntryListWrapper(entryList);
  
  SEXP l;
  PROTECT(l = NEW_LOGICAL( GET_LENGTH(entryNums) ) );
  
  for ( unsigned int i = 0; i < GET_LENGTH(entryNums); ++i ) {
    LOGICAL(l)[i] = el->Contains( INTEGER(entryNums)[i] ) == 1;
  }
  
  UNPROTECT(1);
  
  return l;
}
*/

/////////////////////////
// Put entries into the entry list
SEXP putIntoEntryList(SEXP entryList, SEXP entryNums)
{
  
  TEntryList* el = checkForEntryListWrapper(entryList);
  
  for ( unsigned int i = 0; i < GET_LENGTH(entryNums); ++i ) {
    el->Enter( INTEGER(entryNums)[i] );
  }

  return R_NilValue;
}

/*
///////////////////////////////
// Add entryList2 to entryList1 -- this modifies entryList1
SEXP addEntryLists(SEXP entryList1, SEXP entryList2)
{
  TEntryList* el1 = checkForEntryListWrapper(entryList1);
  TEntryList* el2 = checkForEntryListWrapper(entryList2);
        
  el1->Add(el2);
        
  return R_NilValue;
}

///////////////////////////////
// Subtract entryList2 from entryList1 -- this modifies entryList1
SEXP subtractEntryLists(SEXP entryList1, SEXP entryList2)
{
  TEntryList* el1 = checkForEntryListWrapper(entryList1);
  TEntryList* el2 = checkForEntryListWrapper(entryList2);
        
  el1->Subtract(el2);
        
  return R_NilValue;
}

///////////////////////////////
// Intersect entryList1 with entryList2 -- this modifies entryList1
//  Entries not in entryList2 are removed from entryList1
//SEXP intersectEntryLists(SEXP entryList1, SEXP entryList2)
//{
//      TEntryList* el1 = checkForEntryListWrapper(entryList1);
//      TEntryList* el2 = checkForEntryListWrapper(entryList2);
//      
//      el1->Intersect(el2);
//      
//      return R_NilValue;
//}
*/
