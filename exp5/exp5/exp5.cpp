#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Helper function to generate a sorted array
std::vector<int> generateSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }
    return arr;
}

// Helper function to generate a reverse sorted array
std::vector<int> generateReverseSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i - 1;
    }
    return arr;
}

// Helper function to generate a random array
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Bubble Sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

// Merge Sort helper functions
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort helper functions
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Heap Sort helper functions
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Function to measure the time taken by a sorting algorithm
template <typename Func>
double measureTime(Func func, std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    func(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    const int size = 2000; // You can change the size as needed
    std::vector<int> sortedArr = generateSortedArray(size);
    std::vector<int> reversedArr = generateReverseSortedArray(size);
    std::vector<int> randomArr = generateRandomArray(size);

    std::cout << "Performance of different sorting algorithms:\n";
    std::cout << "Size: " << size << "\n\n";

    // Test Bubble Sort
    std::cout << "Bubble Sort:\n";
    std::cout << "Sorted Array: " << measureTime([&](auto& arr) { bubbleSort(arr); }, sortedArr) << " seconds\n";
    std::cout << "Reversed Array: " << measureTime([&](auto& arr) { bubbleSort(arr); }, reversedArr) << " seconds\n";
    std::cout << "Random Array: " << measureTime([&](auto& arr) { bubbleSort(arr); }, randomArr) << " seconds\n\n";

    // Test Insertion Sort
    std::cout << "Insertion Sort:\n";
    std::cout << "Sorted Array: " << measureTime([&](auto& arr) { insertionSort(arr); }, sortedArr) << " seconds\n";
    std::cout << "Reversed Array: " << measureTime([&](auto& arr) { insertionSort(arr); }, reversedArr) << " seconds\n";
    std::cout << "Random Array: " << measureTime([&](auto& arr) { insertionSort(arr); }, randomArr) << " seconds\n\n";

    // Test Selection Sort
    std::cout << "Selection Sort:\n";
    std::cout << "Sorted Array: " << measureTime([&](auto& arr) { selectionSort(arr); }, sortedArr) << " seconds\n";
    std::cout << "Reversed Array: " << measureTime([&](auto& arr) { selectionSort(arr); }, reversedArr) << " seconds\n";
    std::cout << "Random Array: " << measureTime([&](auto& arr) { selectionSort(arr); }, randomArr) << " seconds\n\n";

    // Test Merge Sort
    std::cout << "Merge Sort:\n";
    std::cout << "Sorted Array: " << measureTime([&](auto& arr) { mergeSort(arr, 0, arr.size() - 1); }, sortedArr) << " seconds\n";
    std::cout << "Reversed Array: " << measureTime([&](auto& arr) { mergeSort(arr, 0, arr.size() - 1); }, reversedArr) << " seconds\n";
    std::cout << "Random Array: " << measureTime([&](auto& arr) { mergeSort(arr, 0, arr.size() - 1); }, randomArr) << " seconds\n\n";

    // Test Quick Sort
    std::cout << "Quick Sort:\n";
    std::cout << "Sorted Array: " << measureTime([&](auto& arr) { quickSort(arr, 0, arr.size() - 1); }, sortedArr) << " seconds\n";
    std::cout << "Reversed Array: " << measureTime([&](auto& arr) { quickSort(arr, 0, arr.size() - 1); }, reversedArr) << " seconds\n";
    std::cout << "Random Array: " << measureTime([&](auto& arr) { quickSort(arr, 0, arr.size() - 1); }, randomArr) << " seconds\n\n";

    // Test Heap Sort
    std::cout << "Heap Sort:\n";
    std::cout << "Sorted Array: " << measureTime([&](auto& arr) { heapSort(arr); }, sortedArr) << " seconds\n";
    std::cout << "Reversed Array: " << measureTime([&](auto& arr) { heapSort(arr); }, reversedArr) << " seconds\n";
    std::cout << "Random Array: " << measureTime([&](auto& arr) { heapSort(arr); }, randomArr) << " seconds\n\n";

    return 0;
}


