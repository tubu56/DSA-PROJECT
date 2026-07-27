#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct DataItem {
    int value;
};

void populateDataset(struct DataItem dataset[], int count) {
    for (int idx = 0; idx < count; idx++) {
        dataset[idx].value = rand() % 1000 + 1;
    }
}

void showAllEntries(DataItem dataset[], int count) {
    cout << "\n------ ALL RECORDS ------\n";

    for (int idx = 0; idx < count; idx++) {
        cout << "Record " << idx + 1 << ": " << dataset[idx].value << endl;
    }

    cout << endl;
}

void selectionSortAlgo(DataItem dataset[], int count) {
    for (int outer = 0; outer < count - 1; outer++) {
        int minPos = outer;

        for (int inner = outer + 1; inner < count; inner++) {
            if (dataset[inner].value < dataset[minPos].value) {
                minPos = inner;
            }
        }

        DataItem swapTemp = dataset[outer];
        dataset[outer] = dataset[minPos];
        dataset[minPos] = swapTemp;
    }

    cout << "\nSelection Sort completed.\n\n";
}

int partitionData(DataItem dataset[], int lowBound, int highBound) {
    int pivotValue = dataset[highBound].value;

    int boundary = lowBound - 1;

    for (int scan = lowBound; scan < highBound; scan++) {
        if (dataset[scan].value < pivotValue) {
            boundary++;

            DataItem swapTemp = dataset[boundary];
            dataset[boundary] = dataset[scan];
            dataset[scan] = swapTemp;
        }
    }
    DataItem swapTemp = dataset[boundary + 1];
    dataset[boundary + 1] = dataset[highBound];
    dataset[highBound] = swapTemp;

    return boundary + 1;
}

void quickSortAlgo(DataItem dataset[], int lowBound, int highBound) {
    if (lowBound < highBound) {
        int splitPos = partitionData(dataset, lowBound, highBound);

        quickSortAlgo(dataset, lowBound, splitPos - 1);
        quickSortAlgo(dataset, splitPos + 1, highBound);
    }
}

void mergeArrays(DataItem dataset[], int startPos, int middlePos, int endPos) {
    int leftSize = middlePos - startPos + 1;
    int rightSize = endPos - middlePos;

    DataItem leftPart[leftSize];
    DataItem rightPart[rightSize];

    for (int idx = 0; idx < leftSize; idx++)
        leftPart[idx] = dataset[startPos + idx];

    for (int idx = 0; idx < rightSize; idx++)
        rightPart[idx] = dataset[middlePos + 1 + idx];

    int leftIdx = 0;
    int rightIdx = 0;
    int mergePos = startPos;

    while (leftIdx < leftSize && rightIdx < rightSize) {
        if (leftPart[leftIdx].value <= rightPart[rightIdx].value) {
            dataset[mergePos] = leftPart[leftIdx];
            leftIdx++;
        }
        else {
            dataset[mergePos] = rightPart[rightIdx];
            rightIdx++;
        }
        mergePos++;
    }

    while (leftIdx < leftSize) {
        dataset[mergePos] = leftPart[leftIdx];
        leftIdx++;
        mergePos++;
    }

    while (rightIdx < rightSize) {
        dataset[mergePos] = rightPart[rightIdx];
        rightIdx++;
        mergePos++;
    }
}

void mergeSortAlgo(DataItem dataset[], int startPos, int endPos) {
    if (startPos < endPos) {
        int middlePos = (startPos + endPos) / 2;

        mergeSortAlgo(dataset, startPos, middlePos);
        mergeSortAlgo(dataset, middlePos + 1, endPos);

        mergeArrays(dataset, startPos, middlePos, endPos);
    }
}

int binarySearchAlgo(DataItem dataset[], int count, int target)
{
    int lowBound = 0;
    int highBound = count - 1;

    while (lowBound <= highBound) {
        int middlePos = (lowBound + highBound) / 2;

        if (dataset[middlePos].value == target) {
            return middlePos;
        }

        else if (dataset[middlePos].value < target) {
            lowBound = middlePos + 1;
        }

        else {
            highBound = middlePos - 1;
        }
    }
    return -1;
}

int interpolationSearchAlgo(DataItem dataset[], int count, int target) {
    int lowBound = 0;
    int highBound = count - 1;

    while (lowBound <= highBound && target >= dataset[lowBound].value && target <= dataset[highBound].value) {
        if (dataset[highBound].value == dataset[lowBound].value) {
            if (dataset[lowBound].value == target)
                return lowBound;
            else
                return -1;
        }

        int estimatePos = lowBound + ((target - dataset[lowBound].value) * (highBound - lowBound)) / (dataset[highBound].value - dataset[lowBound].value);

        if (dataset[estimatePos].value == target)
            return estimatePos;

        if (dataset[estimatePos].value < target)
            lowBound = estimatePos + 1;
        else
            highBound = estimatePos - 1;
    }
    return -1;
}

int main() {
    DataItem dataset[100];
    bool sortedFlag = false;

    srand(time(NULL));
    populateDataset(dataset, 100);

    int menuChoice;

    do {
        cout << "====== MENU ======\n";
        cout << "1. Display All Records\n";
        cout << "2. Sort Records\n";
        cout << "3. Search Number\n";
        cout << "4. Regenerate Records\n";
        cout << "5. Exit\n";

        cout << "Enter Choice: ";
        cin >> menuChoice;

        switch (menuChoice) {
            case 1:
                showAllEntries(dataset, 100);
                break;

            case 2: {
                int sortOption;

                cout << "\n------ SORT RECORDS ------\n";
                cout << "1. Selection Sort\n";
                cout << "2. Quick Sort\n";
                cout << "3. Merge Sort\n";

                cout << "Enter Choice: ";
                cin >> sortOption;

                switch (sortOption) {
                    case 1:
                        selectionSortAlgo(dataset, 100);
                        sortedFlag = true;
                        break;

                    case 2:
                        quickSortAlgo(dataset, 0, 99);
                        sortedFlag = true;
                        cout << "\nQuick Sort completed.\n\n";
                        break;

                    case 3:
                        mergeSortAlgo(dataset, 0, 99);
                        sortedFlag = true;
                        cout << "\nMerge Sort completed.\n\n";
                        break;

                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            }

            case 3: {
                int searchOption;
                int target;
                int foundIndex;

                if (!sortedFlag) {
                    cout << "Please sort the records before searching.\n";
                    break;
                }

                else {
                    cout << "\n------ Search Number ------\n";
                    cout << "1. Binary Search\n";
                    cout << "2. Interpolation Search\n";

                    cout << "Enter Choice: ";
                    cin >> searchOption;

                    cout << "Enter number to search: ";
                    cin >> target;

                    switch (searchOption) {
                        case 1:
                            foundIndex = binarySearchAlgo(dataset, 100, target);

                            if (foundIndex != -1)
                                cout << "\nNumber found at Record " << foundIndex + 1 << "\n\n";
                            else
                                cout << "\nNumber not found.\n\n";
                            break;

                        case 2:
                            foundIndex = interpolationSearchAlgo(dataset, 100, target);

                            if (foundIndex != -1)
                                cout << "\nNumber found at Record " << foundIndex + 1 << "\n\n";
                            else
                                cout << "\nNumber not found.\n\n";

                            break;

                        default:
                            cout << "Invalid choice.\n\n";
                    }
                }
                break;
            }

            case 4:
                populateDataset(dataset, 100);
                sortedFlag = false;

                cout << "New Records generated successfully.\n";
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (menuChoice != 5);

    return 0;
}
