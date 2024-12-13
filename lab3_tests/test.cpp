#include "pch.h"
#include "../lab3_with_tests/sort.h"
#include <random>
#include <vector>
#include <chrono>

using namespace std;

void generateRandomArray(int* arr, int size, int seed = 30) {
    mt19937 gen(seed);
    uniform_int_distribution<> dist(1, 1000000);

    for (int i = 0; i < size; ++i) {
        arr[i] = dist(gen);
    }
}

void generateBackwardsArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
}

// TESTS
TEST(InsertionSortTest, SortSmallArray) {
    int arr[] = {3, 4, 1, 2 };
    insertionSort(arr, arr + 4, [](int a, int b) { return a < b; });
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
}

TEST(QuickSortTest, SortArray) {
    int arr[] = { 10, 5, 3, 7, 6, 1, 9, 8, 4, 2 };
    quickSort(arr, arr + 10, [](int a, int b) { return a < b; });
    for (int i = 0; i < 9; ++i) {
        EXPECT_LE(arr[i], arr[i + 1]);
    }
}

TEST(MedianOfThreeTest, CorrectMedian) {
    int arr[] = { 4, 5, 7, 10, 1, 2, -1 };

    int* first = arr;
    int* last = arr + 7;
    int* mid = mid = first + (last - first) / 2;

    auto median = medianOfThree(first, mid, last, [](int a, int b) { return a < b; });
    EXPECT_EQ(median, 4);
}

TEST(QuickSortTest, SortWithDoubleAndNegativeNumbers) {
    double arr[] = { 1.4, -2.1, 3.4, -4.3, 5.33, 0.1 };
    quickSort(arr, arr + 6, [](double a, double b) { return a < b; });
    EXPECT_EQ(arr[0], -4.3);
    EXPECT_EQ(arr[1], -2.1);
    EXPECT_EQ(arr[2], 0.1);
    EXPECT_EQ(arr[3], 1.4);
}

// Тест для очень большого массива
TEST(QuickSortTest, SortLargeArray) {
    const int size = 1000;
    int arr[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    quickSort(arr, arr + size, [](int a, int b) { return a < b; });
    for (int i = 0; i < size - 1; ++i) {
        EXPECT_LE(arr[i], arr[i + 1]);
    }
}

TEST(SortingTest, SortStringsAlphabetically) {
    std::string strings[] = { "banana", "apple", "cherry", "date" };
    std::string expected[] = { "apple", "banana", "cherry", "date" };
    int size = sizeof(strings) / sizeof(strings[0]);

    quickSort(strings, strings + size, [](const std::string& a, const std::string& b) {
        return a < b;
        });

    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(strings[i], expected[i]);
    }
}

TEST(SortingTest, SortStringsByLength) {
    std::string strings[] = { "kiwi", "pineapple", "pear", "apple" };
    std::string expected[] = { "kiwi", "pear", "apple", "pineapple" };
    int size = sizeof(strings) / sizeof(strings[0]);

    quickSort(strings, strings + size, [](const std::string& a, const std::string& b) {
        return a.size() < b.size();
        });

    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(strings[i], expected[i]);
    }
}

TEST(SortingTest, SortStringsReverseAlphabetical) {
    std::string strings[] = { "banana", "apple", "cherry", "date" };
    std::string expected[] = { "date", "cherry", "banana", "apple" };
    int size = sizeof(strings) / sizeof(strings[0]);

    quickSort(strings, strings + size, [](const std::string& a, const std::string& b) {
        return a > b;
        });

    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(strings[i], expected[i]);
    }
}

int main(int argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);

    int testSizes[] = { 4, 8, 16, 20, 25, 30, 32, 35, 64, 128, 250, 500, 1000, 2000};

    std::cout << "system_clock resolution: "
        << std::chrono::system_clock::period::num << "/"
        << std::chrono::system_clock::period::den << " seconds per tick\n";

    std::cout << "\n==========BENCHMARK==========\n\n";

    std::cout << "INSERT SORT AND CLASSIC QUICK SORT TEST\n\n";

    for (int size : testSizes) {
        std::vector<int> arr(size);
        generateBackwardsArray(arr.data(), size);

        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(arr.data(), arr.data() + size, [](int a, int b) { return a < b; });
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> insertionSortTime = end - start;

        generateBackwardsArray(arr.data(), size);

        start = std::chrono::high_resolution_clock::now();
        simpleQuickSort(arr.data(), arr.data() + size, [](int a, int b) { return a < b; });
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> quickSortWithoutInsertTime = end - start;

        std::cout << "Size: " << size
            << "  InsertionSort: " << insertionSortTime.count()
            << "s, ClassicQuickSort: " << quickSortWithoutInsertTime.count()
             << "s\n";
    }

    std::cout << "\n\nCLASSIC QUICK SORT AND COOL QUICK SORT TEST\n\n";

    for (int size : testSizes) {
        std::vector<int> arr(size);

        generateBackwardsArray(arr.data(), size);

        auto start = std::chrono::high_resolution_clock::now();
        simpleQuickSort(arr.data(), arr.data() + size, [](int a, int b) { return a < b; });
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> quickSortWithoutInsertTime = end - start;

        generateBackwardsArray(arr.data(), size);

        start = std::chrono::high_resolution_clock::now();
        quickSort(arr.data(), arr.data() + size, [](int a, int b) { return a < b; });
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> quickSortTime = end - start;

        std::cout << "Size: " << size
            << "  ClassicQuickSort: " << quickSortWithoutInsertTime.count()
            << "s, QuickSort: " << quickSortTime.count() << "s\n";
    }

    std::cout << "\n==========UNIT TESTS==========\n\n";

    return RUN_ALL_TESTS();
}