#include <iostream>
#include <vector>
#include <thread>
#include <windows.h>
#include <numeric>
#include <limits>

std::vector<int> array;
int minValue = (std::numeric_limits<int>::max)();
int maxValue = (std::numeric_limits<int>::min)();
double averageValue = 0.0;

DWORD WINAPI findMinMax(LPVOID lpParam) {
    for (size_t i = 0; i < array.size(); ++i) {
        if (array[i] < minValue) {
            minValue = array[i];
        }
        if (array[i] > maxValue) {
            maxValue = array[i];
        }
        Sleep(7);
    }
    std::cout << "Min: " << minValue << ", Max: " << maxValue << std::endl;
    return 0;
}

DWORD WINAPI calculateAverage(LPVOID lpParam) {
    int sum = 0;
    for (size_t i = 0; i < array.size(); ++i) {
        sum += array[i];
        Sleep(12);
    }
    averageValue = static_cast<double>(sum) / array.size();
    Sleep(15);
    std::cout << "Average: " << averageValue << std::endl;
    return 0;
}

int main() {
    size_t size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    array.resize(size);
    std::cout << "Enter the elements of the array: ";
    for (size_t i = 0; i < size; ++i) {
        std::cin >> array[i];
    }

    HANDLE hMinMax = CreateThread(NULL, 0, findMinMax, NULL, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, calculateAverage, NULL, 0, NULL);

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    for (size_t i = 0; i < size; ++i) {
        if (array[i] == minValue || array[i] == maxValue) {
            array[i] = static_cast<int>(averageValue);
        }
    }

    std::cout << "Modified array: ";
    for (const int& elem : array) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
