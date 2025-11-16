#ifndef ARRAY_GENERATOR
#define ARRAY_GENERATOR
#include <vector>
#include <random>
#include <algorithm>
#include <functional>

class ArrayGenerator {
    const int _N = 100000;
    std::vector<int> _rnd;
    std::vector<int> _sortedBackwards;
    std::vector<int> _almostSorted;
    std::vector<int> _curRnd;
    std::vector<int> _curSortedBackwards;
    std::vector<int> _curAlmostSorted;
    std::mt19937 mt;

    void _Generate(std::vector<int>& a) {
        for (int i = 0; i < _N; ++i) {
            a[i] = mt() % 6001;
        }
    }

    void _GenerateRandom() {
        _Generate(_rnd);
    }

    void _GenerateBackwards() {
        _Generate(_sortedBackwards);
        std::sort(_sortedBackwards.begin(), _sortedBackwards.end(), std::greater<int>());
    }

    void _GenerateAlmost() {
        _Generate(_almostSorted);
        std::sort(_almostSorted.begin(), _almostSorted.end());
        for (int i = 0; i < 100; ++i) {
            int i1 = mt() % _N;
            int i2 = mt() % _N;
            std::swap(_almostSorted[i1], _almostSorted[i2]);
        }
    }

    void _nextRandom() {
        int m = _curRnd.size();
        if (m == _N) {
            return;
        }
        int n = m == 0 ? 500 : m + 100;
        for (int i = m; i < n; ++i) {
            _curRnd.emplace_back(_rnd[i]);
        }
    }

    void _nextBackwards() {
        int m = _curSortedBackwards.size();
        if (m == _N) {
            return;
        }
        int n = m == 0 ? 500 : m + 100;
        for (int i = m; i < n; ++i) {
            _curSortedBackwards.emplace_back(_sortedBackwards[i]);
        }
    }

    void _nextAlmost() {
        int m = _curAlmostSorted.size();
        if (m == _N) {
            return;
        }
        int n = m == 0 ? 500 : m + 100;
        for (int i = m; i < n; ++i) {
            _curAlmostSorted.emplace_back(_almostSorted[i]);
        }
    }

    public:

    ArrayGenerator() {
        _rnd.resize(_N);
        _sortedBackwards.resize(_N);
        _almostSorted.resize(_N);
        mt.seed(67);
        _GenerateRandom();
        _GenerateBackwards();
        _GenerateAlmost();
    }

    std::vector<int> getRandom() {
        _nextRandom();
        return _curRnd;
    }

    std::vector<int> getBackwards() {
        _nextBackwards();
        return _curSortedBackwards;
    }

    std::vector<int> getAlmost() {
        _nextAlmost();
        return _curAlmostSorted;
    }
};

#endif