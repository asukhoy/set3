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

    void combinedSort(std::vector<int>& a, int l, int r) {
        if (r - l <= threshold) {
            insertionSort(a, l, r);
            return;
        }
    
        int mid = (r + l) / 2;
        combinedSort(a, l, mid);
        combinedSort(a, mid, r);
    
        std::vector<int> left(mid - l);
        for (int i = l; i < mid; ++i) {
            left[i - l] = a[i];
        }
        std::vector<int> right(r - mid);
        for (int i = mid; i < r; ++i) {
            right[i - mid] = a[i];
        }
    
        int lft = 0, rgt = 0;
        while (lft < mid - l && rgt < r - mid) {
            if (left[lft] < right[rgt]) {
                a[l + lft + rgt] = left[lft];
                ++lft;
            } else {
                a[l + lft + rgt] = right[rgt];
                ++rgt;
            }
        }
        while (lft < mid - l) {
            a[l + lft + rgt] = left[lft];
            ++lft;
        }
        while (rgt < r - mid) {
            a[l + lft + rgt] = right[rgt];
            ++rgt;
        }
    }

    void mergeSort(std::vector<int>& a, int l, int r) {
        if (r - l == 1) {
            return;
        }
    
        int mid = (r + l) / 2;
        mergeSort(a, l, mid);
        mergeSort(a, mid, r);
    
        std::vector<int> left(mid - l);
        for (int i = l; i < mid; ++i) {
            left[i - l] = a[i];
        }
        std::vector<int> right(r - mid);
        for (int i = mid; i < r; ++i) {
            right[i - mid] = a[i];
        }
    
        int lft = 0, rgt = 0;
        while (lft < mid - l && rgt < r - mid) {
            if (left[lft] < right[rgt]) {
                a[l + lft + rgt] = left[lft];
                ++lft;
            } else {
                a[l + lft + rgt] = right[rgt];
                ++rgt;
            }
        }
        while (lft < mid - l) {
            a[l + lft + rgt] = left[lft];
            ++lft;
        }
        while (rgt < r - mid) {
            a[l + lft + rgt] = right[rgt];
            ++rgt;
        }
    }

    public:

    SortTester(int a = 5) {
        threshold = a;
    }

    int test(std::vector<int>& a) {
        int n = a.size();
        auto start = std::chrono::high_resolution_clock::now();
        combinedSort(a, 0, n);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }

    int testMerge(std::vector<int>& a) {
        int n = a.size();
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(a, 0, n);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }
};

#endif