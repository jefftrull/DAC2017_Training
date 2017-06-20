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

void qs_sorter( std::vector<int> v ) {
    qsort(v.data(), v.size(), sizeof(int), qs_comparator);
    benchmark::DoNotOptimize(v);
}

auto std_comparator = [](int a, int b) { return b < a; };  // reversed

void std_sorter( std::vector<int> v ) {
    sort(v.begin(), v.end(), std_comparator);
    benchmark::DoNotOptimize(v);
}

template<typename Sorter>
void BM_sort(Sorter s, benchmark::State & state) {
    using namespace std;
    const size_t testsize = state.range(0);

    random_device rnd_device;
    mt19937 mersenne_engine(rnd_device());
    uniform_int_distribution<int> dist;

    // construct random vector of supplied size
    vector<int> rands(testsize);
    generate_n(rands.begin(),
               testsize,
               [&](){ return dist(mersenne_engine); });

    while (state.KeepRunning()) {
        s(rands);
    }
}

void BM_qsort(benchmark::State & state) {
    BM_sort(qs_sorter, state);
}

void BM_stdsort(benchmark::State & state) {
    BM_sort(std_sorter, state);
}

BENCHMARK(BM_qsort)->Arg(10000);

BENCHMARK(BM_stdsort)->Arg(10000);

BENCHMARK_MAIN()
