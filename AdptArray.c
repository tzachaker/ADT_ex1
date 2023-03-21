#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"

typedef struct AdptArray_ {
    COPY_FUNC copyFunc;
    DEL_FUNC deleteFunc;
    PRINT_FUNC printFunc;
    int sizeAdptArray;
    PElement* pElementAdptArray;
} AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete, PRINT_FUNC print) {
    PAdptArray adptArr;
    adptArr = (PAdptArray) malloc(sizeof(AdptArray));
    if (adptArr == NULL){
         return NULL;
    }
    else{
        adptArr->copyFunc = copy;
        adptArr->deleteFunc = delete;
        adptArr->printFunc = print;
        adptArr->sizeAdptArray = 0;
        adptArr->pElementAdptArray = NULL;
        return adptArr;
    }
}

//The DeleteAdptArray function deletes the AdptArray and its elements.
//It calls the deleteFunc function on each element and sets it to NULL.
//Then it frees the array memory and the object memory.
void DeleteAdptArray(PAdptArray adptArr) {
    if (adptArr == NULL) {
        return;
    }
    for (int i = 0; i < adptArr->sizeAdptArray; i++) {
        if (adptArr->pElementAdptArray[i] != NULL) {
            adptArr->deleteFunc(adptArr->pElementAdptArray[i]);
            adptArr->pElementAdptArray[i] = NULL;
        }
    }
    free(adptArr->pElementAdptArray);
    adptArr->sizeAdptArray = 0;
    free(adptArr);
}

//The SetAdptArrayAt function sets the element at the given index to a new value. 
//If the index is out of bounds, it resizes the array to accommodate the new index.
// If the element at the index is not NULL, it is first deleted using the deleteFunc function.
// Then the new element is copied at the index.
Result SetAdptArrayAt(PAdptArray adptArr, int index, PElement pElement) {
    if (adptArr == NULL || index < 0) {
        return FAIL;
    }
    int currSize = (index >= adptArr->sizeAdptArray) ? index + 1 : adptArr->sizeAdptArray;
    PElement *new_pElementAdptArray = realloc(adptArr->pElementAdptArray, sizeof(PElement) * currSize); // increase the arr
    if (new_pElementAdptArray == NULL) {
        return FAIL;
    }
    adptArr->pElementAdptArray = new_pElementAdptArray;
    for (int i = GetAdptArraySize(adptArr); i < currSize; i++) {
        adptArr->pElementAdptArray[i] = NULL;
    }
    adptArr->sizeAdptArray = currSize;
    PElement pE;
    pE = adptArr->pElementAdptArray[index];
    if (pE != NULL ) {
        adptArr->deleteFunc(adptArr->pElementAdptArray[index]);
    }
    PElement newElement = adptArr->copyFunc(pElement);
    if (newElement == NULL){ 
        return FAIL;
    }
    adptArr->pElementAdptArray[index] = newElement;
    return SUCCESS;
}

//The GetAdptArrayAt function return the element at the given index. 
//If the index is out of bounds or the element is NULL, it returns NULL.
//Otherwise, it copies the element using the copyFunc function and returns the copy.
PElement GetAdptArrayAt(PAdptArray adptArr, int index) {
    if (adptArr == NULL || index < 0 || index >= GetAdptArraySize(adptArr)) {
        return NULL;
    }
    PElement element = adptArr->pElementAdptArray[index];
    if (element == NULL) {
        return NULL;
    }
    return adptArr->copyFunc(element);
}

//The GetAdptArraySize function returns the size of the AdptArray. If the object is NULL, it returns -1.
int GetAdptArraySize(PAdptArray adptArr) {
    if (adptArr == NULL){
        return -1;
    }
    return adptArr->sizeAdptArray;
}

//The PrintDB function prints all the "non-NULL" elements of the AdptArray by calling the printFunc function on each "non-NULL" element.
void PrintDB(PAdptArray adptArr) {
    if (adptArr == NULL){ 
        return;
    }
    for (int i = 0; i < GetAdptArraySize(adptArr); i++) {
        PElement currElement = adptArr->pElementAdptArray[i];
        if (currElement != NULL){
            adptArr->printFunc(currElement);
        }
    }
}
