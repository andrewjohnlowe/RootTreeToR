// Wrapper for a TEntryList object -- called by R
//

#ifndef __ENTRYLISTWRAPPER_H__
#define __ENTRYLISTWRAPPER_H__

#include <string>

class TEntryList;

extern "C"
{
  SEXP initEntryListWrapper();
        
  SEXP deleteEntryList(SEXP entryList);
  SEXP getEntryListWithName(SEXP name, SEXP manageItsMemory);
  SEXP newEntryList(SEXP name, SEXP title, SEXP entryNums);
  
  SEXP getNameEntryList(SEXP entryList);
  SEXP getTitleEntryList(SEXP entryList);
  SEXP nEntriesEntryList(SEXP entryList);
  /*  
  SEXP getEntries(SEXP entryList);
        
  SEXP clear(SEXP entryList);
        
  SEXP isInEntryList(SEXP entryList, SEXP entryNums);
  */
  SEXP putIntoEntryList(SEXP entryList, SEXP entryNums);
  
  /*
  SEXP addEntryLists(SEXP entryList1, SEXP entryList2);
  SEXP subtractEntryLists(SEXP entryList1, SEXP entryList2);
  //SEXP intersectEntryLists(SEXP entryList1, SEXP entryList2);
  */
}

TEntryList* checkForEntryListWrapper(SEXP ptr);

SEXP getEntryListWithNameC(std::string name, bool manageItsMemory);

SEXP wrapTEntryListPointer(TEntryList* ptr, bool manageItsMemory);

#endif
