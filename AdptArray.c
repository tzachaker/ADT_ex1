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

//*****************************************************************************
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

//*****************************************************************************
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

//*****************************************************************************

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

//*****************************************************************************

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

//*****************************************************************************
int GetAdptArraySize(PAdptArray adptArr) {
    if (adptArr == NULL){
        return -1;
    }
    return adptArr->sizeAdptArray;
}

//*****************************************************************************
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

//*****************************************************************************