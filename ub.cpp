#include <iostream>
#include <cstdint>

// A famous example of UB (or failure to handle it, rather)

// https://randomascii.wordpress.com/2014/04/17/buggy-security-guidance-from-apple/
// slightly tweaked to make it more obvious
void apple(int m, int n) {
    size_t bytes = n * m;      // UB activated, potentially

    if (n > 0 && m > 0 && SIZE_MAX/n >= m) { // a check *after* UB may have occurred
        /* allocate "bytes" space */
        std::cout << "all good\n";
    } else {
        std::cerr << "rejecting allocation of excessive size\n";
    }
}

// In my tests neither clang nor gcc "take advantage" of the UB to perform optimizations
// gcc, however, does take advantage of the fact that if n>0 and m>0 the sign bits of those
// 32b quantities are not set and therefore they are at most 2^31-1, the product of which
// cannot exceed SIZE_MAX (2^64-1 on my machine).  This results in the removal of the
// SIZE_MAX/n division at O2 and above.


int main() {
    // trigger UB
    apple(1 << 16, 1 << 16);
}
