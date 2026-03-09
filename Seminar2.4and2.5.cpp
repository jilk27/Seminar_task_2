// Seminar2.4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

class TaskTimer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void end() {
        end_time = std::chrono::high_resolution_clock::now();
    }

    long duration() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    }
};

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortHelper(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void mergeSort(std::vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(std::vector<int>& arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}

void stdSort(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
}

int main()
{
    int size;
    std::cin >> size;
    std::vector<int> arr1(size);
    std::vector<int> arr2(size);
    std::vector<int> arr3(size);
    std::vector<int> arr4(size);
    std::vector<int> arr5(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    for (int i = 0; i < size; i++) {
        arr1[i] = dis(gen);
        arr2[i] = dis(gen);
        arr3[i] = dis(gen);
        arr4[i] = dis(gen);
        arr5[i] = dis(gen);
    }

    TaskTimer time;
    time.start();
    bubbleSort(arr1);
    time.end();
    std::cout << "buble " << time.duration() << " mseconds need" << std::endl;

    time.start();
    insertionSort(arr2);
    time.end();
    std::cout << "insertion " << time.duration() << " mseconds need" << std::endl;

    time.start();
    mergeSort(arr3);
    time.end();
    std::cout << "merge " << time.duration() << " mseconds need" << std::endl;

    time.start();
    quickSort(arr4);
    time.end();
    std::cout << "quick " << time.duration() << " mseconds need" << std::endl;

    time.start();
    stdSort(arr5);
    time.end();
    std::cout << "og " << time.duration() << " mseconds need" << std::endl;
    std::cout << "Hello World!\n";
}
