#ifndef SORT_TESTER
#define SORT_TESTER
#include <vector>
#include <chrono>
#include <cmath>

class SortTester {
    int threshold;

    void insertionSort(std::vector<int>& a, int l, int r) {
        for (int i = l + 1; i < r; ++i) {
            int key = a[i];
            int j = i - 1;
            while (j >= l && a[j] > key) {
                a[j + 1] = a[j];
                --j;
            }
            a[j + 1] = key;
        }
    }

    void heapify(std::vector<int>& a, int i, int n, int start) {
        int left = start + (i - start) * 2 + 1;
        int right = start + (i - start) * 2 + 2;

        int res = left < n && a[left] > a[i] ? left : i;
        res = right < n && a[right] > a[res] ? right : res;

        if (res != i) {
            std::swap(a[res], a[i]);
            heapify(a, res, n, start);
        }
    }

    void buildMaxHeap(std::vector<int>& a, int start, int end) {
        int n = end - start + 1;

        for (int i = start + n / 2 - 1; i >= start; --i) {
            heapify(a, i, end + 1, start);
        }
    }

    void heapSort(std::vector<int>& a, int start, int end) {
        buildMaxHeap(a, start, end);

        for (int i = end; i > start; --i) {
            std::swap(a[i], a[start]);
            heapify(a, start, i, start);
        }
    }

    int partition(std::vector<int>& a, int l, int r) {
        int pivot = a[l];
        int k = r;
        for (int i = r; i > l; i--) {
            if (a[i] > pivot)
                std::swap(a[i], a[k--]);
        }
        std::swap(a[l], a[k]);
        return k;
    }

    void combinedSort(std::vector<int>& a, int l, int r, int deep) {
        if (deep == threshold) {
            heapSort(a, l, r);
            return;
        }
        if (r - l < 15) {
            insertionSort(a, l, r + 1);
            return;
        }
        if (l < r) {
            int pivot = partition(a, l, r);
            combinedSort(a, l, pivot - 1, deep + 1);
            combinedSort(a, pivot + 1, r, deep + 1);
        }
    }

    void quickSort(std::vector<int>& a, int l, int r) {
        if (l < r) {
            int pivot = partition(a, l, r);
            quickSort(a, l, pivot - 1);
            quickSort(a, pivot + 1, r);
        }
    }

    public:

    SortTester() {}

    int test(std::vector<int>& a) {
        threshold = 2 * log2(a.size());
        int n = a.size() - 1;
        auto start = std::chrono::high_resolution_clock::now();
        combinedSort(a, 0, n, 0);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }

    int testQuick(std::vector<int>& a) {
        int n = a.size() - 1;
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(a, 0, n);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }
};

#endif