############
## EntryList.R
##
##  S4 Class for an EntryList#

## nEntries becomes a generic function
nEntries <- function(object, selection="") stop("Called without a registered object")
setGeneric("nEntries")

setClass("EntryList",
         representation(ptr="externalptr")
         )

############
## Show
setMethod("show", "EntryList",
          function(object) {
            cat("EntryList", getNameEntryList(object), getDetailsEntryList(object), 
                "with", nEntries(object), "Entries\n")
          }
          )

##########
## getEntryList -- Get the entry list from Root
getEntryList <- function(name, manageItsMemory=F) {
  
  if ( !is.character(name) ) stop ("name must be a character")
  if ( !is.logical(manageItsMemory) ) stop("manageItsMemory must be logical")
  
  ptr = .Call("getEntryListWithName", name, manageItsMemory, 
    PACKAGE="RootTreeToR")
  
  new("EntryList", ptr=ptr)
}

# ############
# ## createEntryList -- make a new entry list
# createEntryList <- function(name, title, entryNums) {
#   
#   if ( !is.character(name) ) stop ("name must be a character")
#   if ( !is.character(title) ) stop ("title must be a character")
#   if ( !is.numeric(entryNums) ) stop ("entryNums must be an integer vector")
#   
#   ptr = .Call("newEntryList", name, title, as.integer(entryNums), 
#     PACKAGE="RootTreeToR")
#   
#   new("EntryList", ptr=ptr)
# }

################
## getName - Get the name of this entryList
getNameEntryList <- function(entryList) {
  .assertClass(entryList, "EntryList")
  
  .Call("getNameEntryList", entryList@ptr,
        PACKAGE="RootTreeToR")
}

################
## getDetails - Get the title of the entryList
getDetailsEntryList <- function(entryList) {
  .assertClass(entryList, "EntryList")
  
  .Call("getTitleEntryList", entryList@ptr,
        PACKAGE="RootTreeToR")
}

################
## nEntries - Get the number of entries in the entry list
setMethod("nEntries", "EntryList",
          function(object, selection="") {
            if (selection != "") stop("Selection in nEntries not implemented for entry lists.", call.=F)
            .Call("nEntriesEntryList", object@ptr, 
                  PACKAGE="RootTreeToR")
          } 
          )

# ################
# ## getEntries - Return a vector of the passed entry numbers
# getEntries <- function(entryList) {
#   .assertClass(entryList, "EntryList")
#   
#   .Call("getEntries", entryList@ptr,
#         PACKAGE="RootTreeToR")
# }
# 
# ################
# ## clear - Clear an entry list
# clear <- function(entryList) {
#   .assertClass(entryList, "EntryList")
#   
#   .Call("clear", entryList@ptr,
#         PACKAGE="RootTreeToR")
#   
#   invisible()
# }
# 
# ################
# ## isInEntryList -- return a logical vector
# isInEntryList <- function(entryList, entryNums) {
#   .assertClass(entryList, "EntryList")
#   
#   if ( !is.numeric(entryNums) ) stop ("entryNums must be an integer vector")
#   
#   .Call("isInEntryList", entryList@ptr, as.integer(entryNums),
#         PACKAGE="RootTreeToR")
# }
# 
# ################
# ## putIntoEntryList -- put entries into the entry list
# putIntoEntryList <- function(entryList, entryNums) {
#   .assertClass(entryList, "EntryList")
#   
#   if ( !is.numeric(entryNums) ) stop ("entryNums must be an integer vector")
#   
#   .Call("putIntoEntryList", entryList@ptr, as.integer(entryNums),
#         PACKAGE="RootTreeToR")
#   
#   invisible()
# }
# 
# #################
# ## addEntryLists -- add entryList2 to entryList1
# addEntryLists <- function(entryList1, entryList2) {
#   .assertClass(entryList1, "EntryList")
#   .assertClass(entryList2, "EntryList")
#   
#   .Call("addEntryLists", entryList1@ptr, entryList2@ptr, 
#         PACKAGE="RootTreeToR")
#   
#   invisible()
# }
# 
# #################
# ## subtractEntryLists -- subtract entryList2 from entryList1
# subtractEntryLists <- function(entryList1, entryList2) {
#   .assertClass(entryList1, "EntryList")
#   .assertClass(entryList2, "EntryList")
#   
#   .Call("subtractEntryLists", entryList1@ptr, entryList2@ptr, 
#         PACKAGE="RootTreeToR")
#   
#   invisible()
# }
# 
# #################
# # intersectEntryLists -- intersect entryList2 with entryList1
# #intersectEntryLists <- function(entryList1, entryList2) {
# #       .assertClass(entryList1, "EntryList")
# #       .assertClass(entryList2, "EntryList")
# #       
# #       .Call("intersectEntryLists", entryList1@ptr, entryList2@ptr, 
# #                   PACKAGE="RootTreeToR")
# #
# #  invisible()
# #}
