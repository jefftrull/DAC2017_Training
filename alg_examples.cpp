// Demonstrating the difference between hand-rolled loops and standard algorithms

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <iterator>

// adjacent_difference example
// transform copy if
// find if

// observations: mechanical; filter criteria intermixed with other code

bool
any_even_handrolled(std::vector<int> const& values) {
    for ( int i = 0; i < values.size(); ++i ) {
        if ((values[i] % 2) == 0) {
            return true;
        }
    }
    return false;
}

bool
all_even_handrolled(std::vector<int> const& values) {
    for ( int i = 0; i < values.size(); ++i ) {
        if ((values[i] % 2) != 0) {
            return false;
        }
    }
    return true;
}

int
count_even_handrolled(std::vector<int> const& values) {
    int count = 0;
    for ( int i = 0; i < values.size(); ++i ) {
        if ((values[i] % 2) == 0) {
            count++;
        }
    }
    return count;
}

// look for adjacent values that are two apart
auto
adj_find_handrolled(std::vector<int> const& values) {
    if (values.size() < 2) {
        return values.end();
    }
    auto first = values.begin();
    auto second = values.begin() + 1;
    while (second != values.end()) {
        if ((*second - *first) == 2) {
            return first;
        }
        ++first;
        ++second;
    }
    return values.end();
}

int main() {
    using namespace std;

    vector<int> values{1, 2, 3, 3, 4, 6, 7};

    if (any_even_handrolled(values)) {
        cout << "some elements are even\n";
    } else {
        cout << "no elements are even\n";
    }

    // standard algorithm
    auto is_even = [](int v) { return v % 2 == 0; };
    if (any_of(values.begin(), values.end(), is_even)) {
        cout << "some elements are even\n";
    } else {
        cout << "no elements are even\n";
    }

    if (all_even_handrolled(values)) {
        cout << "all elements are even\n";
    } else {
        cout << "some elements are odd\n";
    }

    // standard algorithm
    if (all_of(values.begin(), values.end(), is_even)) {
        cout << "all elements are even\n";
    } else {
        cout << "some elements are odd\n";
    }

    int count = count_even_handrolled(values);
    cout << "there are " << count << " even values\n";

    count = count_if(values.begin(), values.end(), is_even);
    
    cout << "there are " << count << " even values\n";

    auto it = adj_find_handrolled(values);
    if (it != values.end()) {
        cout << "there is a distance of 2 between the value at offset " << distance(values.cbegin(), it);
        cout << " and the value at offset " << distance(values.cbegin(), it)+1 << "\n";
    } else {
        cout << "there are no adjacent values that are 2 apart\n";
    }

    auto it_std = adjacent_find(values.begin(), values.end(),
                                [](auto a, auto b) { return b - a == 2; });
    if (it_std != values.end()) {
        cout << "there is a distance of 2 between the value at offset " << distance(values.begin(), it_std);
        cout << " and the value at offset " << distance(values.begin(), it_std)+1 << "\n";
    } else {
        cout << "there are no adjacent values that are 2 apart\n";
    }

}
