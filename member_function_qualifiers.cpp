// Examples of the use of member function qualifiers
// Author: Jeff Trull <edaskel@att.net>

#include <vector>

template<typename T>
class Holder {
    using container_t = typename std::vector<T>;
    using const_it    = typename container_t::const_iterator;
    using it          = typename container_t::iterator;

public:
    Holder(std::initializer_list<T> values) : item_storage(values) {}

    // const-qualified member functions return const versions
    const_it begin() const {
        return item_storage.begin();   // TODO: or cbegin?
    }
    const_it end() const {
        return item_storage.end();
    }
    container_t const & contents() const & {
        return item_storage;
    }

    // non-const qualified members have *the same name* but
    // compiler can figure out how to choose them from the context
    it begin() {
        return item_storage.begin();
    }
    it end() {
        return item_storage.end();
    }
    container_t & contents() & {
        return item_storage;
    }

    container_t && contents() && {
        return std::move(item_storage);
    }

private:
    std::vector<T> item_storage;
};

int main() {
    Holder<int> const citems{1, 2, 3};
    Holder<int>        items{1, 2, 3};

    for(auto & i : items) {     // accesses non-const version of begin/end
        i = 5;                  // works
    }
    for(auto & i : citems) {    // accesses const version of begin and end
        // i = 5;               // fails to compile
    }

    auto & itemsr = items.contents();
    itemsr.push_back(4);
    
    auto & itemscr = citems.contents();
    // itemscr.push_back(4);    // will not compile

    auto itemsmr = Holder<int>{1, 2, 3}.contents();   // move initialization
}
