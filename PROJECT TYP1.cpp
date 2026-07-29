#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <limits>
 
using namespace std;
 
long long operationTally = 0;
 
int readValidInt() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    return value;
}
 
struct Record {
    int number;
};
 
void generateRecords(struct Record collection[], int total) {
    for (int index = 0; index < total; index++) {
        collection[index].number = rand() % 1000 + 1;
    }
}
 
void displayAllRecords(Record collection[], int total) {
    cout << "\n------ ALL RECORDS ------\n";
 
    for (int index = 0; index < total; index++) {
        cout << "Record " << index + 1 << ": " << collection[index].number << endl;
    }
 
    cout << endl;
}
 
void selectionSortMethod(Record collection[], int total) {
    for (int outerIdx = 0; outerIdx < total - 1; outerIdx++) {
        int smallestPos = outerIdx;
 
        for (int innerIdx = outerIdx + 1; innerIdx < total; innerIdx++) {
            operationTally++;
            if (collection[innerIdx].number < collection[smallestPos].number) {
                smallestPos = innerIdx;
            }
        }
 
        Record temp = collection[outerIdx];
        collection[outerIdx] = collection[smallestPos];
        collection[smallestPos] = temp;
    }
 
    cout << "\nSelection Sort completed.\n\n";
}
 
int splitSegment(Record collection[], int lowerLimit, int upperLimit) {
    int pivot = collection[upperLimit].number;
 
    int divider = lowerLimit - 1;
 
    for (int cursor = lowerLimit; cursor < upperLimit; cursor++) {
        operationTally++;
        if (collection[cursor].number < pivot) {
            divider++;
 
            Record temp = collection[divider];
            collection[divider] = collection[cursor];
            collection[cursor] = temp;
        }
    }
    Record temp = collection[divider + 1];
    collection[divider + 1] = collection[upperLimit];
    collection[upperLimit] = temp;
 
    return divider + 1;
}
 
void quickSortMethod(Record collection[], int lowerLimit, int upperLimit) {
    if (lowerLimit < upperLimit) {
        int pivotIndex = splitSegment(collection, lowerLimit, upperLimit);
 
        quickSortMethod(collection, lowerLimit, pivotIndex - 1);
        quickSortMethod(collection, pivotIndex + 1, upperLimit);
    }
}
 
void combineSegments(Record collection[], int beginPos, int midPos, int finishPos) {
    int leftLength = midPos - beginPos + 1;
    int rightLength = finishPos - midPos;
 
    Record leftHalf[leftLength];
    Record rightHalf[rightLength];
 
    for (int index = 0; index < leftLength; index++)
        leftHalf[index] = collection[beginPos + index];
 
    for (int index = 0; index < rightLength; index++)
        rightHalf[index] = collection[midPos + 1 + index];
 
    int leftPointer = 0;
    int rightPointer = 0;
    int combinedPos = beginPos;
 
    while (leftPointer < leftLength && rightPointer < rightLength) {
        operationTally++;
        if (leftHalf[leftPointer].number <= rightHalf[rightPointer].number) {
            collection[combinedPos] = leftHalf[leftPointer];
            leftPointer++;
        }
        else {
            collection[combinedPos] = rightHalf[rightPointer];
            rightPointer++;
        }
        combinedPos++;
    }
 
    while (leftPointer < leftLength) {
        collection[combinedPos] = leftHalf[leftPointer];
        leftPointer++;
        combinedPos++;
    }
 
    while (rightPointer < rightLength) {
        collection[combinedPos] = rightHalf[rightPointer];
        rightPointer++;
        combinedPos++;
    }
}
 
void mergeSortMethod(Record collection[], int beginPos, int finishPos) {
    if (beginPos < finishPos) {
        int midPos = beginPos + (finishPos - beginPos) / 2;
 
        mergeSortMethod(collection, beginPos, midPos);
        mergeSortMethod(collection, midPos + 1, finishPos);
 
        combineSegments(collection, beginPos, midPos, finishPos);
    }
}
 
int binarySearchMethod(Record collection[], int total, int searchKey) {
    int lowerLimit = 0;
    int upperLimit = total - 1;
 
    while (lowerLimit <= upperLimit) {
        int midPos = lowerLimit + (upperLimit - lowerLimit) / 2;
 
        operationTally++;
        if (collection[midPos].number == searchKey)
            return midPos;
 
        if (collection[midPos].number < searchKey)
            lowerLimit = midPos + 1;
        else
            upperLimit = midPos - 1;
    }
    return -1;
}
 
int interpolationSearchMethod(Record collection[], int total, int searchKey) {
    int lowerLimit = 0;
    int upperLimit = total - 1;
 
    while (lowerLimit <= upperLimit &&
           searchKey >= collection[lowerLimit].number &&
           searchKey <= collection[upperLimit].number) {
 
        if (collection[upperLimit].number == collection[lowerLimit].number) {
            operationTally++;
            if (collection[lowerLimit].number == searchKey)
                return lowerLimit;
            break;
        }
 
        int guessPos = lowerLimit + ((searchKey - collection[lowerLimit].number) * (upperLimit - lowerLimit)) / (collection[upperLimit].number - collection[lowerLimit].number);
 
        operationTally++;
        if (collection[guessPos].number == searchKey)
            return guessPos;
 
        if (collection[guessPos].number < searchKey)
            lowerLimit = guessPos + 1;
        else
            upperLimit = guessPos - 1;
    }
    return -1;
}
 
