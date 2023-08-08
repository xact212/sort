#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void swapIndicies(int inpArray[], int index1, int index2) {
    int temp = inpArray[index2];
    inpArray[index2] = inpArray[index1];
    inpArray[index1] = temp;
}

void bubbleSort(int inpArray[], int arrLen) {
    bool swapped = false;
    do {
        swapped = false;
        for (int i = 1; i < arrLen; i++) {
            if (inpArray[i] < inpArray[i - 1]) {
                swapIndicies(inpArray, i, i - 1);
                swapped = true;
            }
        }
    }
    while (swapped);
}

void printArray(int inpArray[], int arrLen, int start) {
    for (int i = start; i < arrLen; i++) {
        printf("%i ", inpArray[i]);
    }
    puts("\n");
}

int* merge(int part1[], int part1Size, int part2[], int part2Size) {
    int* master = malloc((part1Size + part2Size) * sizeof(int)); //final merged array will be the size of both arrays added together
    //loop through every element in first partition and compare it to every element in second partition
    int part1i = 0;
    int part2i = 0;
    int nextMasteri = 0;
    while (part1i < part1Size && part2i < part2Size) 
    {
        if (part1[part1i] < part2[part2i]) { //if unequal add lower to master
            master[nextMasteri] = part1[part1i];
            nextMasteri++;
            part1i++;
            continue;
        }
        else if (part2[part2i] < part1[part1i]) {
            master[nextMasteri] = part2[part2i];
            nextMasteri++;
            part2i++;
            continue;
        }
        else if (part1[part1i] == part2[part2i]) { //if equal add both to master
            master[nextMasteri] = part1[part1i];
            nextMasteri++;
            part1i++;
            master[nextMasteri] = part2[part2i];
            nextMasteri++;
            part2i++;
            continue;
        }
    }
    //mop up remaining elements
    while (part1i < part1Size) {
        master[nextMasteri] = part1[part1i];
        nextMasteri++;
        part1i++;
    }
    while (part2i < part2Size) {
        master[nextMasteri] = part2[part2i];
        nextMasteri++;
        part2i++;
    }
    return master;
}

void mergeSort(int inpArray[], int arrLen) {
    //partition step
    //partition array into 2 pieces
    int part1Start = 0;
    int part2Start;
    part2Start = (arrLen % 2 == 0) ? arrLen / 2 : (arrLen + 1) / 2; //ensures successful partition whether array length is even or odd
    //allocate space for new sub arrays
    int part1Size = part2Start;
    int part2Size = arrLen - part2Start;
    int* part1 = malloc(part1Size * sizeof(int));
    int* part2 = malloc(part2Size * sizeof(int));
    //copy values from input array into each partition array
    for (int i = part1Start; i < part2Start; i++) {part1[i] = inpArray[i];}
    for (int i = part2Start; i < arrLen; i++) {part2[i - part2Start] = inpArray[i];}
    if (part1Size > 1 && part2Size > 1) {
        mergeSort(part1, part1Size);
        mergeSort(part2, part2Size);
    }
    //merge step
    int* master;
    master = merge(part1, part1Size, part2, part2Size);
    for (int i = 0; i < arrLen; i++) {inpArray[i] = master[i];}
    free(part1);
    free(part2);
    free(master);
}

void quickSort(int inpArray[], int start, int end) {
    int arrLen = (end - start) + 1;
    if (arrLen < 2) //if current array is < than 2 elements, return
        return;
    int frontIndex = start; //initialize iterators
    int backIndex = start - 1;
    int pivotIndex = end;
    int pivot = inpArray[pivotIndex];
    while (frontIndex < pivotIndex) { //loop through array
        if (inpArray[frontIndex] < pivot) {
            backIndex++;
            swapIndicies(inpArray, backIndex, frontIndex);
            frontIndex++;
        } 
        else
            frontIndex++;
    }
    backIndex++; //when frontIndex == pivotIndex, increment backIndex and swap the front with the back
    swapIndicies(inpArray, backIndex, frontIndex);
    quickSort(inpArray, start, backIndex - 1); //less than pivot
    quickSort(inpArray, backIndex + 1, end); //greater than pivot
}

unsigned int findHighestVal(unsigned int inpArray[], int arrLen) { 
    unsigned int max = 0; 
    for (int i = 0; i < arrLen; i++) 
        max = (inpArray[i] > max) ? inpArray[i] : max;
    return max;
}

//needs to be unsigned so we dont try to assign a value to an array at a negative index
//construct sorted array by counted number of occourences of each value. this work best if the range of values is pretty low and you know there will be no extreme outliers
void countSort(unsigned int inpArray[], int arrLen) {
    unsigned int highestVal = findHighestVal(inpArray, arrLen);
    unsigned int counts[highestVal + 1];
    for (int i = 0; i < highestVal + 1; i++) {counts[i] = 0;}
    //loop through input array. whatever current value is add one to the corresponding index in counts array
    for (int i = 0; i < arrLen; i++) 
        counts[inpArray[i]]++; //increment value at the index in counts that corresponds to the value at i in the input array
    int inpArrayIter = 0;
    //loop through whole counts array
    for (int i = 0; i < highestVal + 1; i++) {
        //write the current index to the input array the current value at the current index times
        for (int j = 0; j < counts[i]; j++) {
            inpArray[inpArrayIter] = i;
            inpArrayIter++;
        }
    }
}

//selects less of the two array lengths as its iteration amount
void copyArray(int origin[], int destination[], int originLen, int destinationLen) { 
    int iterAmnt = (originLen < destinationLen) ? originLen : destinationLen;
    for (int i = 0; i < iterAmnt; i++) 
        destination[i] = origin[i];
}


int main() {
    time_t t;
    srand((unsigned) time(&t));
    int initConfig[] = {8, 2, 4, 7, 1, 3, 9, 6, 5};
    int arrLen = sizeof(initConfig)/sizeof(int);
    int myArray[arrLen];
    copyArray(initConfig, myArray, arrLen, arrLen);
    puts("quicksort");
    printArray(myArray, arrLen, 0);
    quickSort(myArray, 0, arrLen - 1);
    printArray(myArray, arrLen, 0);
    copyArray(initConfig, myArray, arrLen, arrLen);
    puts("bubblesort");
    printArray(myArray, arrLen, 0);
    bubbleSort(myArray, arrLen);
    printArray(myArray, arrLen, 0);
    copyArray(initConfig, myArray, arrLen, arrLen);
    puts("mergesort");
    printArray(myArray, arrLen, 0);
    bubbleSort(myArray, arrLen);
    printArray(myArray, arrLen, 0);
    copyArray(initConfig, myArray, arrLen, arrLen);
    puts("countsort");
    printArray(myArray, arrLen, 0);
    countSort(myArray, arrLen);
    printArray(myArray, arrLen, 0);
}