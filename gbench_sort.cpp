// comparing sort algorithms with Google Benchmark
// Author: Jeff Trull <edaskel@att.net>

#include <benchmark/benchmark.h>

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <iterator>

int
qs_comparator( void const * a, void const * b ) {
    // sort in *decreasing* order by reversing comparison
    return *reinterpret_cast<int const *>(b) - *reinterpret_cast<int const *>(a);
}

void BM_qsort(benchmark::State & state) {
    using namespace std;
    const size_t testsize = state.range(0);

    random_device rnd_device;
    mt19937 mersenne_engine(rnd_device());
    uniform_int_distribution<int> dist;
    // construct random vector of (TODO) supplied size
    vector<int> rands(testsize);
    generate_n(rands.begin(),
                    testsize,
                    [&](){ return dist(mersenne_engine); });
    vector<int> test(testsize);    // scratch memory for sort
    while (state.KeepRunning()) {
        // overwrite scratch memory with unsorted data
        copy(rands.begin(), rands.end(), test.begin());
        qsort(test.data(), testsize, sizeof(int), qs_comparator);

        benchmark::DoNotOptimize(test);
    }
}

BENCHMARK(BM_qsort)->Arg(10000);

void BM_stdsort(benchmark::State & state) {
    using namespace std;
    const size_t testsize = state.range(0);

    random_device rnd_device;
    mt19937 mersenne_engine(rnd_device());
    uniform_int_distribution<int> dist;
    vector<int> rands(testsize);
    generate_n(rands.begin(),
                    testsize,
                    [&](){ return dist(mersenne_engine); });
    auto cmpfn = [](int a, int b) { return b < a; };  // reversed
    vector<int> test(testsize);
    while (state.KeepRunning()) {
        copy(rands.begin(), rands.end(), test.begin());
        sort(test.begin(), test.end(), cmpfn);

        benchmark::DoNotOptimize(test);
    }
}

BENCHMARK(BM_stdsort)->Arg(10000);

BENCHMARK_MAIN()
