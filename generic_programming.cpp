// Some examples to illustrate generic programming

#include <cassert>

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
#include <functional>

void reuse_example() {
    using namespace std;
    vector<int> ints{7, 42, 1};
    vector<string> strings{"abc", "123", "foo", "bar"};

    // same code, different container
    auto i_it = find(ints.begin(), ints.end(), 42);
    assert(i_it != ints.end());
    auto s_it = find(strings.begin(), strings.end(), "foo");
    assert(s_it != strings.end());

}

template<typename F, typename G>
struct composer {
    composer(F f, G g) : f_(f), g_(g) {}

    // I could use variadic template here but this is simpler to explain:
    // Also we could check to see if the functions were compatible, had just one arg, etc.
    template<typename T>
    T
    operator()(T const& t) {
        return f_(g_(t));
    }

private:
    F f_;
    G g_;

};

template<typename F, typename G>
composer<F, G>
make_composer(F f, G g) {
    return composer<F, G>(f, g);
}

int
composed(int a) {
    return make_composer([](int x) { return x + 2; },
                         [](int y) { return 2 * y; })(a);
}

int main() {
    // our hand-created one
    std::cout << composed(10) << "\n";
    // or use the standard library
    auto composer2 = [](auto f, auto g) {
        return [f, g](int x) { return f(g(x)); };
    };

    std::cout << composer2([](int x) { return x + 2; },
                           [](int y) { return 2 * y; })(10) << "\n";

}
   
void concept_violation() {
    std::vector<int> foo{3, 5, 7, 4, 6};
    std::list<int>   bar{3, 5, 7, 4, 6};

    std::sort(foo.begin(), foo.end());   // works
//  std::sort(bar.begin(), bar.end());   // fails to compile - root cause is not RandomAccessIterator
}
