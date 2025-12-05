//
// Created by Aidan on 10/2/2025.
//

#include "SortUtil.h"
#include "ArrayUtil.h"
#include "Card.h"

void selectionSort(int arr[], const int size) {
    int i = 0;
    while (i < size - 1 && arr[i] <= arr[i + 1]) i++;
    if (i >= size - 1) return;
    int minIndex = i;
    for (int j = i + 1; j < size; j++) if (arr[j] < arr[minIndex]) minIndex = j;
    if (minIndex != i) swap(arr, i, minIndex);
}

void bubbleSort(int arr[], const int size) {
    for (int j = 0; j < size - 1; j++) if (arr[j] > arr[j + 1]) swap(arr, j, j + 1);
}

void insertionSort(int arr[], const int size) { // TODO CURRENTLY BUBLE SORT WITH ONE SEARCH
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        if (arr[j] > key) {
            arr[j + 1] = arr[j];
            arr[j] = key;
            break;
        }
    }
}

void quickSort(int arr[], const int size) {
    int left = 0; // Find a region that is not sorted
    while (left < size - 1 && arr[left] <= arr[left + 1]) left++;
    if (left >= size - 1) return;
    int right = left + 1; // Find the right end of that unsorted region
    while (right < size - 1 && arr[right] > arr[right + 1]) right++;
    const int pivotIndex = (left + right) / 2; // Choose a pivot *inside* the region (not necessarily last)
    const int pivot = arr[pivotIndex];
    int i = left, j = right; // Partition only this region
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr, i, j);
            i++;
            j--;
        }
    }
}

void mergeSort(int arr[], int size) {
    int left = 0; // Find first unsorted region
    while (left < size - 1 && arr[left] <= arr[left + 1]) left++;
    if (left >= size - 1) return;
    int right = left + 1;
    while (right < size - 1 && arr[right] > arr[right + 1]) right++;
    const int mid = (left + right) / 2;
    const int n = right - left + 1;
    const auto tmp = new int[n];  // temporary array
    int i = left;      // pointer for left half
    int j = mid + 1;   // pointer for right half
    int k = 0;         // pointer for tmp[]
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= right) tmp[k++] = arr[j++];
    for (int p = 0; p < n; p++) arr[left + p] = tmp[p];
    delete[] tmp;
}

void bucketSort(int arr[], const int size) {
    const int bucketCount = std::max(2, size / 3);  // scale buckets with array size
    const auto buckets = new int*[bucketCount]; // Allocate buckets
    const auto bucketSizes = new int[bucketCount];
    for (int b = 0; b < bucketCount; b++) bucketSizes[b] = 0;
    for (int b = 0; b < bucketCount; b++) buckets[b] = new int[size];
    int minVal = arr[0], maxVal = arr[0]; // Find min and max
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    if (minVal == maxVal) {
        for (int b = 0; b < bucketCount; b++) delete[] buckets[b]; // clean up
        delete[] buckets;
        delete[] bucketSizes;
        return;
    }
    for (int i = 0; i < size; i++) { // Put elements into buckets
        int idx = static_cast<int>(static_cast<double>(arr[i] - minVal) / (maxVal - minVal + 1) * bucketCount);
        if (idx >= bucketCount) idx = bucketCount - 1;
        buckets[idx][bucketSizes[idx]++] = arr[i];
    }
    for (int b = 0; b < bucketCount; b++) { // Incremental sort: one swap per bucket
        int* bucket = buckets[b];
        int n = bucketSizes[b];
        for (int i = 1; i < n; i++) {
            if (bucket[i] < bucket[i - 1]) {
                swap(bucket, i, i - 1);
                break; // only one step per bucket
            }
        }
    }
    int k = 0; // Merge buckets back into arr[]
    for (int b = 0; b < bucketCount; b++) {
        for (int i = 0; i < bucketSizes[b]; i++) {
            arr[k++] = buckets[b][i];  // this actually updates arr[]
        }
    }
    for (int b = 0; b < bucketCount; b++) delete[] buckets[b]; // Clean up
    delete[] buckets;
    delete[] bucketSizes;
}

void swap(int arr[], const int i, const int j) {
    const int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void printArray(const int arr[], const int size) {
    std::cout << "Array: ";
    for (int i = 0; i < size; i++) std::cout << arr[i] << " ";
    std::cout << std::endl;
}

bool isSorted(const int arr[], const int size) {
    for (int i = 1; i < size; i++) if (arr[i] < arr[i - 1]) return false;
    return true;
}

bool contains(const int arr[], const int len, const int elem) {
    for (int i = 0; i < len; ++i) if (arr[i] == elem) return true;
    return false;
}

string jsonifyArray(const int arr[], const int size) {
    if (arr == nullptr) return "{\"array\":[]}";
    string result = "{\"array\":[";
    for (int i = 0; i < size; i++) {
        result += std::to_string(arr[i]);
        if (i < size - 1) result += ",";
    }
    return result += "]}";
}