int main() {
    Record collection[100];
    bool isSorted = false;
 
    srand(time(NULL));
    generateRecords(collection, 100);
 
    int userSelection;
 
    do {
        cout << "====== MENU ======\n";
        cout << "1. Display All Records\n";
        cout << "2. Sort Records\n";
        cout << "3. Search Number\n";
        cout << "4. Regenerate Records\n";
        cout << "5. Exit\n";
 
        cout << "Enter Choice: ";
        userSelection = readValidInt();
 
        switch (userSelection) {
            case 1:
                displayAllRecords(collection, 100);
                break;
 
            case 2: {
                int sortChoice;
 
                cout << "\n------ SORT RECORDS ------\n";
                cout << "1. Selection Sort\n";
                cout << "2. Quick Sort\n";
                cout << "3. Merge Sort\n";
 
                cout << "Enter Choice: ";
                sortChoice = readValidInt();
 
                switch (sortChoice) {
                    case 1: {
                        operationTally = 0;
                        clock_t beginClock = clock();
 
                        selectionSortMethod(collection, 100);
 
                        clock_t finishClock = clock();
                        double durationMs = double(finishClock - beginClock) / CLOCKS_PER_SEC * 1000;
 
                        isSorted = true;
                        cout << "Time taken: " << durationMs << " ms\n";
                        cout << "Comparisons: " << operationTally << "\n\n";
                        break;
                    }
 
                    case 2: {
                        operationTally = 0;
                        clock_t beginClock = clock();
 
                        quickSortMethod(collection, 0, 99);
 
                        clock_t finishClock = clock();
                        double durationMs = double(finishClock - beginClock) / CLOCKS_PER_SEC * 1000;
 
                        isSorted = true;
                        cout << "\nQuick Sort completed.\n";
                        cout << "Time taken: " << durationMs << " ms\n";
                        cout << "Comparisons: " << operationTally << "\n\n";
                        break;
                    }
 
                    case 3: {
                        operationTally = 0;
                        clock_t beginClock = clock();
 
                        mergeSortMethod(collection, 0, 99);
 
                        clock_t finishClock = clock();
                        double durationMs = double(finishClock - beginClock) / CLOCKS_PER_SEC * 1000;
 
                        isSorted = true;
                        cout << "\nMerge Sort completed.\n";
                        cout << "Time taken: " << durationMs << " ms\n";
                        cout << "Comparisons: " << operationTally << "\n\n";
                        break;
                    }
 
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            }
 
            case 3: {
                int searchChoice;
                int searchKey;
                int resultIndex;
 
                if (!isSorted) {
                    cout << "Please sort the records before searching.\n";
                    break;
                }
 
                else {
                    cout << "\n------ Search Number ------\n";
                    cout << "1. Binary Search\n";
                    cout << "2. Interpolation Search\n";
 
                    cout << "Enter Choice: ";
                    searchChoice = readValidInt();
 
                    cout << "Enter number to search: ";
                    searchKey = readValidInt();
 
                    switch (searchChoice) {
                        case 1: {
                            const int iterationTotal = 100000;
                            operationTally = 0;
                            clock_t beginClock = clock();
 
                            for (int repeatIdx = 0; repeatIdx < iterationTotal; repeatIdx++) {
                                resultIndex = binarySearchMethod(collection, 100, searchKey);
                            }
 
                            clock_t finishClock = clock();
                            double durationMs = double(finishClock - beginClock) / CLOCKS_PER_SEC * 1000 / iterationTotal;
                            long long meanComparisons = operationTally / iterationTotal;
 
                            if (resultIndex != -1)
                                cout << "\nNumber found at Record " << resultIndex + 1 << "\n";
                            else
                                cout << "\nNumber not found.\n";
 
                            cout << "Avg time taken: " << durationMs << " ms\n";
                            cout << "Avg comparisons: " << meanComparisons << "\n\n";
                            break;
                        }
 
                        case 2: {
                            const int iterationTotal = 100000;
                            operationTally = 0;
                            clock_t beginClock = clock();
 
                            for (int repeatIdx = 0; repeatIdx < iterationTotal; repeatIdx++) {
                                resultIndex = interpolationSearchMethod(collection, 100, searchKey);
                            }
 
                            clock_t finishClock = clock();
                            double durationMs = double(finishClock - beginClock) / CLOCKS_PER_SEC * 1000 / iterationTotal;
                            long long meanComparisons = operationTally / iterationTotal;
 
                            if (resultIndex != -1)
                                cout << "\nNumber found at Record " << resultIndex + 1 << "\n";
                            else
                                cout << "\nNumber not found.\n";
 
                            cout << "Avg time taken: " << durationMs << " ms\n";
                            cout << "Avg comparisons: " << meanComparisons << "\n\n";
                            break;
                        }
 
                        default:
                            cout << "Invalid choice.\n\n";
                    }
                }
                break;
            }
 
            case 4:
                generateRecords(collection, 100);
                isSorted = false;
 
                cout << "New Records generated successfully.\n";
                break;
 
            case 5:
                cout << "Exiting...\n";
                break;
 
            default:
                cout << "Invalid choice.\n";
        }
    } while (userSelection != 5);
 
    return 0;
}